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
#include <geometry_msgs/Point32.h>
#include <signal.h>
#include <sys/fcntl.h>
#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"
#include "semantic_slam_msgs/doors.h"
#include "semantic_slam_msgs/gotoAction.h"
#include <string.h>

#define PI							3.1415f
#define DegToRad					0.017453293f
#define RadToDeg					57.29577951f
#define USING_TEST_CODE				0

using namespace std;

semantic_slam_msgs::objects objects;
semantic_slam_msgs::places places;
semantic_slam_msgs::doors doors;
void printfObjects(void);
void printfPlaces(void);


int receivedPlaces = 0; 
int receivedDoors = 0; 

void my_handler(int s)
{
	//printf("Caught signal %d\n",s);
	ros::shutdown();
}

class PlanActionServer 
{
private:

	ros::NodeHandle nh_;  	

	actionlib::SimpleActionServer<semantic_slam_msgs::gotoAction> as_;
	

public:
	PlanActionServer() :
	as_(nh_, "/goto", boost::bind(&PlanActionServer::executeCB, this, _1), false)
	{
		as_.start();
	}

	~PlanActionServer(void) {
	}

	semantic_slam_msgs::gotoResult result;
	// Action Interface
	void executeCB(const semantic_slam_msgs::gotoGoalConstPtr& goal)
	{
		// static int count = 0;
		printf("[%d] goal recvd  : %s\n", goal->typeInfo, goal->name.c_str());
		// result.result = 1;
		// as_.setSucceeded(result);	
		// return;
		while(receivedPlaces == 0)
			usleep(100000);
		while(receivedDoors == 0)
			usleep(100000);

		int ok = 0;

		// check type - don't need..., only check 0
		if(goal->typeInfo == 1 || goal->typeInfo == 2)
		{
			// check name
			int findFlag = 0;
			
			// printf("[DEBUG][%d]\n",__LINE__);
			
			// printf("[DEBUG][%d] places count : %d\n",__LINE__,size);
			
			if (goal->name.find("doorway") != string::npos) 
			{
				int size = doors.doors.size();
				for(int i=0 ; i<size ; i++)
				{
					//find objname -> position 
					// printf("place_name : %s\n",places.places[i].placeName.c_str());
					// int size = (int)places.places.size();
					if(goal->name.compare(doors.doors[i].doorName) == 0) //same
					{
						// find poylgon position
						printf("Find search [%s] door position\n",goal->name.c_str());
					
						actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
						ac.waitForServer();
						move_base_msgs::MoveBaseGoal goal;
						goal.target_pose.header.frame_id = "map";
						goal.target_pose.header.stamp = ros::Time::now();


						goal.target_pose.pose.position.x = doors.doors[i].pose.position.x;
						goal.target_pose.pose.position.y = doors.doors[i].pose.position.y;
						goal.target_pose.pose.orientation.x = doors.doors[i].pose.orientation.x;
						goal.target_pose.pose.orientation.y = doors.doors[i].pose.orientation.y;
						goal.target_pose.pose.orientation.z = doors.doors[i].pose.orientation.z;
						goal.target_pose.pose.orientation.w = doors.doors[i].pose.orientation.w;

						ROS_INFO("Sending goal");
						ac.sendGoal(goal);

						// [KIRO] waiting
						ac.waitForResult();
						// [KIRO] recevice move_base action result
						if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
						{
							// [KIRO] if (move_base success) -> ok=1 (rosplan result)
							ok = 1;
						}else
						{
							// [KIRO] else ok=0;
							ok = 0;
						}

						findFlag = 1;
						break;
					}
				}
			}
			else
			{
				int size = (int)places.places.size();
				for(int i=0 ; i<size ; i++)
				{
					//find objname -> position 
					// printf("place_name : %s\n",places.places[i].placeName.c_str());
					if(goal->name.compare(places.places[i].placeName) == 0) //same
					{
						// find poylgon position
						printf("Find search [%s] place position\n",goal->name.c_str());
					
						int polySize = places.places[i].polygon.points.size(); 
						for(int j=0 ; j<polySize ; j++)
						{
							printf("[%d] search place point[%d] : %.2f, %.2f\n", i, j, places.places[i].polygon.points[j].x, places.places[i].polygon.points[j].y);	
						}

						actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
						ac.waitForServer();
						move_base_msgs::MoveBaseGoal goal;
						goal.target_pose.header.frame_id = "map";
						goal.target_pose.header.stamp = ros::Time::now();

						
						float area = 0;
						float centerx = 0;
						float centery = 0;

						for (i = 0; i < polySize; i++)
						{
						    int j = (i + 1) % polySize;

						    geometry_msgs::Point32 pt1 = places.places[i].polygon.points[i];
						    geometry_msgs::Point32 pt2 = places.places[i].polygon.points[j];
	 
						    float x1 = pt1.x;
						    float x2 = pt2.x;
						    float y1 = pt1.y;
						    float y2 = pt2.y;

						    area += x1 * y2;
						    area -= y1 * x2;

						    centerx += ((x1 + x2) * ((x1 * y2) - (x2 * y1)));
						    centery += ((y1 + y2) * ((x1 * y2) - (x2 * y1)));
						}

						area /= 2.0;
						area = fabs(area);

						centerx = centerx / (6.0 * area);
						centery = centery / (6.0 * area);


						goal.target_pose.pose.position.x = centerx;
						goal.target_pose.pose.position.y = centery;
						goal.target_pose.pose.orientation.x = 0;
						goal.target_pose.pose.orientation.y = 0;
						goal.target_pose.pose.orientation.z = 0;
						goal.target_pose.pose.orientation.w = 1.0;

						ROS_INFO("Sending goal");
						ac.sendGoal(goal);

						// [KIRO] waiting
						ac.waitForResult();
						// [KIRO] recevice move_base action result
						if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
						{
							// [KIRO] if (move_base success) -> ok=1 (rosplan result)
							ok = 1;
						}else
						{
							// [KIRO] else ok=0;
							ok = 0;
						}

						findFlag = 1;
						break;
					}
				}

			}

				
			
			
			if(findFlag == 0)
			{
				printf("[DEBUG][%d] unknown name(%s)\n",__LINE__,goal->name.c_str());
				//failed. unknown name
				//send failed
				result.result = 0;
				as_.setAborted(result);	
			}
		}
		else
		{
			printf("[DEBUG][%d] unknown type (object or place)\n",__LINE__);
			//failed. unknown type
			//send failed
			result.result = 0;
			as_.setAborted(result);	
		}

		
		// send rosplan action result
		if(ok == 1)
		{
			printf("[DEBUG][%d] Arrived %s.\n",__LINE__,goal->name.c_str());
			//action complete, 
			result.result = 1;
			as_.setSucceeded(result);	
		}else
		{
			printf("[DEBUG][%d] Failed go to %s.\n",__LINE__,goal->name.c_str());
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
	// printfPlaces();
	receivedPlaces = 1;
}
void dbDoorCB(const semantic_slam_msgs::doors msg)
{
	doors = msg;
	// printfPlaces();
	receivedDoors = 1;
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
	ros::init(argc, argv, "ses_as_goto");

	ros::NodeHandle n;
	ros::Subscriber db_objects_sub = n.subscribe<semantic_slam_msgs::objects>("semantic_objects_info", 10, dbObjectsCB);
	ros::Subscriber db_places_sub = n.subscribe<semantic_slam_msgs::places>("semantic_places_info", 10, dbPlacesCB);
	ros::Subscriber db_door_sub = n.subscribe<semantic_slam_msgs::doors>("semantic_doors_info", 10, dbDoorCB);
	
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel2", 1000);

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


	while(n.ok())
	{
		ros::spinOnce();               		// check for incoming messages



		r.sleep();

	}
}
