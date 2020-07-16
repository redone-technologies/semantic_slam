#!/usr/bin/env python3
from tosm_database_handler import TOSMDatabaseHandler
from tosm_database_sparql import TOSMDatabaseSPARQL
import rospy
import rospkg
import re

if __name__ == "__main__":
    rospy.init_node("test")

    print()
    print("*****TOSM Database Handler Test")
    print()

    test = TOSMDatabaseHandler(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))

    # when you find an object (Column)
    # you can compare using query results
    results = test.query_individuals_of_class("Column")    

    for item in results:
        # if matched - True
        if True: 
            # update the pre-registered individuals
            break
    
    # add new individuals (if there is no same object)
    start = rospy.get_rostime().to_sec()
    if True:
        data = {
            "pose" : "[1.0, 2.8, 3.2, 0, 0, 0, 1]",
            "velocity" : "[1, 2, 3, 0, 0, 0]",
            "isKeyObject" : True
        }
        test.add_individual("Column", "101", data)
        data = {
            "pose" : "[11.0, 12.8, 13.2, 0, 0, 0, 1]",
            "velocity" : "[11, 12, 13, 0, 0, 0]",
            "isKeyObject" : True
        }
        test.add_individual("Column", "102", data)
    end = rospy.get_rostime().to_sec()
    print("add individual time: ", format((end-start)*1000, ".3f"), "[ms]")

    # update the individual
    start = rospy.get_rostime().to_sec()
    data = {
        "pose" : "[2.0, 2.0, 3.5, 0, 0, 0, 1]",
        "velocity" : "[10, 20, 30, 0, 0, 0]",
    }
    test.update_individual("Column", "102", data)
    end = rospy.get_rostime().to_sec()
    print("update individual time: ", format((end-start)*1000, ".3f"), "[ms]")

    # delete individual
    #test.delete_individual("column101")

    # save as
    test.save_as(rospy.get_param("save_as_owl_file_name"))

    print()
    print("*****TOSM Database SPARQL Test")
    print()

    test2 = TOSMDatabaseSPARQL(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))

    # query s and o related with isConnectedTo (using SPQRQL)
    resultsList = test2.query_connected_places()

    print()
    print("******** Query places using isConnectedTo property")
    print()

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)
        print(s + "  isConnectedTo  " + o)
        print(test.query_individual(s).name, "boundary: ", test.query_individual(s).boundary[0])
        print(test.query_individual(o).name, "boundary: ", test.query_individual(o).boundary[0])
        print()


    # query s and o related with isInsideOf (using SPQRQL)
    resultsList = test2.query_places("isInsideOf")

    print()
    print("******** Query places using isInsideOf property")
    print()

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)
        print(s + "  isInsideOf  " + o)
        print(test.query_individual(s).name, "boundary: ", test.query_individual(s).boundary[0])
        print(test.query_individual(o).name, "boundary: ", test.query_individual(o).boundary[0])
        print()