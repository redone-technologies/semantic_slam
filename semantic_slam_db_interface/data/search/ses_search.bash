#!/bin/bash

echo "Generating waypoints.";

rosservice call /kcl_rosplan/roadmap_server/create_prm "{nr_waypoints: 8, waypoints_x: [], waypoints_y: [], min_distance: 0.0, casting_distance: 3.0, connecting_distance: 14.0, occupancy_threshold: 10, total_attempts: 10}";
# ========= object ==============
param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'robot'
  instance_name: 'ugv'
  attribute_name: ''
  function_value: 0.0";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'area'
  instance_name: 'corridor1'
  attribute_name: ''
  function_value: 0.0";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'area'
  instance_name: 'corridor2'
  attribute_name: ''
  function_value: 0.0";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'area'
  instance_name: 'corridor3'
  attribute_name: ''
  function_value: 0.0";

param_type="update_type:
- 0";
param="knowledge:
- knowledge_type: 0
  instance_type: 'homepoint'
  instance_name: 'hp'
  attribute_name: ''
  function_value: 0.0";
# ========= init==============
# ========= init1 attribute_name : robot_at_hp ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'robot_at_hp'
  values:
  - {key: 'v', value: 'ugv'}
  - {key: 'hp', value: 'hp'}
  function_value: 0.0";
# ========= init2 attribute_name : is_checkpoint ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column1'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column10'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column11'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column12'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column13'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column14'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column15'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column16'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column17'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column18'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column19'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'column20'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column1'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint
  values:
  - {key: 'cp', value: 'tri_column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_checkpoint'
  values:
  - {key: 'cp', value: 'tri_column10'}
  function_value: 0.0";
# ========= init2 attribute_name : is_area ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area'
  values:
  - {key: 'ar', value: 'corridor1'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area'
  values:
  - {key: 'ar', value: 'corridor2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area'
  values:
  - {key: 'ar', value: 'corridor3'}
  function_value: 0.0";
# ========= init3 attribute_name : is_area0, is_area1, is_area2 ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column1'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'column10'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column1'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area0'
  values:
  - {key: 'cp', value: 'tri_column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column11'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column12'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column13'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column14'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column15'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area1'
  values:
  - {key: 'cp', value: 'column16'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area2'
  values:
  - {key: 'cp', value: 'column17'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area2'
  values:
  - {key: 'cp', value: 'column18'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area2'
  values:
  - {key: 'cp', value: 'column19'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_area2'
  values:
  - {key: 'cp', value: 'column20'}
  function_value: 0.0";
# ========= init4 attribute_name : is_homepoint ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'is_homepoint'
  values:
  - {key: 'hp', value: 'hp'}
  function_value: 0.0";

# ========= init5 attribute_name : connected_cp ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column1'}
  - {key: 'cp2', value: 'column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column2'}
  - {key: 'cp2', value: 'column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column3'}
  - {key: 'cp2', value: 'column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column4'}
  - {key: 'cp2', value: 'column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column5'}
  - {key: 'cp2', value: 'column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column6'}
  - {key: 'cp2', value: 'column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column7'}
  - {key: 'cp2', value: 'column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column8'}
  - {key: 'cp2', value: 'column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column9'}
  - {key: 'cp2', value: 'column10'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column11'}
  - {key: 'cp2', value: 'column12'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column12'}
  - {key: 'cp2', value: 'column13'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column13'}
  - {key: 'cp2', value: 'column14'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column14'}
  - {key: 'cp2', value: 'column15'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column15'}
  - {key: 'cp2', value: 'column16'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column17'}
  - {key: 'cp2', value: 'column18'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column18'}
  - {key: 'cp2', value: 'column19'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column19'}
  - {key: 'cp2', value: 'column20'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'column16'}
  - {key: 'cp2', value: 'tri_column10'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column10'}
  - {key: 'cp2', value: 'tri_column9'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column9'}
  - {key: 'cp2', value: 'tri_column8'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column8'}
  - {key: 'cp2', value: 'tri_column7'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column7'}
  - {key: 'cp2', value: 'tri_column6'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column6'}
  - {key: 'cp2', value: 'tri_column5'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column5'}
  - {key: 'cp2', value: 'tri_column4'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column4'}
  - {key: 'cp2', value: 'tri_column3'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column3'}
  - {key: 'cp2', value: 'tri_column2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp'
  values:
  - {key: 'cp1', value: 'tri_column2'}
  - {key: 'cp2', value: 'tri_column1'}
  function_value: 0.0";

# ========= init6 attribute_name : connected_cp_ar ==============

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp_ar'
  values:
  - {key: 'cp', value: 'column10'}
  - {key: 'ar', value: 'corridor2'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp_ar'
  values:
  - {key: 'cp', value: 'tri_column10'}
  - {key: 'ar', value: 'corridor1'}
  function_value: 0.0";
# ========= init7 attribute_name : connected_ar_cp ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_ar_cp'
  values:
  - {key: 'ar', value: 'corridor2'}
  - {key: 'cp', value: 'column11'}
  function_value: 0.0";

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_ar_cp'
  values:
  - {key: 'ar', value: 'corridor1'}
  - {key: 'cp', value: 'tri_column9'}
  function_value: 0.0";

# ========= init8 attribute_name : connected_cp_hp ==============

param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_cp_hp'
  values:
  - {key: 'cp', value: 'tri_column6'}
  - {key: 'hp', value: 'hp'}
  function_value: 0.0";

# ========= init2 attribute_name : connected_hp_cp ==============
param_type="$param_type
- 0";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'connected_hp_cp'
  values:
  - {key: 'hp', value: 'hp'}
  - {key: 'cp', value: 'column1'}
  function_value: 0.0";
# ========= goal==============
# ========= goal1 attribute_name : visited_cp ==============
param_type="$param_type
- 1"
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited_cp'
  values:
  - {key: 'wp', value: 'wp$i'}
  function_value: 0.0"

# ========= goal1 attribute_name : visited_cp_hp ==============
param_type="$param_type
- 1";
param="$param
- knowledge_type: 1
  instance_type: ''
  instance_name: ''
  attribute_name: 'visited_cp_hp'
  values:
  - {key: 'cp', value: 'tri_column10'}
  - {key: 'hp', value: 'hp'}
  function_value: 0.0";


