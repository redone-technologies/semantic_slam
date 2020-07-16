(define (problem task)
(:domain turtlebot)
(:objects
    wp0 wp1 wp2 wp3 - waypoint
    kenny - robot
    i01 i02 i03 - item
)
(:init
    (robot_at kenny wp0)


    (not_localised kenny)


    (docked kenny)

    (dock_at wp0)

    (material_at black wp0)
    (material_at blue wp1)
    (material_at green wp2)
    (material_at white wp3)

    (at 584.559 (material_at red wp0))
    (at 644.559 (not (material_at red wp0)))
    (at 1184.56 (material_at red wp0))
    (at 1244.56 (not (material_at red wp0)))
    (at 1784.56 (material_at red wp0))
    (at 1844.56 (not (material_at red wp0)))
    (at 2384.56 (material_at red wp0))
    (at 2444.56 (not (material_at red wp0)))
    (at 2984.56 (material_at red wp0))
    (at 3044.56 (not (material_at red wp0)))
    (at 3584.56 (material_at red wp0))
    (at 3644.56 (not (material_at red wp0)))
    (at 4184.56 (material_at red wp0))
    (at 4244.56 (not (material_at red wp0)))
    (at 4784.56 (material_at red wp0))
    (at 4844.56 (not (material_at red wp0)))




    (not_busy)




    (= (carrying kenny black) 0)
    (= (carrying kenny blue) 0)
    (= (carrying kenny green) 0)
    (= (carrying kenny white) 0)

    (= (requires i01 black) 1)
    (= (requires i02 black) 1)
    (= (requires i03 black) 1)
    (= (requires i01 blue) 0)
    (= (requires i02 blue) 1)
    (= (requires i03 blue) 1)
    (= (requires i01 green) 0)
    (= (requires i02 green) 0)
    (= (requires i03 green) 0)
    (= (requires i01 red) 1)
    (= (requires i02 red) 0)
    (= (requires i03 red) 1)
    (= (requires i01 white) 1)
    (= (requires i02 white) 0)
    (= (requires i03 white) 1)


)
(:goal (and
    (complete i01 wp1)
    (complete i02 wp1)
    (complete i03 wp1)
))
(:metric minimize total_distance)
)
