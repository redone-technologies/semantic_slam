#include "rosplan_interface_movebase/movefloor.h"

/* The implementation of RPMoveBase.h */
namespace KCL_rosplan {

	/* constructor */
	RPMoveFloor::RPMoveFloor(ros::NodeHandle &nh, std::string &actionserver)
	 : message_store(nh), action_client(actionserver, true) {

		// costmap client
		//clear_costmaps_client = nh.serviceClient<std_srvs::Empty>("/move_base/clear_costmaps");
	}

	/* action dispatch callback */
	bool RPMoveFloor::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) 
	{
		ROS_INFO("KCL: (%s) waiting for goto_checkpoint action server to start", params.name.c_str());
		action_client.waitForServer();
		
		// int32 mode  		#1=enter, 2=leave, 3=movefloor
		// int32 cur_floor 	#1,2,3
		// int32 goal_floor

		//get name from action dispatch
		int mode = 3;
		int cur_floor = 0;
		int goal_floor = 0;
		

		int found = 0;
		printf("action name: %s\n", msg->name.c_str());
		// action name: movefloor
		// key: r / value: anv
		// key: from / value: elevator2
		// key: floor1 / value: floor1
		// key: floor2 / value: floor3
		// key: to / value: doorway317
		for(size_t i=0; i<msg->parameters.size(); i++) 
		{

			printf("key: %s / value: %s\n", msg->parameters[i].key.c_str(),msg->parameters[i].value.c_str());
			if(0==msg->parameters[i].key.compare("floor1")) 
			{
				if(msg->parameters[i].value.compare("floor1") == 0)
					cur_floor = 1;
				else if(msg->parameters[i].value.compare("floor2") == 0)
					cur_floor = 2;
				else if(msg->parameters[i].value.compare("floor3") == 0)
					cur_floor = 3;
				else
					cur_floor = 0;
				found += 1;
			}
			else if(0==msg->parameters[i].key.compare("floor2")) 
			{
				if(msg->parameters[i].value.compare("floor1") == 0)
					goal_floor = 1;
				else if(msg->parameters[i].value.compare("floor2") == 0)
					goal_floor = 2;
				else if(msg->parameters[i].value.compare("floor3") == 0)
					goal_floor = 3;
				else
					goal_floor = 0;
				found += 1;
			}
		}


		return true;


		if(found != 2) {
			ROS_INFO("KCL: (%s) aborting action dispatch; PDDL action missing required parameter ?to", params.name.c_str());
			return false;
		}
		//msg parsing -> name
		//how check object or place?


		semantic_slam_msgs::elevatorGoal goal;

		goal.mode = mode;
		goal.cur_floor = cur_floor;
		goal.goal_floor = goal_floor;

		action_client.sendGoal(goal);
		



		bool finished_before_timeout = action_client.waitForResult();
		if (finished_before_timeout) 
		{

			actionlib::SimpleClientGoalState state = action_client.getState();
			ROS_INFO("KCL: (%s) action finished: %s", params.name.c_str(), state.toString().c_str());

			if(state == actionlib::SimpleClientGoalState::SUCCEEDED) 
			{
				// publish feedback (achieved)
				return true;

			} else 
			{
				// publish feedback (failed)
				return false;
			}
		} else 
		{
			// timed out (failed)
			action_client.cancelAllGoals();
			ROS_INFO("KCL: (%s) action timed out", params.name.c_str());
			return false;
		}

		// // get waypoint ID from action dispatch
		// std::string name;
		// bool found = false;
		// for(size_t i=0; i<msg->parameters.size(); i++) {
		// 	if(0==msg->parameters[i].key.compare("to")) {
		// 		wpID = msg->parameters[i].value;
		// 		found = true;
		// 	}
		// }
		// if(!found) {
		// 	ROS_INFO("KCL: (%s) aborting action dispatch; PDDL action missing required parameter ?to", params.name.c_str());
		// 	return false;
		// }
		
		// // get pose from message store
		// std::vector< boost::shared_ptr<geometry_msgs::PoseStamped> > results;
		// if(message_store.queryNamed<geometry_msgs::PoseStamped>(wpID, results)) 
		// {
		// 	if(results.size()<1) 
		// 	{
		// 		ROS_INFO("KCL: (%s) aborting action dispatch; no matching wpID %s", params.name.c_str(), wpID.c_str());
		// 		return false;
		// 	}
		// 	if(results.size()>1)
		// 		ROS_INFO("KCL: (%s) multiple waypoints share the same wpID", params.name.c_str());

		// 	ROS_INFO("KCL: (%s) waiting for move_base action server to start", params.name.c_str());
		// 	action_client.waitForServer();

		// 	// dispatch MoveBase action
		// 	move_base_msgs::MoveBaseGoal goal;
		// 	geometry_msgs::PoseStamped &pose = *results[0];
		// 	goal.target_pose = pose;
		// 	action_client.sendGoal(goal);

		// 	bool finished_before_timeout = action_client.waitForResult();
		// 	if (finished_before_timeout) 
		// 	{

		// 		actionlib::SimpleClientGoalState state = action_client.getState();
		// 		ROS_INFO("KCL: (%s) action finished: %s", params.name.c_str(), state.toString().c_str());

		// 		if(state == actionlib::SimpleClientGoalState::SUCCEEDED) 
		// 		{

		// 			// publish feedback (achieved)
		// 			return true;

		// 		} else 
		// 		{

		// 			// clear costmaps
		// 			std_srvs::Empty emptySrv;
		// 			clear_costmaps_client.call(emptySrv);

		// 			// publish feedback (failed)
		// 			return false;
		// 		}
		// 	} else 
		// 	{
		// 		// timed out (failed)
		// 		action_client.cancelAllGoals();
		// 		ROS_INFO("KCL: (%s) action timed out", params.name.c_str());
		// 		return false;
		// 	}
		// } else {
		// 	// no KMS connection (failed)
		// 	ROS_INFO("KCL: (%s) aborting action dispatch; query to sceneDB failed", params.name.c_str());
		// 	return false;
		// }
	}
} // close namespace

	/*-------------*/
	/* Main method */
	/*-------------*/

	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_semantic_slam_movefloor");
		ros::NodeHandle nh("~");

		std::string actionserver;
		nh.param("action_server", actionserver, std::string("/move_floor"));

		// create PDDL action subscriber
		KCL_rosplan::RPMoveFloor rpmb(nh, actionserver);

		rpmb.runActionInterface();

		return 0;
	}
