#!/usr/bin/env python3
"""
This script is made for update a tosm-based database manually
"""
from tosm_database_handler import TOSMDatabaseHandler
import rospy
import rospkg
import re

if __name__ == "__main__":
    rospy.init_node("tosm_db_update_node")

    print()
    print("*****TOSM Database Update")
    print()

    tosm = TOSMDatabaseHandler(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))

    # update individuals of Column
    start = rospy.get_rostime().to_sec()
    results = tosm.query_individuals_of_class("Column")
    for item in results:
        id = re.findall(r"\d+", item.name)
        data = {
            "pose" : "[0.0, 0.0, 0.0, 0, 0, 0, 1]"
        }
        tosm.update_individual("Column", id[0], data)

    end = rospy.get_rostime().to_sec()
    print("update individuals time: ", format((end-start)*1000, ".3f"), "[ms]")

    # update individuals of Corridor
    start = rospy.get_rostime().to_sec()
    results = tosm.query_individuals_of_class("Corridor")
    for item in results:
        id = re.findall(r"\d+", item.name)
        data = {
            "boundary" : "[[0, 0], [0, 0], [0, 0], [0, 0], [0, 0]]"
        }
        tosm.update_individual("Corridor", id[0], data)

    end = rospy.get_rostime().to_sec()
    print("update individuals time: ", format((end-start)*1000, ".3f"), "[ms]")

    # save as
    tosm.save_as(rospy.get_param("save_as_owl_file_name"))