# TOSM-based database handler
OWL-based database handler using Owlready2
    
    # How to test
    roslaunch tosm_db_handler sample_test.launch

    # Update tosm-based database manually
    roslaunch tosm_db_handler db_update.launch

    # Database query for ROSPLAN
    roslaunch tosm_db_handler pohang.launch

# To use python3 in ROS
We use an Owlready2 python3 package to handle the ontology-based database. In order to use python3 in ROS, you should install packages as follow.

    sudo apt-get install python3-pip python3-yaml
    sudo pip3 install rospkg catkin_pkg

# Requirements
Python 3.5, Owlready2 0.23, setuptools 41.0.0, rdflib 4.2.2, cython

If you get a warning "owlready2_optimized is not available" when importing owlready2, you should install cython to improve optimization and then reinstall the owlready2 sequentially.

    pip3 install cython
    pip3 install --force-reinstall --no-cache-dir owlready2

# Version history
Version 0.0.1 (May 15, 2020)
- Added database handling APIs (e.g., query individuals, add individuals, update individuals, and save the owl file).
- Added a test python script to explain how to use APIs.
- Todo: Add relationship-related APIs such as handling object property functions.

Version 0.0.2 (May 22, 2020)
- Added a class "TOSMDatabaseSPARQL" which is used for a query with SPARQL.
- Added a test script for testing SPARQL in sample_test.py (isConnectedTo and isInsideOf; only for places)
- Added a database update node to update DB manually in need.
- Todo: Make various SPARQL queires functions.

Version 0.0.3 (July 8, 2020)
- Added TOSM-based database for Pohang (pohang.owl).
- Added a script for rosplan, query_for_rosplan.py (You can test with pohang.launch file).
- Added query function for finding doors which are inside of doorways.
- Todo: Update metric information for pohang.owl (Their values are initialized.)