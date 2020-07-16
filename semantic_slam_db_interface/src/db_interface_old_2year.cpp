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


#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "semantic_slam_msgs/objects.h"
#include "semantic_slam_msgs/places.h"

#define USE_TEST_CODE 	0

#define OBJECTID		0
#define OBJECTISMOVABLE	1
#define OBJECTPOINTX	2
#define OBJECTPOINTY	3
using namespace std;

semantic_slam_msgs::objects objects;
semantic_slam_msgs::places places;

string ipAddress = "192.168.10.107";
int portNumber = 11000;

int sock = -1;
char recvBuf[1024*1024] = {0,};
void my_handler(int s);


int socketConnect();
void RequestObjects(unsigned char flag);
void RecvXmlFromSocket();
void Parser(char src[]);
void parseObjects(string xml);
void printfObjects(void);
void parsePlaces(string xml);
void updatePolygon(geometry_msgs::Point32 points[], string strName, string strData);
void printfPlaces(void);



void parseObjects(string xml)
{
	// 0. xml 
	cout << "-----------------------------------------------" << endl;
	cout << "objects" << endl;
	cout << "-----------------------------------------------" << endl;
	// cout << xml << endl;


	// 1. result substr
	string bindingName;
	string uriValue;
	int curr, next, start;
	
	semantic_slam_msgs::object object;
	int checkResult[4] = {0,};
	string preObjName;
	int repeatResultCount = 0;
	while(1) 
	{
		//2. result string 
		int linestart = xml.find("<result>");
		if(linestart != string::npos)	
		{
			repeatResultCount++;
			start = xml.find("<result>", linestart);
			next = xml.find("</result>", linestart);		
			string strResult = xml.substr(start+1, next - start - 1);
			xml = xml.substr(next);
			//printf("2. subStr result\n%s\n",strResult.c_str());
			
			
			// 3. inside result
			//ObjName, objectID, objectIsMovable, objectPointX, objectPointY
			
			while(1)
			{
				int startPos = strResult.find("<binding name=");
				if(startPos != string::npos)	
				{
					//2.2 parse binding name
					start = strResult.find("\"", startPos);
					next = strResult.find("\">", startPos);	
					bindingName = strResult.substr(start+1, next - start - 1);
					//printf("binding_name : %s\n",bindingName.c_str());
					strResult = strResult.substr(next);

					if(bindingName.compare("ObjName") == 0)
					{
						//2.3 parse 
						startPos = strResult.find("<uri>http://semanticslam/ses#");
						if(startPos != string::npos)	
						{
							start = strResult.find("#", startPos);
							next = strResult.find("</uri>", startPos);		
							uriValue = strResult.substr(start+1, next - start - 1);
							strResult = strResult.substr(next);
							//TODO preObj, nextObj
							if(preObjName.compare(uriValue) != 0)
							{
								object.objName = uriValue;
								printf("1. %s : %s\n", bindingName.c_str(), uriValue.c_str());
							}
							preObjName = uriValue;
						}	
					}
					else if(bindingName.compare("Property") == 0)
					{	
						startPos = strResult.find("<uri>http://semanticslam/ses#");
						if(startPos != string::npos)	
						{
							start = strResult.find("#", startPos);
							next = strResult.find("</uri>", startPos);		
							uriValue = strResult.substr(start+1, next - start - 1);
							//printf("2. %s : %s\n", bindingName.c_str(), uriValue.c_str());
							
							//TODO preObj, nextObj
							if(uriValue.compare("objectID") == 0)
							{
								// /cout << strResult << endl;
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#int", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+6, next - start - 6);
									printf("2. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									object.id = atoi(strData.c_str());
									break;
								}
								
							}
							else if(uriValue.compare("objectIsMovable") == 0)
							{
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#boolean", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+10, next - start - 10);
									printf("3. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									if(strData.compare("false") == 0)
									{
										object.isMovable = 0;
									}else
									{
										object.isMovable = 1;
									}
									break;
								}
							}
							else if(uriValue.compare("objectPointX") == 0)
							{
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#float", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+8, next - start - 8);
									printf("4. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									object.point.x = atof(strData.c_str());
									break;
								}
							}
							else if(uriValue.compare("objectPointY") == 0)
							{
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#float", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+8, next - start - 8);
									printf("5. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									object.point.y = atof(strData.c_str());
									break;
								}
							}
							strResult = strResult.substr(next);
						}
					}
				}
				else
				{
					break;
				}
			}
			if(repeatResultCount == 4)
			{
				printf("=======================\n");
				objects.objects.push_back(object);
				repeatResultCount = 0;
			}
		}
		else
		{
			break;
		}
	}
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

void parsePlaces(string xml)
{
	// 0. xml 
	cout << "-----------------------------------------------" << endl;
	cout << "Places" << endl;
	cout << "-----------------------------------------------" << endl;
	// cout << xml << endl;


	// 1. result substr
	string bindingName;
	string uriValue;
	int curr, next, start;
	
	semantic_slam_msgs::place place;
	geometry_msgs::Point32 points[4];

	int checkResult[4] = {0,};
	string preName;
	int repeatResultCount = 0;
	while(1) 
	{
		//2. result string 
		int linestart = xml.find("<result>");
		if(linestart != string::npos)	
		{
			repeatResultCount++;
			start = xml.find("<result>", linestart);
			next = xml.find("</result>", linestart);		
			string strResult = xml.substr(start+1, next - start - 1);
			xml = xml.substr(next);
			//printf("2. subStr result\n%s\n",strResult.c_str());
			
			
			// 3. inside result
			//PlaceName, placeID, place1X, place1Y, place2X, place2Y, place3X, place3Y, place4X, place4Y
			
			while(1)
			{
				int startPos = strResult.find("<binding name=");
				if(startPos != string::npos)	
				{
					//2.2 parse binding name
					start = strResult.find("\"", startPos);
					next = strResult.find("\">", startPos);	
					bindingName = strResult.substr(start+1, next - start - 1);
					//printf("binding_name : %s\n",bindingName.c_str());
					strResult = strResult.substr(next);

					if(bindingName.compare("PlaceName") == 0)
					{
						//2.3 parse 
						startPos = strResult.find("<uri>http://semanticslam/ses#");
						if(startPos != string::npos)	
						{
							start = strResult.find("#", startPos);
							next = strResult.find("</uri>", startPos);		
							uriValue = strResult.substr(start+1, next - start - 1);
							strResult = strResult.substr(next);
							//TODO preObj, nextObj
							if(preName.compare(uriValue) != 0)
							{
								place.placeName = uriValue;
								printf("1. %s : %s\n", bindingName.c_str(), uriValue.c_str());
							}
							preName = uriValue;
						}	
					}
					else if(bindingName.compare("Property") == 0)
					{	
						startPos = strResult.find("<uri>http://semanticslam/ses#");
						if(startPos != string::npos)	
						{
							start = strResult.find("#", startPos);
							next = strResult.find("</uri>", startPos);		
							uriValue = strResult.substr(start+1, next - start - 1);
							//printf("2. %s : %s\n", bindingName.c_str(), uriValue.c_str());
							
							//TODO preObj, nextObj
							if(uriValue.compare("placeID") == 0)
							{
								// /cout << strResult << endl;
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#int", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+6, next - start - 6);
									printf("3. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									place.id = atoi(strData.c_str());
									break;
								}
							}
							else 
							{
								startPos = strResult.find("<literal datatype=\"http://www.w3.org/2001/XMLSchema");
								if(startPos != string::npos)	
								{
									start = strResult.find("#float", startPos);
									next = strResult.find("</literal>", startPos);		
									string strData = strResult.substr(start+8, next - start - 8);
									printf("2. %s : %s\n", uriValue.c_str(), strData.c_str());
									strResult = strResult.substr(next);
									updatePolygon(points, uriValue, strData);
									break;
								}
							}
							strResult = strResult.substr(next);
						}

					}
				}
				else
				{
					break;
				}
			}
			if(repeatResultCount == 9)
			{
				printf("=======================\n");
				place.polygon.points.push_back(points[0]);
				place.polygon.points.push_back(points[1]);
				place.polygon.points.push_back(points[2]);
				place.polygon.points.push_back(points[3]);
				places.places.push_back(place);
				place.polygon.points.clear();
				repeatResultCount = 0;
				
			}
		}
		else
		{
			break;
		}
	}
}

void updatePolygon(geometry_msgs::Point32 points[], string strName, string strData)
{

	if(strName.compare("place1X") == 0)
	{
		points[0].x = atof(strData.c_str());	
	}
	else if(strName.compare("place1Y") == 0)
	{
		points[0].y = atof(strData.c_str());	
	}
	else if(strName.compare("place2X") == 0)
	{
		points[1].x = atof(strData.c_str());	
	}
	else if(strName.compare("place2Y") == 0)
	{
		points[1].y = atof(strData.c_str());	
	}
	else if(strName.compare("place3X") == 0)
	{
		points[2].x = atof(strData.c_str());	
	}
	else if(strName.compare("place3Y") == 0)
	{
		points[2].y = atof(strData.c_str());	
	}
	else if(strName.compare("place4X") == 0)
	{
		points[3].x = atof(strData.c_str());	
	}
	else if(strName.compare("place4Y") == 0)
	{
		points[3].y = atof(strData.c_str());	
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

void fileparsing()
{
	string file_name = "/home/msi/test/xmlparsing.txt";
	std::ifstream infile(file_name.c_str());
	std::string line;
	int curr,next,start,start1,next1;
	std::string alltext((std::istreambuf_iterator<char>(infile)),std::istreambuf_iterator<char>());

	vector<string> variables;
	// T_KNOWLEDGE_ITEM temp;
	// diagnostic_msgs::KeyValue valuetemp;
	int count_xml = 0;
	int count_knowledge = 0;
	while(1)
	{
		// printf("xml substr : %d\n",count_xml);
		
		// 1. find start xml
		int startXmlPos = alltext.find("<?xml");
		if(startXmlPos != string::npos)	
		{
			// printf("startXmlPos : %d\n", startXmlPos);
		}
		else
		{
			break;
		}


		//2.find end xml
		int endXmlPos = alltext.find("</sparql>");
		if (endXmlPos != string::npos)
		{
			// printf("endxmlpos: %d\n", endXmlPos);
		}


		//3. substr xml
		int cutlen = endXmlPos+9-startXmlPos;
		string strSubXml = alltext.substr(startXmlPos, cutlen);
		alltext = alltext.substr(endXmlPos+9);
		// printf("len : %d\n", (int)strSubXml.length());
		// cout << strSubXml << endl;
		// cout << "==========================================" << endl;
		count_xml++;
		

		// 4. find head variable
		while(1) 
		{
			int linestart = strSubXml.find("<variable name");
			if(linestart != string::npos)	
			{
				start = strSubXml.find("\"", linestart);
				next = strSubXml.find("\"/>", linestart);		
				string str2 = strSubXml.substr(start+1, next - start - 1);
				printf("variable : %s\n",str2.c_str());
				variables.push_back(str2);
				strSubXml = strSubXml.substr(next);
			}else
			{
				break;
			}
			usleep(10000);	
		}

		// 5. call parser
		if(variables[0].compare("ObjName") == 0)
		{	
			parseObjects(strSubXml);
			printfObjects();
			
		}
		else if(variables[0].compare("PlaceName") == 0)
		{
			parsePlaces(strSubXml);
			printfPlaces();
		}
		else
		{
			printf("no parser : %s\n", variables[0].c_str());
		}
		variables.clear();
	}
	printf("XML Parse : %d, objects : %d, placces : %d\n",count_xml, (int)objects.objects.size(), (int)places.places.size());
}



void Parser(char src[])
{
	std::string line;
	int curr,next,start,start1,next1;
	string alltext(src); 

	vector<string> variables;
	// T_KNOWLEDGE_ITEM temp;
	// diagnostic_msgs::KeyValue valuetemp;
	int count_xml = 0;
	int count_knowledge = 0;
	while(1)
	{
		// printf("xml substr : %d\n",count_xml);
		
		// 1. find start xml
		int startXmlPos = alltext.find("<?xml");
		if(startXmlPos != string::npos)	
		{
			// printf("startXmlPos : %d\n", startXmlPos);
		}
		else
		{
			break;
		}


		//2.find end xml
		int endXmlPos = alltext.find("</sparql>");
		if (endXmlPos != string::npos)
		{
			// printf("endxmlpos: %d\n", endXmlPos);
		}


		//3. substr xml
		int cutlen = endXmlPos+9-startXmlPos;
		string strSubXml = alltext.substr(startXmlPos, cutlen);
		alltext = alltext.substr(endXmlPos+9);
		// printf("len : %d\n", (int)strSubXml.length());
		// cout << strSubXml << endl;
		// cout << "==========================================" << endl;
		count_xml++;
		

		// 4. find head variable
		while(1) 
		{
			int linestart = strSubXml.find("<variable name");
			if(linestart != string::npos)	
			{
				start = strSubXml.find("\"", linestart);
				next = strSubXml.find("\"/>", linestart);		
				string str2 = strSubXml.substr(start+1, next - start - 1);
				printf("variable : %s\n",str2.c_str());
				variables.push_back(str2);
				strSubXml = strSubXml.substr(next);
			}else
			{
				break;
			}
			usleep(10000);	
		}

		// 5. call parser
		if(variables[0].compare("ObjName") == 0)
		{	
			parseObjects(strSubXml);
			printfObjects();
			
		}
		else if(variables[0].compare("PlaceName") == 0)
		{
			parsePlaces(strSubXml);
			printfPlaces();
		}
		else
		{
			printf("no parser : %s\n", variables[0].c_str());
		}
		variables.clear();
	}
	printf("XML Parse : %d, objects : %d, placces : %d\n",count_xml, (int)objects.objects.size(), (int)places.places.size());
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


	ros::Publisher objs_pub_ = n.advertise<semantic_slam_msgs::objects>("semantic_objects_info", 100);
	ros::Publisher places_pub_ = n.advertise<semantic_slam_msgs::places>("semantic_places_info", 100);

	string s;
	if (ros::param::get("/db_interface_node/db_ip", s))
	{
		ROS_INFO("Got param: %s", s.c_str());
		ipAddress = s;
	}
	else
	{
		ROS_WARN("Failed to get param 'robot_ip' : default ip : %s", ipAddress.c_str());
		//ros::shutdown();
	}

	int port;
	if (ros::param::get("/db_interface_node/db_port", port))
	{
		ROS_INFO("Got param: %d", port);
		portNumber = port;
	}
	else
	{
	  ROS_WARN("Failed to get param 'db_port' : defualt port = %d", portNumber);
	  //ros::shutdown();
	}

#if USE_TEST_CODE
	fileparsing();
	//return 0;
#else
	if(socketConnect() < 0)
		return -1;
	RequestObjects(1);
	RecvXmlFromSocket();
	Parser(recvBuf);
	close(sock);
#endif

	ros::Rate r(1.0);
	while(n.ok())
	{
		ros::spinOnce();               		

		objs_pub_.publish(objects);
		places_pub_.publish(places);

		r.sleep();

	}
}




int socketConnect()
{
	// 1. socket connect
	struct sockaddr_in serv_addr;
	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1)
	{
		printf("socket Create Failed!! : %d\n",sock);	
		return -1;
	}

	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	serv_addr.sin_port = htons(portNumber);

TRY_CONNECT:
	int r = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if(r == -1)
	{
		printf("socket connection Failed!! : %d\n",sock);	
		usleep(200000);
		goto TRY_CONNECT;
		//return -2;
	}
	printf("socket connection ok\n");
	return 1;
}


void RequestObjects(unsigned char flag)
{
	// int r = write(sock, str.c_str(), str.length());
	char buf[1];
	buf[0] = flag;
	int r = write(sock, buf, sizeof(buf));
	if(r < 0)
	{
		printf("Request Write Error\n");
	}
	printf("req write len : %d\n", r);
}



void RecvXmlFromSocket()
{
	int r = 0;
	int recvLen = 0;
	printf("recv Starting...\n");
	int flag = 0;
	memset(&recvBuf, 0, sizeof(recvBuf));
	while(1)
	{
		char buf[2048] = {0,};
		r = read(sock, buf, sizeof(buf));
		//printf("r = %d, %s\n",r, buf);

		if(r > 0)
		{
			memcpy(recvBuf+recvLen, buf, r);
			recvLen += r;
			for(int i=0 ; i<r ; i++)
			{
				//printf("0x%02X | ", buf[i]);
				if(buf[i] == '$')
				{
					printf("Recv End\n");
					flag = 1;
					break;
				}
			}
			//printf("\n");	
		}else
		{
			printf("read failed\n");
			break;
		}
		if(flag == 1)
			break;
		//printf("BBB\n");
		usleep(100000);
	}
	printf("%s\n", recvBuf);

}



void my_handler(int s)
{
	printf("Caught signal %d\n",s);
	close(sock);
	exit(0);
	ros::shutdown();
}