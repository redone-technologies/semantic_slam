#!/usr/bin/env python3
from tosm_database_handler import TOSMDatabaseHandler
from tosm_database_sparql import TOSMDatabaseSPARQL
import rospy
import rospkg
import re
import pandas as pd
from std_msgs.msg import Int32


if __name__ == "__main__":
    rospy.init_node("redone_db_interface")

    print()
    print("*****TOSM Database Handler tosm")
    print()
    pub = rospy.Publisher('plan_sequency_state', Int32, queue_size=1)

    tosm = TOSMDatabaseHandler(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))
    tosm_sq = TOSMDatabaseSPARQL(rospy.get_param("owl_file_name"), rospy.get_param("owl_file_path"))


    # query s and o related with isConnectedTo (using SPQRQL)
    resultsList = tosm_sq.query_connected_places()

    print()
    print("******** Query places using isConnectedTo property")
    print()

    con = open(rospy.get_param("db_result_outdir")+"Connected.txt", 'w')
    bou = open(rospy.get_param("db_result_outdir")+"Boundary.txt", 'w')

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)

        bs = tosm.query_individual(s).boundary[0]
        bo = tosm.query_individual(o).boundary[0]

        lst1 = bs
        lst2 = bo
        count_1 = lst1.count("]")-1
        count_2 = lst2.count("]")-1
        bs_re = bs.replace('[','').replace(']','').replace(' ','')
        bo_re = bo.replace('[','').replace(']','').replace(' ','')

       
        # con.write("(connected " + s + " " + o + ")\n")
        con.write(s + "," + o + "\n")

        bou.write(s + "," + str(count_1) + "," + bs_re + "\n")
        bou.write(o + "," + str(count_2) + "," + bo_re + "\n")

        print("Connected " + s + " " + o)
        print(tosm.query_individual(s).name, "boundary: ", tosm.query_individual(s).boundary[0])
        print(tosm.query_individual(o).name, "boundary: ", tosm.query_individual(o).boundary[0])
        print()

    con.close()
    bou.close()



    resultsList = tosm_sq.query_leaf_places()
    print()
    print("******** Query places using leaf places property")
    print()
    pla = open(rospy.get_param("db_result_outdir")+"Placename.txt", 'w')
    
    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        pla.write(s + "\n")

        # print("LeafPlace : " + s)
    pla.close()
    


    resultsList = tosm_sq.query_places("isInsideOf")
    print()
    print("******** Query places using isInsideOf property")
    print()

    insideof = open(rospy.get_param("db_result_outdir")+"Insideof.txt", 'w')

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)

        # if s == 'building1':
        #     continue

        # insideof.write("(isInsideOf " + s + " " + o + ")\n")
        insideof.write(s + "," + o + "\n")
        # print(s + "  isInsideOf  " + o)
        # print(tosm.query_individual(s).name, "boundary: ", tosm.query_individual(s).boundary[0])
        # print(tosm.query_individual(o).name, "boundary: ", tosm.query_individual(o).boundary[0])
        # print()

    insideof.close()



    doorinfo = open(rospy.get_param("db_result_outdir")+"doorinfo.txt", 'w')
    print()
    print("******** Query doors which are inside of doorways")
    print()
    resultsList = tosm_sq.qeury_door_insideOf_doorway()

    for item in resultsList:
        s = str(item['s'].toPython())
        s = re.sub(r'.*#',"",s)

        o = str(item['o'].toPython())
        o = re.sub(r'.*#', "", o)


        cs = tosm.query_individual(s).size[0]
        cs_re = cs.replace('[','').replace(']','')
        
        cp = tosm.query_individual(s).pose[0]
        cp_re = cp.replace('[','').replace(']','')
        

        doorinfo.write(o + "," + tosm.query_individual(o).availableTime[0] + "," + cs_re + "," + cp_re + "\n")


        # hingeddoor39  isInsideOf  doorway39
        # doorway39 available time:  ['0, 24']
        # hingeddoor39 size:  ['[0.0]']

        print(s + "  isInsideOf  " + o)
        print(tosm.query_individual(o).name, "available time: ", tosm.query_individual(o).availableTime)
        print(tosm.query_individual(o).availableTime[0])
        print(tosm.query_individual(s).name, "size: ", tosm.query_individual(s).size)
        print(tosm.query_individual(s).size[0])
        print(tosm.query_individual(s).name, "pose: ", tosm.query_individual(s).pose)
        
        print()
    doorinfo.close()


  
        
    done = 1
    pub.publish(done)

