#!/usr/bin/env python3
from tosm_database_handler import TOSMDatabaseHandler
from tosm_database_sparql import TOSMDatabaseSPARQL
import rospy
import rospkg
import re

if __name__ == "__main__":
    rospy.init_node("tosm_db_handler")

    print()
    print("*****TOSM Database Handler Test")
    print()

    tosm = TOSMDatabaseHandler(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))
    tosm_sq = TOSMDatabaseSPARQL(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))

    print()
    print("*****TOSM Database SPARQL for ROSPLAN")
    print()

    #query s and o related with isConnectedTo (using SPQRQL)
    print()
    print("******** Query places using isConnectedTo property")
    print()
    resultsList = tosm_sq.query_connected_places()

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)
        print(s + "  isConnectedTo  " + o)
        print(tosm.query_individual(s).name, "boundary: ", tosm.query_individual(s).boundary[0])
        print(tosm.query_individual(o).name, "boundary: ", tosm.query_individual(o).boundary[0])
        print()

    #query s and o related with isInsideOf (using SPQRQL)
    print()
    print("******** Query doors which are inside of doorways")
    print()
    resultsList = tosm_sq.qeury_door_insideOf_doorway()

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)
        print(s + "  isInsideOf  " + o)
        print(tosm.query_individual(o).name, "available time: ", tosm.query_individual(o).availableTime)
        print(tosm.query_individual(s).name, "size: ", tosm.query_individual(s).size)
        print()
