(define (domain turtlebot_demo)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	object 
	robot
)

(:predicates
	(robot_at ?v - robot ?obj - object)
	(connected ?from ?to - object)
	(visited ?v - robot ?wp - object)
)


;; Move between any two waypoints, avoiding terrain
(:durative-action goto_waypoint
	:parameters (?v - robot ?from ?to - object)
	:duration ( = ?duration 10)
	:condition (and
		(at start (robot_at ?v ?from))
		(at start (connected ?from ?to)))
	:effect (and
		(at end (visited ?v ?to))
		(at start (not (robot_at ?v ?from)))
		(at end (robot_at ?v ?to)))
)
)
