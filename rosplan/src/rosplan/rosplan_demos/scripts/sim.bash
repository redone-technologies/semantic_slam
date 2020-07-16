#!/bin/bash

echo "Generating waypoints.";
echo "Adding initial state and goals to knowledge base.";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'agv'
  instance_name: 'cookie0 cookie1 cookie2'
  attribute_name: ''
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 0
  instance_type: 'auv'
  instance_name: 'beyond0'
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
  - {key: 'v', value: 'cookie0'}
  - {key: 'wp', value: 'wp0'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'robot_at'
  values:
  - {key: 'v', value: 'cookie1'}
  - {key: 'wp', value: 'wp2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'robot_at'
  values:
  - {key: 'v', value: 'cookie2'}
  - {key: 'wp', value: 'wp4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'robot_at'
  values:
  - {key: 'v', value: 'beyond0'}
  - {key: 'wp', value: 'wp6'}
  function_value: 0.0";

# =========================================================================
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_indoor'
  values:
  - {key: 'wp', value: 'wp0'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_indoor'
  values:
  - {key: 'wp', value: 'wp1'}
  function_value: 0.0";


# ============================================

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_outdoor'
  values:
  - {key: 'wp', value: 'wp2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_outdoor'
  values:
  - {key: 'wp', value: 'wp3'}
  function_value: 0.0";


# ============================================

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_street'
  values:
  - {key: 'wp', value: 'wp4'}
  function_value: 0.0";


param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_street'
  values:
  - {key: 'wp', value: 'wp5'}
  function_value: 0.0";



# ============================================

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_sky'
  values:
  - {key: 'wp', value: 'wp6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_sky'
  values:
  - {key: 'wp', value: 'wp7'}
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
  - {key: 'wp', value: 'wp0'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp1'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp2'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp3'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp4'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp5'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp6'}
  function_value: 0.0"


param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited'
  values:
  - {key: 'wp', value: 'wp7'}
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
