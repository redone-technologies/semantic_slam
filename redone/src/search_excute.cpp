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


using namespace std;

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



string ipAddress = "192.168.10.107";
int portNumber = 11000;




vector<T_KNOWLEDGE_ITEM> m_objects;
vector<T_KNOWLEDGE_ITEM> m_init;
vector<T_KNOWLEDGE_ITEM> m_goal;



ros::ServiceClient update_knowledge_client;


int sock = -1;
char recvBuf[1024*1024*2] = {0,};


int socketConnect();
void RequestObjects(unsigned char flag);
void RequestObjects(std::string str);
void RecvXmlFromSocket();
vector<T_KNOWLEDGE_ITEM> Parser(char src[], int update_type, int knowledge_type);
vector<T_KNOWLEDGE_ITEM> Parser(string src, int update_type, int knowledge_type);
void ObejectsRecvAndParse();
void UpdateInstance(vector<T_KNOWLEDGE_ITEM> item);

void printfUpdateArray(vector<T_KNOWLEDGE_ITEM> src);



int main(int argc, char** argv)
{
	ros::init(argc, argv, "rosplan_excuter");
	ros::NodeHandle n;


	update_knowledge_client = n.serviceClient<rosplan_knowledge_msgs::KnowledgeUpdateService>("/rosplan_knowledge_base/update");


	string s;
	if (ros::param::get("/search_excute_node/db_ip", s))
	{
		ROS_INFO("Got param: %s", s.c_str());
		ipAddress = s;
	}
	else
	{
		ROS_WARN("Failed to get param 'db_ip' : default ip : %s", ipAddress.c_str());
		//ros::shutdown();
	}

	int port;
	if (ros::param::get("/search_excute_node/db_port", port))
	{
		ROS_INFO("Got param: %d", port);
		portNumber = port;
	}
	else
	{
	  ROS_WARN("Failed to get param 'db_port' : defualt port = %d", portNumber);
	  //ros::shutdown();
	}



#if 0
	string filename = "/home/msi/catkin_ws/src/semantic_slam/semantic_slam_db_interface/data/search/search_object.xml";
	std::ifstream infile(filename.c_str());
	std::stringstream strStream;
	strStream << infile.rdbuf();
	string alltext = strStream.str();
	m_objects = Parser(alltext, 0, 0);
	printfUpdateArray(m_objects);
	

	string filename2 = "/home/msi/catkin_ws/src/semantic_slam/semantic_slam_db_interface/data/search/search_init.xml";
	std::ifstream infile2(filename2.c_str());
	std::stringstream strStream2;
	strStream2 << infile2.rdbuf();
	string alltext2 = strStream2.str();
	m_init = Parser(alltext2, 0, 1);
	printfUpdateArray(m_init);





	string filename3 = "/home/msi/catkin_ws/src/semantic_slam/semantic_slam_db_interface/data/search/search_goal.xml";
	std::ifstream infile3(filename3.c_str());
	std::stringstream strStream3;
	strStream3 << infile3.rdbuf();
	string alltext3 = strStream3.str();
	m_goal = Parser(alltext3, 1, 1);
	printfUpdateArray(m_goal);

#else

	if(socketConnect() < 0)
		return -1;
	RequestObjects(1);	//1= problem's object
	RecvXmlFromSocket();
	m_objects = Parser(recvBuf, 0, 0);
	printfUpdateArray(m_objects);
	close(sock);


	if(socketConnect() < 0)
		return -1;
	RequestObjects(2);	//2= problem's init
	RecvXmlFromSocket();
	m_init = Parser(recvBuf, 0, 1);
	printfUpdateArray(m_init);
	//usleep(500000);
	close(sock);


	if(socketConnect() < 0)
		return -1;
	RequestObjects(3);	//3= problem's goal
	RecvXmlFromSocket();
	m_goal = Parser(recvBuf, 1, 1);
	printfUpdateArray(m_goal);
	close(sock);


#endif


	UpdateInstance(m_objects);
	UpdateInstance(m_init);
	UpdateInstance(m_goal);

	system("rosservice call /rosplan_problem_interface/problem_generation_server");

	system("rosservice call /rosplan_planner_interface/planning_server");

	system("rosservice call /rosplan_parsing_interface/parse_plan");

	system("rosservice call /rosplan_plan_dispatcher/dispatch_plan");

	
	
	ros::Rate r(10.0);
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
	}
}




int socketConnect()
{
	// 1. socket connect
	struct sockaddr_in serv_addr;
	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1)
	{
		printf("socket Create Failed!! : %d\n",socket);	
		return -1;
	}
	//printf("%s, %d\n",ip.c_str(), portnum);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	serv_addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
	// serv_addr.sin_port = htons(11000);
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
			printf("\n");	
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

	// printf("=========================================\n");
	// printf("recvData: %d\n",recvLen);
	// printf("%s\n",recvBuf);
	// printf("=========================================\n");
}

void printfUpdateArray(vector<T_KNOWLEDGE_ITEM> src)
{
	int len = src.size();
	for(int i=0 ; i<len ; i++)
	{
		printf("-----------------------\n");
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

vector<T_KNOWLEDGE_ITEM> Parser(char src[], int update_type, int knowledge_type)
{
	vector<T_KNOWLEDGE_ITEM> result;
	string alltext(src); 
	int curr, next, start;
	

	vector<string> variables;
	T_KNOWLEDGE_ITEM temp;
	diagnostic_msgs::KeyValue valuetemp;
	int count_xml = 0;
	int count_knowledge = 0;
	//int ccc = 2;
	//while(ccc--)
	while(1)
	{
		//printf("xml substr : %d\n",count_xml);
		
		// 1. find start xml
		int startXmlPos = alltext.find("<?xml");
		if(startXmlPos != string::npos)	
		{
			//printf("startXmlPos : %d\n", startXmlPos);
		}else
		{
			break;
		}
		// 2. find end xml
		int endXmlPos = alltext.find("</sparql>");
		if(endXmlPos != string::npos)	
		{
			//printf("endXmlPos : %d\n",endXmlPos);
		}
		// 3. substr xml
		int cutlen = endXmlPos+9-startXmlPos;
		string strSubXml = alltext.substr(startXmlPos, cutlen);
		alltext = alltext.substr(endXmlPos+9);
		//printf("len : %d\n", strSubXml.length());
		//cout << strSubXml << endl;
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
				//printf("variable : %s\n",str2.c_str());
				variables.push_back(str2);
				strSubXml = strSubXml.substr(next);
			}else
			{
				break;
			}
			usleep(10000);	
		}
		
		//cout << "==================" << endl;
		

		// 5. result substr
		string bindingName;
		string uriValue;
		temp.update_type = update_type;
		temp.knowledge_type = knowledge_type;
		temp.instance_type = "";
		temp.instance_name = "";
		temp.function_value = 0.0;

		if(knowledge_type == 0)
		{
			int linestart = 0;
			int lineend = 0;
			int strpos = 0;
			int count = 0;
			string instance_type;
			string instance_name;
			int objCount = 0;
			while(1) 
			{
				linestart = strSubXml.find("<uri>http://www.ses-plan.org/convention#");
				if(linestart != string::npos)	
				{
					start = strSubXml.find("#", linestart);
					next = strSubXml.find("</uri>", linestart);		
					if(count == 0)
						instance_type = strSubXml.substr(start+1, next - start - 1);
					else if(count == 1)
						instance_name = strSubXml.substr(start+1, next - start - 1);
					strSubXml = strSubXml.substr(next);
					count++;
					if(count == 2)
					{
						printf("[%d] type: %s, name: %s\n",objCount,instance_type.c_str(),instance_name.c_str());
						T_KNOWLEDGE_ITEM temp;
						temp.update_type = 0;
						temp.knowledge_type = 0;
						temp.instance_type = instance_type;
						temp.instance_name = instance_name;
						result.push_back(temp);
						count = 0;
						objCount++;
					}

				}else
				{
					return result;
				}
				usleep(10000);	
			}
		}

		while(1) 
		{
			int linestart = strSubXml.find("<result>");
			if(linestart != string::npos)	
			{
				start = strSubXml.find("<result>", linestart);
				next = strSubXml.find("</result>", linestart);		
				string str2 = strSubXml.substr(start+1, next - start - 1);
				strSubXml = strSubXml.substr(next);
				//printf("5. subStr result\n%s\n",str2.c_str());
				//5.1 parse binding name and value
				int repeatCount = 0;

				while(1)
				{
					int startPos = str2.find("<binding name=");
					if(startPos != string::npos)	
					{
						//5.2 parse binding name
						start = str2.find("\"", startPos);
						next = str2.find("\">", startPos);	
						bindingName = str2.substr(start+1, next - start - 1);
						//printf("[%d]binding_name : %s\n",repeatCount,bindingName.c_str());
						str2 = str2.substr(next);

						//5.2 parse value
						startPos = str2.find("<uri>http://www.ses-plan.org/convention#");
						if(startPos != string::npos)	
						{
							start = str2.find("#", startPos);
							next = str2.find("</uri>", startPos);		
							uriValue = str2.substr(start+1, next - start - 1);
							//printf("[%d]uriVaule : %s\n",repeatCount, uriValue.c_str());
							str2 = str2.substr(next);
						}
						repeatCount++;
						if (variables[0].compare(bindingName) == 0) //attribut_name
						{
							temp.attribute_name = uriValue;
						}else
						{
							valuetemp.key = bindingName;
							valuetemp.value = uriValue;
							temp.values.push_back(valuetemp);
						}
					}else
					{
						break;
					}
				}
				result.push_back(temp);
				temp.values.clear();
				count_knowledge++;
			}else
			{
				break;
			}
			
		}
	}
	printf("XML Parse : %d, knowledge : %d\n",count_xml, count_knowledge);
	return result;
}



vector<T_KNOWLEDGE_ITEM> Parser(string src, int update_type, int knowledge_type)
{
	vector<T_KNOWLEDGE_ITEM> result;
	string alltext = src; 
	int curr, next, start;
	

	vector<string> variables;
	T_KNOWLEDGE_ITEM temp;
	diagnostic_msgs::KeyValue valuetemp;
	int count_xml = 0;
	int count_knowledge = 0;
	//int ccc = 2;
	//while(ccc--)
	while(1)
	{
		//printf("xml substr : %d\n",count_xml);
		
		// 1. find start xml
		int startXmlPos = alltext.find("<?xml");
		if(startXmlPos != string::npos)	
		{
			//printf("startXmlPos : %d\n", startXmlPos);
		}else
		{
			break;
		}
		// 2. find end xml
		int endXmlPos = alltext.find("</sparql>");
		if(endXmlPos != string::npos)	
		{
			//printf("endXmlPos : %d\n",endXmlPos);
		}
		// 3. substr xml
		int cutlen = endXmlPos+9-startXmlPos;
		string strSubXml = alltext.substr(startXmlPos, cutlen);
		alltext = alltext.substr(endXmlPos+9);
		//printf("len : %d\n", strSubXml.length());
		//cout << strSubXml << endl;
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
				//printf("variable : %s\n",str2.c_str());
				variables.push_back(str2);
				strSubXml = strSubXml.substr(next);
			}else
			{
				break;
			}
			usleep(10000);	
		}
		
		//cout << "==================" << endl;
		

		// 5. result substr
		string bindingName;
		string uriValue;
		temp.update_type = update_type;
		temp.knowledge_type = knowledge_type;
		temp.instance_type = "";
		temp.instance_name = "";
		temp.function_value = 0.0;

		if(knowledge_type == 0)
		{
			int linestart = 0;
			int lineend = 0;
			int strpos = 0;
			int count = 0;
			string instance_type;
			string instance_name;
			int objCount = 0;
			while(1) 
			{
				linestart = strSubXml.find("<uri>http://www.ses-plan.org/convention#");
				if(linestart != string::npos)	
				{
					start = strSubXml.find("#", linestart);
					next = strSubXml.find("</uri>", linestart);		
					if(count == 0)
						instance_type = strSubXml.substr(start+1, next - start - 1);
					else if(count == 1)
						instance_name = strSubXml.substr(start+1, next - start - 1);
					strSubXml = strSubXml.substr(next);
					count++;
					if(count == 2)
					{
						printf("[%d] type: %s, name: %s\n",objCount,instance_type.c_str(),instance_name.c_str());
						T_KNOWLEDGE_ITEM temp;
						temp.update_type = 0;
						temp.knowledge_type = 0;
						temp.instance_type = instance_type;
						temp.instance_name = instance_name;
						result.push_back(temp);
						count = 0;
						objCount++;
					}

				}else
				{
					return result;
				}
				usleep(10000);	
			}
		}

		while(1) 
		{
			int linestart = strSubXml.find("<result>");
			if(linestart != string::npos)	
			{
				start = strSubXml.find("<result>", linestart);
				next = strSubXml.find("</result>", linestart);		
				string str2 = strSubXml.substr(start+1, next - start - 1);
				strSubXml = strSubXml.substr(next);
				//printf("5. subStr result\n%s\n",str2.c_str());
				//5.1 parse binding name and value
				int repeatCount = 0;

				while(1)
				{
					int startPos = str2.find("<binding name=");
					if(startPos != string::npos)	
					{
						//5.2 parse binding name
						start = str2.find("\"", startPos);
						next = str2.find("\">", startPos);	
						bindingName = str2.substr(start+1, next - start - 1);
						printf("[%d]binding_name : %s\n",repeatCount,bindingName.c_str());
						str2 = str2.substr(next);

						//5.2 parse value
						startPos = str2.find("<uri>http://www.ses-plan.org/convention#");
						if(startPos != string::npos)	
						{
							start = str2.find("#", startPos);
							next = str2.find("</uri>", startPos);		
							uriValue = str2.substr(start+1, next - start - 1);
							printf("[%d]uriVaule : %s\n",repeatCount, uriValue.c_str());
							str2 = str2.substr(next);
						}
						repeatCount++;
						if (variables[0].compare(bindingName) == 0) //attribut_name
						{
							temp.attribute_name = uriValue;
						}else
						{
							valuetemp.key = bindingName;
							valuetemp.value = uriValue;
							temp.values.push_back(valuetemp);
						}
					}else
					{
						break;
					}
				}
				result.push_back(temp);
				temp.values.clear();
				count_knowledge++;
			}else
			{
				break;
			}
			
		}
	}
	printf("XML Parse : %d, knowledge : %d\n",count_xml, count_knowledge);
	return result;
}


void RequestObjects(std::string str)
{
	printf("req : %s\n", str.c_str());
	char buf[255] = "request object1\n";
	// int r = write(sock, str.c_str(), str.length());
	int r = write(sock, buf, strlen(buf));
	if(r < 0)
	{
		printf("Request Write Error\n");
	}
	printf("req write len : %d\n", r);
}

void ObejectsRecvAndParse()
{
	int r = 0;
	int recvLen = 0;
	char recvBuf[1024*1024] = {0,};

	printf("recv Starting...\n");
	int flag = 0;
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
					printf("AAA\n");
					flag = 1;
					break;
				}
			}
			printf("\n");	
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

	printf("=========================================\n");
	printf("recvData: %d\n",recvLen);
	printf("%s\n",recvBuf);
	printf("=========================================\n");
	
	int curr,next, start;
	string alltext(recvBuf); 


	int linestart = 0;
	int lineend = 0;
	int strpos = 0;
	int count = 0;
	string instance_type;
	string instance_name;
	int objCount = 0;
	while(1) 
	{
		linestart = alltext.find("<uri>http://www.redone.org/plan#");
		if(linestart != string::npos)	
		{
			start = alltext.find("#", linestart);
			next = alltext.find("</uri>", linestart);		
			if(count == 0)
				instance_type = alltext.substr(start+1, next - start - 1);
			else if(count == 1)
				instance_name = alltext.substr(start+1, next - start - 1);
			alltext = alltext.substr(next);
			count++;
			if(count == 2)
			{
				printf("[%d] type: %s, name: %s\n",objCount,instance_type.c_str(),instance_name.c_str());
				T_KNOWLEDGE_ITEM temp;
				temp.update_type = 0;
				temp.knowledge_type = 0;
				temp.instance_type = instance_type;
				temp.instance_name = instance_name;
				m_objects.push_back(temp);
				count = 0;
				objCount++;
			}

		}else
		{
			break;
		}
		usleep(10000);	
	}
}
