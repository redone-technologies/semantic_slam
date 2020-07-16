# --------------------------------------------------------------
# install
# --------------------------------------------------------------



# --------------------------------------------------------------
# execution
# --------------------------------------------------------------
roslaunch ses_demos demo.launch

# change goal, initPosition, robotType 
modify ses_demos/demo.launch 




# --------------------------------------------------------------
# reference info
# --------------------------------------------------------------

## db topic
/semantic_doors_info
/semantic_places_info

## db text file
pkg semantic_slam_db_interface/config/*.txt

## rosplan action <--> robot interface
pkg semantic_slam_robot_interface


## db update(db file change)
copy to   tosm_db_handler/tosm_owl/[db file]

modify    tosm_db_handler/launch/redone_db_interface.launch
          --> owl_file_name


## if rosplan unsolve, check file
rosplan_demos/common/problem.pddl
rosplan_demos/common/plan.pddl 



# --------------------------------------------------------------
export ROS_MASTER_URI=http://localhost:11311
export ROS_HOSTNAME=192.168.0.198
# --------------------------------------------------------------









