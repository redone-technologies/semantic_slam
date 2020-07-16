(define (domain turtlebot_demo)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions :equality)

(:types
	area
	waypoint 
	auv agv - robot
	object
)

(:predicates
	(robot_at ?v - robot ?wp - waypoint)
	(waypoint_at ?wp - waypoint ?ar - area) 
	(given_area ?v - robot ?ar - area) 
	(object_at ?obj - object ?wp - waypoint)
	(connected ?from ?to - waypoint)
	(visited ?wp - waypoint)
)

(:functions
	(distance ?wp1 ?wp2 - waypoint) 
)

;; Move between any two waypoints, avoiding terrain
(:durative-action goto_waypoint
	:parameters (?v - robot ?ar - area ?from ?to - waypoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 10)
	:condition (and
		;;(at start (connected ?from ?to))
		(at start (given_area ?v ?ar))
		(at start (waypoint_at ?from ?ar))
		(at start (waypoint_at ?to ?ar))
		(at start (robot_at ?v ?from)))
	:effect (and
		(at start (not (robot_at ?v ?from)))
		(at end (visited ?to))
		(at end (robot_at ?v ?to)))
)
)
