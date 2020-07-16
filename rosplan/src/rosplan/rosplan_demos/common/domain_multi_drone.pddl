(define (domain turtlebot_demo)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions :equality)

(:types
	waypoint 
	auv agv - robot
	object
)

(:predicates
	(robot_at ?v - robot ?wp - waypoint)
	(object_at ?obj - object ?wp - waypoint)
	(is_indoor ?wp - waypoint)
	(is_outdoor ?wp - waypoint)
	(is_street ?wp - waypoint)
	(is_sky ?wp - waypoint)
	(visited ?wp - waypoint)
	(detected ?obj - object)
)

(:functions
	(distance ?wp1 ?wp2 - waypoint) 
)

;; Move between any two waypoints, avoiding terrain
(:durative-action goto_waypoint0
	:parameters (?v - robot ?from ?to - waypoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 300)
	:condition (and
		(at start (is_indoor ?from))
		(at start (is_indoor ?to))
		(at start (robot_at ?v ?from)))
	:effect (and
		(at start (not (robot_at ?v ?from)))
		(at end (visited ?to))
		(at end (robot_at ?v ?to)))
)

(:durative-action goto_waypoint1
	:parameters (?v - robot ?from ?to - waypoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 300)
	:condition (and
		(at start (is_outdoor ?from))
		(at start (is_outdoor ?to))
		(at start (robot_at ?v ?from)))
	:effect (and
		(at start (not (robot_at ?v ?from)))
		(at end (visited ?to))
		(at end (robot_at ?v ?to)))
)

(:durative-action goto_waypoint2
	:parameters (?v - robot ?from ?to - waypoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 300)
	:condition (and
		(at start (is_street ?from))
		(at start (is_street ?to))
		(at start (robot_at ?v ?from)))
	:effect (and
		(at start (not (robot_at ?v ?from)))
		(at end (visited ?to))
		(at end (robot_at ?v ?to)))
)

(:durative-action fly
	:parameters (?v - robot ?from ?to - waypoint)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 300)
	:condition (and
		(at start (is_sky ?from))
		(at start (is_sky ?to))
		(at start (robot_at ?v ?from)))
	:effect (and
		(at start (not (robot_at ?v ?from)))
		(at end (visited ?to))
		(at end (robot_at ?v ?to)))
)

(:durative-action detect
	:parameters (?v - robot ?wp - waypoint ?obj - object)
	;;:duration ( = ?duration (distance ?from ?to))
	:duration ( = ?duration 10)
	:condition (and
		(at start (robot_at ?v ?wp))
		(at start (visited ?wp))
		(at start (object_at ?obj ?wp)))
	:effect (and
		(at end (detected ?obj)))
)


)