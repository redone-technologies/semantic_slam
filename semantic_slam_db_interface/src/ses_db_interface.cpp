#include <ros/ros.h>

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdlib.h> 
#include <algorithm> 
#include <streambuf>
#include <signal.h>
#include <unistd.h>
#include <vector>
#include <iostream>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"
#include "semantic_slam_msgs/doors.h"
#include "std_msgs/Int32.h"

#define OBJECTID		0
#define OBJECTISMOVABLE	1
#define OBJECTPOINTX	2
#define OBJECTPOINTY	3
using namespace std;

semantic_slam_msgs::objects objects;
semantic_slam_msgs::places places;
semantic_slam_msgs::doors doors;
string filepath;

int get_db_done = 0;


void my_handler(int s);


int socketConnect();
void printfObjects(void);
void printfPlaces(void);
void placeParsing();
void doorInfoParsing();

template <typename ForwardIterator>
ForwardIterator remove_duplicates( ForwardIterator first, ForwardIterator last )
{
    auto new_last = first;
    for ( auto current = first; current != last; ++current )
    {
        if ( std::find( first, new_last, *current ) == new_last )
        {
            if ( new_last != current ) *new_last = *current;
            ++new_last;
        }
    }
    return new_last;
}

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
		int point_size = places.places[i].polygon.points.size();
		for(int j=0 ; j<point_size ; j++)
		{
			printf("[%d] point[%d] : %.2f, %.2f\n", i, j, places.places[i].polygon.points[j].x, places.places[i].polygon.points[j].y);	
		}
		

	}
}
void doorInfoParsing()
{
	string file_name = filepath + "doorinfo.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;
	semantic_slam_msgs::door temp;
	
	while (infile.peek() != EOF) 
	{
		getline(infile, line);
		vector<string> token = tokenize_getline(line, ',');


		temp.doorName = token[0];
		temp.opentime = atoi(token[1].c_str());
		temp.closetime = atoi(token[2].c_str());
		temp.width = atof(token[3].c_str());
		temp.pose.position.x = atof(token[6].c_str());
		temp.pose.position.y = atof(token[7].c_str());
		temp.pose.position.z = atof(token[8].c_str());

		temp.pose.orientation.x = atof(token[9].c_str());
		temp.pose.orientation.y = atof(token[10].c_str());
		temp.pose.orientation.z = atof(token[11].c_str());
		temp.pose.orientation.w = atof(token[12].c_str());

		doors.doors.push_back(temp);
    
	}


	infile.close();

}


void placeParsing()
{
	string file_name = filepath + "Boundary.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;

	vector<string> v;
	while (infile.peek() != EOF) 
	{
		getline(infile, line);
    	v.push_back(line);
	}
	v.erase(remove_duplicates(v.begin(), v.end()), v.end());
	sort(v.begin(), v.end());
	infile.close();

	

	int size = v.size();
	for(int i=0 ; i<size ; i++)
	{
		semantic_slam_msgs::place place;
		vector<geometry_msgs::Point32> points;
		geometry_msgs::Point32 point;
		vector<string> result = tokenize_getline(v[i], ',');

		// printf("size : %d\n",result.size());
		//update place
		place.placeName = result[0];
		int point_size = atoi(result[1].c_str());
		for(int j=0 ; j<point_size ; j++)
		{

			if(result.size() <= 5)
			{
				point.x = 0;
				point.y = 0;
				points.push_back(point);	
			}else
			{
				point.x = atof(result[2+2*j].c_str());
				point.y = atof(result[3+2*j].c_str());
				points.push_back(point);
			}

			
		}
		place.polygon.points = points;
		places.places.push_back(place);
		points.clear();
		place.polygon.points.clear();
	}
	printfPlaces();	

	ofstream out;
	out.open(filepath + "Places.txt");
	int place_count = places.places.size();
	printf("place_count : %d\n", place_count);
	for(int i=0 ; i<place_count ;i++)
	{
		out << 	places.places[i].placeName << endl;
		printf("place : %s\n", places.places[i].placeName.c_str());
	}
	out.close();

}

void PlanSequencyStateCB(const std_msgs::Int32& msg)
{
	get_db_done = msg.data;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "semantic_db_interface");
	ros::NodeHandle n;
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);


	// ros::Publisher objs_pub_ = n.advertise<semantic_slam_msgs::objects>("semantic_objects_info", 100);
	ros::Publisher places_pub_ = n.advertise<semantic_slam_msgs::places>("semantic_places_info", 1);
	ros::Publisher doors_pub_ = n.advertise<semantic_slam_msgs::doors>("semantic_doors_info", 1);

	ros::Subscriber planstate_sub = n.subscribe("plan_sequency_state",1,&PlanSequencyStateCB);
	// ros::Publisher ready_pub_ = n.advertise<std_msgs::Int32>("ready_to_run", 1);

	n.param<std::string>("file_dir", filepath, "/home/msi/catkin_ws/src/semantic_slam/semantic_slam_db_interface/config/");
	

	int parsingDone = 0;
	ros::Rate r(1.0);
	while(n.ok())
	{
		ros::spinOnce();               		


		if(parsingDone == 0 && get_db_done == 1)
		{
			placeParsing();
			doorInfoParsing();
			parsingDone = 1;
			// std_msgs::Int32 msg;
			// msg.data = 1;
			// ready_pub_.publish(msg);
		}

		if(parsingDone == 1)
		{
			places_pub_.publish(places);
			doors_pub_.publish(doors);			
		}

		r.sleep();

	}
}






void my_handler(int s)
{
	printf("Caught signal %d\n",s);
	exit(0);
	ros::shutdown();
}