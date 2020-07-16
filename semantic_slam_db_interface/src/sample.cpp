#include <ros/ros.h>

#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdlib.h> 
#include <algorithm> 

//---------------------------------
#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"

using namespace std;


semantic_slam_msgs::objects objects;
semantic_slam_msgs::places places;


void updateObjectsInfo();
void updatePlacesInfo();


//---------------------------------

void updateObjectsInfo()
{
	semantic_slam_msgs::object object;

	object.objName = "elevator";
	object.id = 1;
	object.point.x = -9.75;
	object.point.y = -8.8;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 2;
	object.point.x = -9;
	object.point.y = -21;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 3;
	object.point.x = -9;
	object.point.y = -33;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 4;
	object.point.x = -9.3;
	object.point.y = -45;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 5;
	object.point.x = -9.1;
	object.point.y = -57;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 6;
	object.point.x = -9;
	object.point.y = -69;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 7;
	object.point.x = -9;
	object.point.y = -81;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 8;
	object.point.x = -8.6;
	object.point.y = -93;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 9;
	object.point.x = -8.9;
	object.point.y = -105;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "tri_column";
	object.id = 10;
	object.point.x = -8.6;
	object.point.y = -117;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 1;
	object.point.x = 6.5;
	object.point.y = -2.8;
	object.isMovable = false;

	objects.objects.push_back(object);
	object.objName = "column";
	object.id = 2;
	object.point.x = 6;
	object.point.y = -9;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 3;
	object.point.x = 5.6;
	object.point.y = -21;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 4;
	object.point.x = 5.4;
	object.point.y = -33;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 5;
	object.point.x = 5.3;
	object.point.y = -45;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 6;
	object.point.x = 4.5;
	object.point.y = -57.3;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 7;
	object.point.x = 4.4;
	object.point.y = -69;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 8;
	object.point.x = 4.5;
	object.point.y = -81.5;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 9;
	object.point.x = 3.6;
	object.point.y = -93;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 10;
	object.point.x = 3.3;
	object.point.y = -105;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 11;
	object.point.x = 3.1;
	object.point.y = -117;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 12;
	object.point.x = 2.7;
	object.point.y = -129;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 13;
	object.point.x = 11.5;
	object.point.y = -129;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 14;
	object.point.x = 11.3;
	object.point.y = -138;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 15;
	object.point.x = 11.8;
	object.point.y = -145;
	object.isMovable = false;

	objects.objects.push_back(object);
	object.objName = "column";
	object.id = 16;
	object.point.x = -7.1;
	object.point.y = -143;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 17;
	object.point.x = -15.8;
	object.point.y = -143;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 18;
	object.point.x = -24.2;
	object.point.y = -140.5;
	object.isMovable = false;

	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 19;
	object.point.x = -32.7;
	object.point.y = -139;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "column";
	object.id = 20;
	object.point.x = -41.7;
	object.point.y = -137;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "exhibition_number";
	object.id = 1;
	object.point.x = -15;
	object.point.y = -104;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "exhibition_number";
	object.id = 2;
	object.point.x = -15;
	object.point.y = -55;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "exhibition_number";
	object.id = 3;
	object.point.x = -15;
	object.point.y = -107;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "trashcan";
	object.id = 1;
	object.point.x = -8.4;
	object.point.y = -84;
	object.isMovable = false;
	objects.objects.push_back(object);


	object.objName = "trashcan";
	object.id = 2;
	object.point.x = -8.6;
	object.point.y = -29.8;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "trashcan";
	object.id = 3;
	object.point.x = -8.9;
	object.point.y = -23.8;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "waterpurifier";
	object.id = 1;
	object.point.x = -8.3;
	object.point.y = -83;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "waterpurifier";
	object.id = 2;
	object.point.x = -8.8;
	object.point.y = -22.2;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "vending_machine1";
	object.id = 1;
	object.point.x = -8.5;
	object.point.y = -31.8;
	object.isMovable = false;
	objects.objects.push_back(object);

	object.objName = "vending_machine2";
	object.id = 2;
	object.point.x = -8.4;
	object.point.y = -30;
	object.isMovable = false;
	objects.objects.push_back(object);
}

//---------------------------------

void updatePlacesInfo()
{
	semantic_slam_msgs::place place;
	geometry_msgs::Polygon polygon;
	geometry_msgs::Point32 point;


	place.placeName = "information_desk";
	place.id = 1;
	point.x = -6;
	point.y = -128;
	polygon.points.push_back(point);
	point.x = -8.8;
	point.y = -132;
	polygon.points.push_back(point);
	point.x = -10;
	point.y = -130;
	polygon.points.push_back(point);
	point.x = -7.6;
	point.y = -127;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "information_center";
	place.id = 1;
	point.x = -5.3;
	point.y = -124;
	polygon.points.push_back(point);
	point.x = -5.6;
	point.y = -118;
	polygon.points.push_back(point);
	point.x = -8.6;
	point.y = -118;
	polygon.points.push_back(point);
	point.x = -8.6;
	point.y = -124;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "flower_shop";
	place.id = 1;
	point.x = -36;
	point.y = -130;
	polygon.points.push_back(point);
	point.x = -36;
	point.y = -135;
	polygon.points.push_back(point);
	point.x = -44;
	point.y = -135;
	polygon.points.push_back(point);
	point.x = -44;
	point.y = -130;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "cafe_the_may";
	place.id = 1;
	point.x = -15;
	point.y = -130;
	polygon.points.push_back(point);
	point.x = -15;
	point.y = -135;
	polygon.points.push_back(point);
	point.x = -30;
	point.y = -135;
	polygon.points.push_back(point);
	point.x = -30;
	point.y = -130;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "kim_dae_jung_hall";
	place.id = 1;
	point.x = 20;
	point.y = -139;
	polygon.points.push_back(point);
	point.x = 18;
	point.y = -147;
	polygon.points.push_back(point);
	point.x = 24;
	point.y = -139;
	polygon.points.push_back(point);
	point.x = 24;
	point.y = -147;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "escalator1";
	place.id = 1;
	point.x = -4;
	point.y = -26;
	polygon.points.push_back(point);
	point.x = -6;
	point.y = -26;
	polygon.points.push_back(point);
	point.x = -4;
	point.y = -14;
	polygon.points.push_back(point);
	point.x = -6;
	point.y = -14;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();




	place.placeName = "escalator2";
	place.id = 2;
	point.x = -3.5;
	point.y = -88.5;
	polygon.points.push_back(point);
	point.x = -3.5;
	point.y = -100;
	polygon.points.push_back(point);
	point.x = -6;
	point.y = -100;
	polygon.points.push_back(point);
	point.x = -6;
	point.y = -88.5;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "escalator3";
	place.id = 3;
	point.x = 15.5;
	point.y = -123;
	polygon.points.push_back(point);
	point.x = 15;
	point.y = -136;
	polygon.points.push_back(point);
	point.x = 18;
	point.y = -123;
	polygon.points.push_back(point);
	point.x = 18;
	point.y = -136;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "escalator";
	place.id = 4;
	point.x = -14.5;
	point.y = -145;
	polygon.points.push_back(point);
	point.x = -13;
	point.y = -147;
	polygon.points.push_back(point);
	point.x = -26.5;
	point.y = -145;
	polygon.points.push_back(point);
	point.x = -27;
	point.y = -144;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "corridor1";
	place.id = 1;
	point.x = -12;
	point.y = 9;
	polygon.points.push_back(point);
	point.x = 25;
	point.y = 9;
	polygon.points.push_back(point);
	point.x = 25;
	point.y = -112;
	polygon.points.push_back(point);
	point.x = -12;
	point.y = -112;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "corridor2";
	place.id = 2;
	point.x = -12;
	point.y = -112;
	polygon.points.push_back(point);
	point.x = 25;
	point.y = -112;
	polygon.points.push_back(point);
	point.x = 25;
	point.y = -153;
	polygon.points.push_back(point);
	point.x = -12;
	point.y = -153;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "corridor3";
	place.id = 3;
	point.x = -12;
	point.y = -112;
	polygon.points.push_back(point);
	point.x = -80;
	point.y = -112;
	polygon.points.push_back(point);
	point.x = -80;
	point.y = -153;
	polygon.points.push_back(point);
	point.x = -12;
	point.y = -153;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();



	place.placeName = "kdj_center";
	place.id = 1;
	point.x = 25;
	point.y = 9;
	polygon.points.push_back(point);
	point.x = -80;
	point.y = 9;
	polygon.points.push_back(point);
	point.x = -80;
	point.y = -153;
	polygon.points.push_back(point);
	point.x = 25;
	point.y = -153;
	polygon.points.push_back(point);
	place.polygon = polygon;
	places.places.push_back(place);
	polygon.points.clear();
}

//---------------------------------



int main(int argc, char** argv)
{
	ros::init(argc, argv, "db_interface");
	ros::NodeHandle n;

	ros::Publisher objs_pub_ = n.advertise<semantic_slam_msgs::objects>("semantic_objects_info", 100);
	ros::Publisher places_pub_ = n.advertise<semantic_slam_msgs::places>("semantic_places_info", 100);

	updateObjectsInfo();
	updatePlacesInfo();

	ROS_INFO("object_num : %d", (int)objects.objects.size());
	ROS_INFO("place_num : %d", (int)places.places.size());

	ros::Rate r(1.0);
	while(n.ok())
	{
			ros::spinOnce();
			objs_pub_.publish(objects);
			places_pub_.publish(places);
			r.sleep();

	}
}

