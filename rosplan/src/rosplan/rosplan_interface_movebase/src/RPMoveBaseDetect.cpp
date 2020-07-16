#include "rosplan_interface_movebase/RPMoveBaseDetect.h"
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#define DegToRad					0.017453293f
/* The implementation of RPMoveBase.h */
namespace KCL_rosplan {

	/* constructor */
	RPMoveBaseInspect::RPMoveBaseInspect(ros::NodeHandle &nh, std::string &actionserver)
	 : message_store(nh), action_client(actionserver, true) {

		// costmap client
		//clear_costmaps_client = nh.serviceClient<std_srvs::Empty>("/move_base/clear_costmaps");
	}

	/* action dispatch callback */
	bool RPMoveBaseInspect::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) 
	{
		ROS_INFO("KCL: (%s) waiting for Detect action server to start", params.name.c_str());
		action_client.waitForServer();

		// dispatch MoveBase action
		move_base_msgs::MoveBaseGoal goal;

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

				// clear costmaps
				std_srvs::Empty emptySrv;
				clear_costmaps_client.call(emptySrv);

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

	}
} // close namespace

	/*-------------*/
	/* Main method */
	/*-------------*/

	int main(int argc, char **argv) {

		ros::init(argc, argv, "rosplan_interface_movebase");
		ros::NodeHandle nh("~");

		std::string actionserver;
		nh.param("action_server", actionserver, std::string("/move_base"));

		// create PDDL action subscriber
		KCL_rosplan::RPMoveBaseInspect rpmbi(nh, actionserver);

		rpmbi.runActionInterface();

		return 0;
	}
