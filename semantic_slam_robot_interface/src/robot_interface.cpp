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
#include "semantic_slam_msgs/goto_checkpointAction.h"
#include "semantic_slam_msgs/goto_checkpointGoal.h"
#include "semantic_slam_msgs/goto_checkpointResult.h"


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

	actionlib::SimpleActionServer<semantic_slam_msgs::goto_checkpointAction> as_;
	

public:
	PlanActionServer() :
	as_(nh_, "/goto_checkpoint", boost::bind(&PlanActionServer::executeCB, this, _1), false)
	{
		as_.start();
	}

	~PlanActionServer(void) {
	}

	semantic_slam_msgs::goto_checkpointResult result;
	// Action Interface
	void executeCB(const semantic_slam_msgs::goto_checkpointGoalConstPtr& goal)
	{
		static int count = 0;
		printf("[%d] goal recvd  : %d, %s\n", count++, goal->typeInfo, goal->name.c_str());

		int ok = 0;

		// check type - don't need..., only check 0
		if(goal->typeInfo == 1 || goal->typeInfo == 2)//object=1, place=2
		{
			// check name
			int findFlag = 0;
			int size = (int)objects.objects.size();
			for(int i=0 ; i<size ; i++)
			{
				//find objname -> position 
				if(goal->name.compare(objects.objects[i].objName) == 0) //same
				{

					// find position
					printf("Find obj [%s] position : %.2f, %.2f\n", goal->name.c_str(), objects.objects[i].point.x,objects.objects[i].point.y);
					// [KIRO] send move_base action goal (move_base action client)
					//for detect action
					{
						if(goal->name.compare("kdj_hall") == 0)
						{
							detectActionEnable = 1;
							ok = 1;
							findFlag = 1;
							break;
						}
						
					}

					actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
					ac.waitForServer();
					move_base_msgs::MoveBaseGoal goal;
					goal.target_pose.header.frame_id = "map";
					goal.target_pose.header.stamp = ros::Time::now();

					goal.target_pose.pose.position.x = objects.objects[i].point.x;
					goal.target_pose.pose.position.y = objects.objects[i].point.y;
					goal.target_pose.pose.orientation.w = 1.0;
				SENDING_GOAl:
					ROS_INFO("Sending goal [%d]",count);
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
						system("rosservice call /move_base/clear_costmaps");
    					usleep(1000000);
						goto SENDING_GOAl;
						//ok = 0;
					}

					findFlag = 1;
					break;
				}else
				{
					printf("not found, object name\n");
				}
			}
			if(findFlag == 0)
			{
				printf("[DEBUG][%d]\n",__LINE__);
				int size = (int)places.places.size();
				for(int i=0 ; i<size ; i++)
				{
					//find objname -> position 
					if(goal->name.compare(places.places[i].placeName) == 0) //same
					{
						// find poylgon position
						printf("Find search [%s] place position\n",goal->name);
					
						for(int j=0 ; j<4 ; j++)
						{
							printf("[%d] search place point[%d] : %.2f, %.2f\n", i, j, places.places[i].polygon.points[j].x, places.places[i].polygon.points[j].y);	
						}
						actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);
						ac.waitForServer();
						move_base_msgs::MoveBaseGoal goal;
						goal.target_pose.header.frame_id = "map";
						goal.target_pose.header.stamp = ros::Time::now();

						float x1=0, y1=0, x2=0, y2=0;
						for(int k=0 ; k<4 ; k++)
						{
							if(x1 > places.places[i].polygon.points[k].x)
							{
								//small
								x1 = places.places[i].polygon.points[k].x;
							}
						}
						for(int k=0 ; k<4 ; k++)
						{
							if(y1 > places.places[i].polygon.points[k].y)
							{
								//small
								y1 = places.places[i].polygon.points[k].y;
							}
						}
						for(int k=0 ; k<4 ; k++)
						{
							if(x2 > places.places[i].polygon.points[k].x)
							{
								//big
								x2 = places.places[i].polygon.points[k].x;
							}
						}
						for(int k=0 ; k<4 ; k++)
						{
							if(y2 < places.places[i].polygon.points[k].y)
							{
								//big
								y2 = places.places[i].polygon.points[k].y;
							}
						}
						//cal. center pos.
						float goalx = x1 + (x2 - x1)/2;
						float goaly = y1 + (y2 - y1)/2;

						goal.target_pose.pose.position.x = goalx;
						goal.target_pose.pose.position.y = goaly;
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
	ros::init(argc, argv, "beyond_control");

	ros::NodeHandle n;
	ros::Subscriber db_objects_sub = n.subscribe<semantic_slam_msgs::objects>("semantic_objects_info", 10, dbObjectsCB);
	ros::Subscriber db_places_sub = n.subscribe<semantic_slam_msgs::places>("semantic_places_info", 10, dbPlacesCB);
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
	int detectDuration = 0;

	while(n.ok())
	{
		ros::spinOnce();               		// check for incoming messages

		if(detectActionEnable == 1)
		{
			geometry_msgs::Twist cmd;
			// detectDuration++;
			
			// if(detectDuration >= 600)
			// {
			// 	//detectActionEnable = 0;		
			// 	detectDuration = 0;
			// 	//cmd.linear.x = 0.0;
			// 	//cmd.angular.z = 0.0;
			// }else
			// {
				cmd.linear.x = 3.0;
				cmd.linear.y = 0;
				cmd.linear.z = 0;
				cmd.angular.x = 0;
				cmd.angular.y = 0;
				cmd.angular.z = 2.5;	
			// }
			pub.publish(cmd);
		}

		r.sleep();

	}
}
