#!/bin/bash

# echo "Generating waypoints.";
# # 1 path
# # rosservice call /kcl_rosplan/roadmap_server/create_prm "{nr_waypoints: 10, min_distance: 0.3, casting_distance: 2.0, connecting_distance: 8.0, occupancy_threshold: 10, total_attempts: 10}";

# # 2 path circle
# # rosservice call /kcl_rosplan/roadmap_server/create_prm "{nr_waypoints: 21, waypoints_x: [2192,  2192,  2248, 2286, 2335, 2344, 2335, 2258, 2194, 2256, 2333, 2342, 2333, 2284, 2246, 2202, 2190, 2160, 2210, 2204], waypoints_y: [1999,  2092,  2148, 2147, 2140, 2075, 2000, 1992, 1999, 1992, 2000, 2075, 2140, 2147, 2148, 2140, 2092, 2050, 2045, 2140], min_distance: 0.0, casting_distance: 3.0, connecting_distance: 14.0, occupancy_threshold: 10, total_attempts: 10}";



# # 3 path
# rosservice call /kcl_rosplan/roadmap_server/create_prm "{nr_waypoints: 11, waypoints_x: [2182, 2290, 2330, 2339, 2337, 2320, 2225, 2190, 2184, 2231], waypoints_y: [1999, 1987, 1994, 2070, 2130, 2150, 2153, 2120, 1999, 1989], min_distance: 0.0, casting_distance: 3.0, connecting_distance: 14.0, occupancy_threshold: 10, total_attempts: 10}";

# # rosservice call /kcl_rosplan/roadmap_server/create_prm "{nr_waypoints: 20, waypoints_x: [2182,  2197, 2227, 2322, 2341, 2332, 2292, 2233, 2184, 2231, 2290, 2330, 2339, 2320, 2225, 2195, 2185, 2165, 2210], waypoints_y: [1999,  2135, 2153, 2150, 2070, 1994, 1987, 1989, 1999, 1989, 1987, 1994, 2070, 2150, 2153, 2135, 2090, 2050, 2060], min_distance: 0.0, casting_distance: 3.0, connecting_distance: 14.0, occupancy_threshold: 10, total_attempts: 10}";

# echo "Adding initial state and goals to knowledge base.";
# param_type="update_type:
# - 0";
# param="knowledge:
# - knowledge_type: 0
#   instance_type: 'robot'
#   instance_name: 'kenny'
#   attribute_name: ''
#   function_value: 0.0";

# # for i in $(seq 0 $(( $(rosservice call /rosplan_knowledge_base/state/instances "type_name: 'waypoint'" | sed 's/wp/\n/g' | wc -l) - 2)) )
# for i in $(seq 0 $(( $(rosservice call /rosplan_knowledge_base/state/instances "type_name: 'waypoint'" | sed 's/wp/\n/g' | wc -l) - 3)) )
# do
# param_type="$param_type
# - 1"
# param="$param
# - knowledge_type: 1
#   instance_type: ''
#   instance_name: ''
#   attribute_name: 'visited'
#   values:
#   - {key: 'wp', value: 'wp$i'}
#   function_value: 0.0"
# done;

# rosservice call /rosplan_knowledge_base/update_array "
# $param_type
# $param"

finished="false";

while [ $finished != "true" ]
do

echo "Calling problem generator.";
rosservice call /rosplan_problem_interface/problem_generation_server;

echo "Calling planner interface.";
rosservice call /rosplan_planner_interface/planning_server;

echo "Calling plan parser.";
rosservice call /rosplan_parsing_interface/parse_plan;

echo "Calling plan dispatcher.";
# rosservice call /rosplan_plan_dispatcher/dispatch_plan;

if rosservice call /rosplan_plan_dispatcher/dispatch_plan
then
finished="true"
else
finished="false"
fi
done;



echo "Finished!";
