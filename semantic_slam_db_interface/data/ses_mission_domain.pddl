(define (domain turtlebot_demo)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions :equality)

(:types
	checkpoint 
	robot
	object
	area
	homepoint
)

(:predicates
	(robot_at_cp ?v - robot ?cp - checkpoint)
	(robot_at_ar ?v - robot ?ar - area)
	(robot_at_hp ?v - robot ?hp - homepoint)
	(object_at ?obj - object ?cp - checkpoint)

	(is_area ?ar - area)
	(is_area0 ?cp - checkpoint)
	(is_area1 ?cp - checkpoint)
	(is_area2 ?cp - checkpoint)
	(is_checkpoint ?cp - checkpoint)
	(is_homepoint ?hp - homepoint)

	(visited_cp ?cp - checkpoint)
	(visited_ar ?ar - area)
	(visited_cp_ar ?cp - checkpoint ?ar - area)
	(visited_ar_cp ?ar - area ?cp - checkpoint)
	(visited_cp_hp ?cp - checkpoint ?hp - homepoint)
	(visited_hp_cp ?hp - homepoint ?cp - checkpoint)

	(connected_cp ?cp1 ?cp2 - checkpoint)
	(connected_cp_ar ?cp - checkpoint ?ar - area)
	(connected_ar_cp ?ar - area ?cp - checkpoint)
	(connected_ar ?ar1 ?ar2 - area)
	(connected_cp_hp ?cp - checkpoint ?hp - homepoint)
	(connected_hp_cp ?hp - homepoint ?cp - checkpoint)
	(connected_obj ?obj - object ?cp - checkpoint)
	
	(detected ?obj - object)
)

(:functions
	(distance ?cp1 ?cp2 - checkpoint)
)

;; action1 : Move between any two checkpoint, avoiding obstacle

(:durative-action goto_area1_cp
	:parameters (?v - robot ?from ?to - checkpoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (connected_cp ?from ?to))
		(at start (is_area0 ?from))
		;;(at start (is_area0 ?to))
		(at start (robot_at_cp ?v ?from)))
	:effect (and
		(at start (not (robot_at_cp ?v ?from)))
		(at end (visited_cp ?to))
		(at end (robot_at_cp ?v ?to)))
) 

(:durative-action goto_area2_cp
	:parameters (?v - robot ?from ?to - checkpoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (connected_cp ?from ?to))	
		(at start (is_area1 ?from))
		;;(at start (is_area1 ?to))
		(at start (robot_at_cp ?v ?from)))
	:effect (and
		(at start (not (robot_at_cp ?v ?from)))
		(at end (visited_cp ?to))
		(at end (robot_at_cp ?v ?to)))
) 

(:durative-action goto_area3_cp
	:parameters (?v - robot ?from ?to - checkpoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (connected_cp ?from ?to))	
		(at start (is_area2 ?from))
		;;(at start (is_area1 ?to))
		(at start (robot_at_cp ?v ?from)))
	:effect (and
		(at start (not (robot_at_cp ?v ?from)))
		(at end (visited_cp ?to))
		(at end (robot_at_cp ?v ?to)))
) 

;; action3 : Move from wp to area, avoiding obstacle	
(:durative-action goto_cp_to_area
	:parameters (?v - robot ?from - checkpoint ?to - area)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (connected_cp_ar ?from ?to))
		(at start (is_area ?to))
		(at start (robot_at_cp ?v ?from)))
	:effect (and
		(at start (not (robot_at_cp ?v ?from)))
		(at end (visited_cp_ar ?from ?to))
		(at end (robot_at_ar ?v ?to)))
)

;; action4 : Move from wp to area, avoiding obstacle	
(:durative-action goto_area_to_cp
	:parameters (?v - robot ?from - area ?to - checkpoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (connected_ar_cp ?from ?to))
		(at start (is_checkpoint ?to))
		(at start (robot_at_ar ?v ?from)))
	:effect (and
		(at start (not (robot_at_ar ?v ?from)))
		(at end (visited_ar_cp ?from ?to))
		(at end (robot_at_cp ?v ?to)))
)

(:durative-action goto_hp_to_cp
	:parameters (?v - robot ?from - homepoint ?to - checkpoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and 		
		(at start (connected_hp_cp ?from ?to))
		(at start (is_homepoint ?from))
		(at start (robot_at_hp ?v ?from)))
	:effect (and
		(at start (not (robot_at_hp ?v ?from)))
		(at end (visited_hp_cp ?from ?to))
		(at end (robot_at_cp ?v ?to)))
)

;; action2 : Move between any two area, avoiding obstacle	
(:durative-action return_to_charge
	:parameters (?v - robot ?from - checkpoint ?to - homepoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and 		
		(at start (connected_cp_hp ?from ?to))
		(at start (is_checkpoint ?from))
		(at start (robot_at_cp ?v ?from)))
	:effect (and
		(at start (not (robot_at_cp ?v ?from)))
		(at end (visited_cp_hp ?from ?to))
		(at end (robot_at_hp ?v ?to)))
)

(:durative-action detect
	:parameters (?v - robot ?cp - checkpoint ?obj - object)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 100)
	:condition (and
		(at start (robot_at_cp ?v ?cp))
		(at start (visited_cp ?cp))
		(at start (object_at ?obj ?cp)))
	:effect (and
		(at end (detected ?obj)))
		
)

)
