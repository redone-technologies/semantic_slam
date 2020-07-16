(define (problem task)
(:domain turtlebot_demo)
(:objects
    tri_column6 column17 column5 column2 column8 column18 column12 tri_column7 column3 tri_column3 column16 tri_column1 tri_column9 tri_column10 column19 column4 column11 tri_column4 column15 tri_column2 column9 tri_column8 column20 column14 column6 tri_column5 column1 column13 column10 column7 - checkpoint
    ugv - robot
    kdj_hall - object
    corridor1 corridor2 corridor3 - area
    hp - homepoint
)
(:init


    (robot_at_hp ugv hp)

    (object_at kdj_hall column15)

    (is_area corridor1)
    (is_area corridor2)
    (is_area corridor3)

    (is_area0 column1)
    (is_area0 column10)
    (is_area0 column2)
    (is_area0 column3)
    (is_area0 column4)
    (is_area0 column5)
    (is_area0 column6)
    (is_area0 column7)
    (is_area0 column8)
    (is_area0 column9)
    (is_area0 tri_column1)
    (is_area0 tri_column3)
    (is_area0 tri_column4)
    (is_area0 tri_column5)
    (is_area0 tri_column6)
    (is_area0 tri_column7)
    (is_area0 tri_column8)
    (is_area0 tri_column9)

    (is_area1 column11)
    (is_area1 column12)
    (is_area1 column13)
    (is_area1 column14)
    (is_area1 column15)
    (is_area1 column16)

    (is_area2 column17)
    (is_area2 column18)
    (is_area2 column19)
    (is_area2 column20)

    (is_checkpoint column1)
    (is_checkpoint column10)
    (is_checkpoint column11)
    (is_checkpoint column12)
    (is_checkpoint column13)
    (is_checkpoint column14)
    (is_checkpoint column15)
    (is_checkpoint column16)
    (is_checkpoint column17)
    (is_checkpoint column18)
    (is_checkpoint column19)
    (is_checkpoint column2)
    (is_checkpoint column20)
    (is_checkpoint column3)
    (is_checkpoint column4)
    (is_checkpoint column5)
    (is_checkpoint column6)
    (is_checkpoint column7)
    (is_checkpoint column8)
    (is_checkpoint column9)
    (is_checkpoint tri_column1)
    (is_checkpoint tri_column10)
    (is_checkpoint tri_column2)
    (is_checkpoint tri_column3)
    (is_checkpoint tri_column4)
    (is_checkpoint tri_column5)
    (is_checkpoint tri_column6)
    (is_checkpoint tri_column7)
    (is_checkpoint tri_column8)
    (is_checkpoint tri_column9)

    (is_homepoint hp)







    (connected_cp column1 column2)
    (connected_cp column11 column12)
    (connected_cp column12 column13)
    (connected_cp column13 column14)
    (connected_cp column14 column15)
    (connected_cp column15 column16)
    (connected_cp column16 tri_column10)
    (connected_cp column17 column18)
    (connected_cp column18 column19)
    (connected_cp column19 column20)
    (connected_cp column2 column3)
    (connected_cp column3 column4)
    (connected_cp column4 column5)
    (connected_cp column5 column6)
    (connected_cp column6 column7)
    (connected_cp column7 column8)
    (connected_cp column8 column9)
    (connected_cp column9 column10)
    (connected_cp tri_column10 tri_column9)
    (connected_cp tri_column2 tri_column1)
    (connected_cp tri_column3 tri_column2)
    (connected_cp tri_column4 tri_column3)
    (connected_cp tri_column5 tri_column4)
    (connected_cp tri_column6 tri_column5)
    (connected_cp tri_column7 tri_column6)
    (connected_cp tri_column8 tri_column7)
    (connected_cp tri_column9 tri_column8)

    (connected_cp_ar column10 corridor2)
    (connected_cp_ar tri_column10 corridor1)

    (connected_ar_cp corridor1 tri_column9)
    (connected_ar_cp corridor2 column11)


    (connected_cp_hp tri_column6 hp)

    (connected_hp_cp hp column1)




)
(:goal (and
    (visited_cp column15)
    (detected kdj_hall)
))
)
