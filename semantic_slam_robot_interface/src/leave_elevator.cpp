#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Twist.h>	
#include <move_base_msgs/MoveBaseAction.h>
#include "ackermann_msgs/AckermannDrive.h"
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <signal.h>
#include <sys/fcntl.h>
#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"
#include "semantic_slam_msgs/elevatorAction.h"


#define PI							3.1415f
#define DegToRad					0.017453293f
#define RadToDeg					57.29577951f
#define USING_TEST_CODE				0

semantic_slam_msgs::objects objects;
semantic_slam_msgs::places places;
void printfObjects(void);
void printfPlaces(void);


int detectActionEnable = 0;

void my_handler(int s)
{
	//printf("Caught signal %d\n",s);
	ros::shutdown();
}

class PlanActionServer 
{
private:

	ros::NodeHandle nh_;  	

	actionlib::SimpleActionServer<semantic_slam_msgs::elevatorAction> as_;
	

public:
	PlanActionServer() :
	as_(nh_, "/leave_elevator", boost::bind(&PlanActionServer::executeCB, this, _1), false)
	{
		as_.start();
	}

	~PlanActionServer(void) {
	}

	semantic_slam_msgs::elevatorResult result;
	// Action Interface
	void executeCB(const semantic_slam_msgs::elevatorGoalConstPtr& goal)
	{
		static int count = 0;
		// int32 mode  		#1=enter, 2=leave, 3=movefloor
		// int32 cur_floor 	#0,1,2,3
		// int32 goal_floor #0,1,2,3
		printf("[%d] goal recvd. mode: %d, c_floor: %d, g_floor: %d\n", goal->mode, goal->cur_floor, goal->goal_floor);

		int ok = 0;

		if(goal->mode == 2)
		{
			//TODO leave ev
		}else
		{
			//another action->check rosplan dispatch action
			ok = 0;
		}

		
		// send rosplan action result
		if(ok == 1)
		{
			printf("[DEBUG][%d] leaved elevator .\n",__LINE__);
			//action complete, 
			result.result = 1;
			as_.setSucceeded(result);	
		}else
		{
			printf("[DEBUG][%d] Failed leave \n",__LINE__);
			//failed
			result.result = 0;
			as_.setAborted(result);	
		}
	}
};


//move_base/result (move_base_msgs/MoveBaseActionResult) 


void dbObjectsCB(const semantic_slam_msgs::objects msg)
{
	objects = msg;
	//printfObjects();
}

void dbPlacesCB(const semantic_slam_msgs::places msg)
{
	places = msg;
	//printfPlaces();
}

void printfObjects(void)
{
	int size = objects.objects.size();
	for(int i=0 ; i<size ; i++)
	{
		printf("================================\n");
		printf("[%d] objName : %s\n", i, objects.objects[i].objName.c_str());
		printf("[%d] id : %d\n", i, objects.objects[i].id);
		printf("[%d] isMovable : %d\n", i, objects.objects[i].isMovable);
		printf("[%d] point : %.2f, %.2f\n", i, objects.objects[i].point.x, objects.objects[i].point.y);

	}
}
void printfPlaces(void)
{
	int size = places.places.size();
	for(int i=0 ; i<size ; i++)
	{
		printf("================================\n");
		printf("[%d] placeName : %s\n", i, places.places[i].placeName.c_str());
		printf("[%d] id : %d\n", i, places.places[i].id);
		for(int j=0 ; j<4 ; j++)
		{
			printf("[%d] point[%d] : %.2f, %.2f\n", i, j, places.places[i].polygon.points[j].x, places.places[i].polygon.points[j].y);	
		}
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "leave_ev");

	ros::NodeHandle n;
	ros::Subscriber db_objects_sub = n.subscribe<semantic_slam_msgs::objects>("semantic_objects_info", 10, dbObjectsCB);
	ros::Subscriber db_places_sub = n.subscribe<semantic_slam_msgs::places>("semantic_places_info", 10, dbPlacesCB);
	// ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel2", 1000);

	PlanActionServer as_object;

	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);


	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();


	ros::Rate r(10.0);
	int detectDuration = 0;

	while(n.ok())
	{
		ros::spinOnce();               		// check for incoming messages

		r.sleep();

	}
}
