#!/bin/bash

echo "Generating waypoints.";
echo "Adding initial state and goals to knowledge base.";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'object'
  instance_name: 'corridor1 corridor2 corridor3 elevator'
  attribute_name: ''
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 0
  instance_type: 'robot'
  instance_name: 'robot1'
  attribute_name: ''
  function_value: 0.0";


# =========================================================================
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'robot_at'
  values:
  - {key: 'v', value: 'robot1'}
  - {key: 'wp', value: 'corridor1'}
  function_value: 0.0";


param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected'
  values:
  - {key: 'from', value: 'corridor1'}
  - {key: 'to', value: 'corridor2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected'
  values:
  - {key: 'from', value: 'corridor2'}
  - {key: 'to', value: 'corridor3'}
  function_value: 0.0";

  param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected'
  values:
  - {key: 'from', value: 'corridor3'}
  - {key: 'to', value: 'elevator'}
  function_value: 0.0";


#========================================================================= 

param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'v', value: 'robot1'}  
  - {key: 'wp', value: 'corridor2'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'v', value: 'robot1'}
  - {key: 'wp', value: 'corridor3'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'v', value: 'robot1'}
  - {key: 'wp', value: 'elevator'}
  function_value: 0.0"



#========================================================================= 


rosservice call /rosplan_knowledge_base/update_array "
$param_type
$param"


echo "Calling problem generator.";
rosservice call /rosplan_problem_interface/problem_generation_server;

echo "Calling planner interface.";
rosservice call /rosplan_planner_interface/planning_server;

echo "Calling plan parser.";
rosservice call /rosplan_parsing_interface/parse_plan;

echo "Calling plan dispatcher.";
rosservice call /rosplan_plan_dispatcher/dispatch_plan;

echo "Finished!";
