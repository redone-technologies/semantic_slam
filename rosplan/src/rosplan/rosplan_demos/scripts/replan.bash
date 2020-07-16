#!/bin/bash

finished="false";
while [$finished != "true" ]
do
rosservice call /rosplan_problem_interface/problem_generation_server;
rosservice call /rosplan_planner_interface/planning_server;
rosservice call /rosplan_parsing_interface/parse_plan;
rosservice call /rosplan_plan_dispatcher/dispatch_plan;

if rosservice call /rosplan_plan_dispatcher/dispatch_plan
then
finished="true"
else
finished="false"
fi
done;

echo "Finished!";
 
