#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Twist.h>	
#include "geometry_msgs/PoseStamped.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/ParamSet.h>
#include <actionlib/server/simple_action_server.h>
#include "mongodb_store/message_store.h"
#include "rosplan_knowledge_msgs/KnowledgeItem.h"
#include "rosplan_knowledge_msgs/KnowledgeUpdateService.h"
#include "std_srvs/Empty.h"
#include "diagnostic_msgs/KeyValue.h"
#include "tf/transform_listener.h"
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"
#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/Odometry.h"
#include "nav_msgs/GetMap.h"
#include "geometry_msgs/PoseStamped.h"
#include "mongodb_store/message_store.h"
#include "rosplan_knowledge_msgs/KnowledgeItem.h"
#include "rosplan_knowledge_msgs/KnowledgeUpdateService.h"
#include "rosplan_knowledge_msgs/CreatePRM.h"
#include "rosplan_knowledge_msgs/AddWaypoint.h"
#include "rosplan_knowledge_msgs/RemoveWaypoint.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdlib.h> 
#include <algorithm> 
#include <streambuf>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"
#include "semantic_slam_msgs/doors.h"

using namespace std;

int ENABLE_ROBOT_SIZE = 0;
int ENABLE_DOOR_OPEN_TIME = 0;

typedef struct 
{
	unsigned update_type;
	unsigned char knowledge_type;
	string instance_type;
	string instance_name;
	string attribute_name;
	vector<diagnostic_msgs::KeyValue> values;
	double function_value;
}T_KNOWLEDGE_ITEM;

typedef struct 
{
	vector<T_KNOWLEDGE_ITEM> item;
}T_KNOWLEDGE_UPDAE;

vector<string> tokenize_getline(const string& data, const char delimiter = ' ') 
{
	vector<string> result;
	string token;
	stringstream ss(data);

	while (getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

semantic_slam_msgs::places places;
semantic_slam_msgs::doors doors;
float robot_size = 0.0f;
int recvMsgFlag = 0;
string filepath;


vector<T_KNOWLEDGE_ITEM> m_objects;
vector<T_KNOWLEDGE_ITEM> m_init;
vector<T_KNOWLEDGE_ITEM> m_goal;
vector<string> blocklist;


ros::ServiceClient update_knowledge_client;

void PlacesInfoCB(const semantic_slam_msgs::places msg);
void DoorInfoCB(const semantic_slam_msgs::doors msg);
vector<T_KNOWLEDGE_ITEM> ParserObject(void);
T_KNOWLEDGE_ITEM AddObject(string type, string name);
vector<T_KNOWLEDGE_ITEM> ParserConnected(void);
vector<T_KNOWLEDGE_ITEM> ParserInsideOf(void);
T_KNOWLEDGE_ITEM AddInitRobotAt(string r, string p);
T_KNOWLEDGE_ITEM AddGoal(string r, string p);
void UpdateInstance(vector<T_KNOWLEDGE_ITEM> item);
void printfUpdateArray(vector<T_KNOWLEDGE_ITEM> src);
int CheckBlockList(string name1, string name2);


T_KNOWLEDGE_ITEM AddObject(string type, string name)
{
	int update_type = 0; 
	int knowledge_type = 0;

	T_KNOWLEDGE_ITEM temp;
	temp.update_type = update_type;
	temp.knowledge_type = knowledge_type;
	temp.instance_type = type;
	temp.instance_name = name;
	return temp;
}

T_KNOWLEDGE_ITEM AddInitRobotAt(string r, string p)
{
	int update_type = 0; 
	int knowledge_type = 1;
	diagnostic_msgs::KeyValue valuetemp;
	T_KNOWLEDGE_ITEM temp;
	temp.update_type = update_type;
	temp.knowledge_type = knowledge_type;
	temp.instance_type = "";
	temp.instance_name = "";
	temp.attribute_name = "robot_at";
	valuetemp.key = "r";
	valuetemp.value = r;
	temp.values.push_back(valuetemp);
	valuetemp.key = "p";
	valuetemp.value = p;
	temp.values.push_back(valuetemp);
	temp.function_value = 0.0;
	return temp;
}
T_KNOWLEDGE_ITEM AddGoal(string r, string p)
{
	int update_type = 1; 
	int knowledge_type = 1;
	diagnostic_msgs::KeyValue valuetemp;
	T_KNOWLEDGE_ITEM temp;
	temp.update_type = update_type;
	temp.knowledge_type = knowledge_type;
	temp.instance_type = "";
	temp.instance_name = "";
	temp.attribute_name = "robot_at";
	valuetemp.key = "r";
	valuetemp.value = r;
	temp.values.push_back(valuetemp);
	valuetemp.key = "p";
	valuetemp.value = p;
	temp.values.push_back(valuetemp);
	temp.function_value = 0.0;
	return temp;
}

vector<T_KNOWLEDGE_ITEM> ParserObject(void)
{
	vector<T_KNOWLEDGE_ITEM> result;
	//problem.pddl <- object's types
	int update_type = 0; 
	int knowledge_type = 0;

	string file_name = filepath + "Placename.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;

	
	T_KNOWLEDGE_ITEM temp;
	temp.update_type = update_type;
	temp.knowledge_type = knowledge_type;

	while (infile.peek() != EOF) 
	{
		getline(infile, line);
	
		if (line.find("corridor") != string::npos) 
		{
			temp.instance_type = "corridor";
			temp.instance_name = line;
			result.push_back(temp);
		}
		else if (line.find("doorway") != string::npos) 
		{
			temp.instance_type = "doorway";
			temp.instance_name = line;
			result.push_back(temp);
		}
		else if (line.find("elevator") != string::npos) 
		{
			temp.instance_type = "elevator";
			temp.instance_name = line;
			result.push_back(temp);
		}
		else if (line.find("room") != string::npos) 
		{
			temp.instance_type = "room";
			temp.instance_name = line;
			result.push_back(temp);
		}
		else if (line.find("sidewalk") != string::npos) 
		{
			temp.instance_type = "sidewalk";
			temp.instance_name = line;
			result.push_back(temp);
		}
		else if (line.find("staircase") != string::npos) 
		{
			temp.instance_type = "staircase";
			temp.instance_name = line;
			result.push_back(temp);
		}	
	}
	infile.close();
	return result;
}
int CheckBlockList(string name1, string name2)
{
	int size = blocklist.size();
	for(int i=0 ; i<size ; i++)
	{
		if(blocklist[i] == name1 || blocklist[i] == name2)
		{
			return 1;
		}
	}
	return 0;
}
vector<T_KNOWLEDGE_ITEM> ParserConnected(void)
{
	vector<T_KNOWLEDGE_ITEM> result;
	diagnostic_msgs::KeyValue valuetemp;
	//problem.pddl <- object's types
	int update_type = 0; 
	int knowledge_type = 1;

	string file_name = filepath + "Connected.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;

	while (infile.peek() != EOF) 
	{
		getline(infile, line);
		vector<string> token = tokenize_getline(line, ',');
		if(CheckBlockList(token[0],token[1]) == 1)
			continue;

		T_KNOWLEDGE_ITEM temp;
		temp.update_type = update_type;
		temp.knowledge_type = knowledge_type;
		temp.instance_type = "";
		temp.instance_name = "";
		temp.attribute_name = "connected";
		valuetemp.key = "from";
		valuetemp.value = token[0];
		temp.values.push_back(valuetemp);
		valuetemp.key = "to";
		valuetemp.value = token[1];
		temp.values.push_back(valuetemp);
		temp.function_value = 0.0;
		result.push_back(temp);

	}
	infile.close();
	return result;	
}

vector<T_KNOWLEDGE_ITEM> ParserInsideOf(void)
{
	vector<T_KNOWLEDGE_ITEM> result;
	diagnostic_msgs::KeyValue valuetemp;
	//problem.pddl <- object's types
	int update_type = 0; 
	int knowledge_type = 1;

	string file_name = filepath + "Insideof.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;

	while (infile.peek() != EOF) 
	{
		getline(infile, line);
		vector<string> token = tokenize_getline(line, ',');

		if (token[0].find("floor") == string::npos) 
		{
			continue;
		}

		T_KNOWLEDGE_ITEM temp;
		temp.update_type = update_type;
		temp.knowledge_type = knowledge_type;
		temp.instance_type = "";
		temp.instance_name = "";
		temp.attribute_name = "isinsideof";
		valuetemp.key = "floor";
		valuetemp.value = token[0];
		temp.values.push_back(valuetemp);
		valuetemp.key = "wp";
		valuetemp.value = token[1];
		temp.values.push_back(valuetemp);
		temp.function_value = 0.0;
		result.push_back(temp);

	}
	infile.close();
	return result;	
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "rosplan_excuter");
	ros::NodeHandle n;
	string target_goal;
	string init_pos;
	string robotname;
	ros::Rate r(10.0);

	n.param<std::string>("/executer_node/robot_name", robotname, "nrlab02");
	n.param<std::string>("/executer_node/robot_at", init_pos, "sidewalk1");
	n.param<std::string>("/executer_node/goal", target_goal, "room33");
	n.param("/executer_node/check_door_width", ENABLE_ROBOT_SIZE, 0);
	n.param("/executer_node/check_door_open_time", ENABLE_DOOR_OPEN_TIME, 0);
	n.param<std::string>("/executer_node/file_dir", filepath, "/home/msi/catkin_ws/src/semantic_slam/semantic_slam_db_interface/config/");
	

	printf("---robot_name : %s\n", robotname.c_str());
	printf("---robot_at : %s\n", init_pos.c_str());
	printf("---goal : %s\n", target_goal.c_str());
	printf("---check door witdh : %d\n", ENABLE_ROBOT_SIZE);
	printf("---check door time : %d\n", ENABLE_DOOR_OPEN_TIME);

	if(robotname == "anv")
	{
		robot_size = 0.7f;
	}else if(robotname == "kirobot")
	{
		robot_size = 0.7f;
	}else if(robotname == "nrlab02")
	{
		robot_size = 0.4f;
	}
	printf("---robot size : %f\n", robot_size);


	update_knowledge_client = n.serviceClient<rosplan_knowledge_msgs::KnowledgeUpdateService>("/rosplan_knowledge_base/update");
	ros::Subscriber db_places_sub = n.subscribe<semantic_slam_msgs::places>("semantic_places_info", 10, PlacesInfoCB);
	ros::Subscriber db_doors_sub = n.subscribe<semantic_slam_msgs::doors>("semantic_doors_info", 10, DoorInfoCB);
	// ros::Subscriber ready_sub = n.subscribe<std_msgs::Int32>("semantic_doors_info", 10, DoorInfoCB);



	while(n.ok())
	{
		ros::spinOnce();               		
		if(recvMsgFlag > 0)
			break;
		r.sleep();

	}

	m_objects = ParserObject();
	m_objects.push_back(AddObject("robot", robotname));
	m_objects.push_back(AddObject("floor", "floor1"));
	m_objects.push_back(AddObject("floor", "floor2"));
	m_objects.push_back(AddObject("floor", "floor3"));
	// printfUpdateArray(m_objects);

	
	m_init = ParserConnected();
	vector<T_KNOWLEDGE_ITEM> m_initTemp = ParserInsideOf();
	m_init.insert(m_init.end(), m_initTemp.begin(), m_initTemp.end());
	m_init.push_back(AddInitRobotAt(robotname, init_pos));
	// printfUpdateArray(m_init);



	m_goal.push_back(AddGoal(robotname, target_goal));
	// printfUpdateArray(m_goal);



	UpdateInstance(m_objects);
	UpdateInstance(m_init);
	UpdateInstance(m_goal);

	system("rosservice call /rosplan_problem_interface/problem_generation_server");

	system("rosservice call /rosplan_planner_interface/planning_server");

	system("rosservice call /rosplan_parsing_interface/parse_plan");

	system("rosservice call /rosplan_plan_dispatcher/dispatch_plan");

	
	
	
	while(n.ok())
	{
		ros::spinOnce();               		

		r.sleep();

	}
}


void UpdateInstance(vector<T_KNOWLEDGE_ITEM> item)
{
	rosplan_knowledge_msgs::KnowledgeUpdateService updateSrv;
	int size = item.size();
	printf("updateInstance item.size() = %d\n",size);
	for(int i=0 ; i<size ; i++)
	{
		updateSrv.request.update_type = item[i].update_type;
		updateSrv.request.knowledge.knowledge_type = item[i].knowledge_type;
		updateSrv.request.knowledge.instance_type = item[i].instance_type;
		updateSrv.request.knowledge.instance_name = item[i].instance_name;
		updateSrv.request.knowledge.attribute_name = item[i].attribute_name;
		updateSrv.request.knowledge.values = item[i].values;
		updateSrv.request.knowledge.function_value = 0.0;
		update_knowledge_client.call(updateSrv);
		//printf("--- %s\n",item[i].instance_name.c_str());
	}
}




void printfUpdateArray(vector<T_KNOWLEDGE_ITEM> src)
{
	int len = src.size();
	for(int i=0 ; i<len ; i++)
	{
		printf("[%d] -----------------------\n", i);
		printf("update_type: %d\n", src[i].update_type);
		printf("knowledge_type: %d\n", src[i].knowledge_type);
		printf("instance_type: %s\n", src[i].instance_type.c_str());
		printf("instance_name: %s\n", src[i].instance_name.c_str());
		printf("attribute_name: %s\n", src[i].attribute_name.c_str());
		for(int j=0 ; j<src[i].values.size() ; j++)
		{
			printf(" - key,value: %s / %s\n", src[i].values[j].key.c_str(),src[i].values[j].value.c_str());
		}
	}
}


void PlacesInfoCB(const semantic_slam_msgs::places msg)
{
	places = msg;
	recvMsgFlag = 1;
}

int checkOnce = 0;
void DoorInfoCB(const semantic_slam_msgs::doors msg)
{
	doors = msg;
	recvMsgFlag = 2;

	if(checkOnce == 0)
	{
		struct tm curr_tm;
		time_t curr_time = time(nullptr);
		localtime_r(&curr_time, &curr_tm);

		int curr_hour = curr_tm.tm_hour;
		printf("curr_hour : %d\n", curr_hour);

		int size = doors.doors.size();
		int duplicateCheck = 0;
		for(int i=0 ; i<size ; i++)
		{	
			duplicateCheck = 0;
			if(ENABLE_ROBOT_SIZE)
			{
				if(doors.doors[i].width < robot_size + 0.3) //pffset = 0.3m
				{
					blocklist.push_back(doors.doors[i].doorName);
					duplicateCheck = 1;
				}
			}
			if(ENABLE_DOOR_OPEN_TIME)
			{
				if(doors.doors[i].opentime > curr_hour || doors.doors[i].closetime < curr_hour)
				{
					if(duplicateCheck == 0)
						blocklist.push_back(doors.doors[i].doorName);
				}
			}
		}
		checkOnce = 1;

		printf("Block List [%d]------\n", blocklist.size());
		for(int i=0 ; i<blocklist.size() ; i++)
		{
			printf("[%d] %s\n", i, blocklist[i].c_str());
		}
	}
}