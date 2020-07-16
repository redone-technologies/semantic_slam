(define (domain delivery)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	waypoint lighthouse airport sea - place
	driver truck airplane ship - transport
	transport packages place - object
)


(:predicates
	(connected ?pl1 ?pl2 - place)
	(sea_connected ?pl1 ?pl2 - place)
	(sky_connected ?pl1 ?pl2 - place)
	(at ?o1 - object ?o2 - object)
	(loaded  ?pk - packages)
	(unloaded ?pk - packages ?pl - place)
)


(:functions
	(distance_walk ?wp1 ?wp2 - waypoint)
	(distance_drive ?wp1 ?wp2 - waypoint)
	(distance ?p1 ?p2 - place)
)


(:durative-action walk
	:parameters (?d - driver ?from ?to - waypoint)
	:duration ( = ?duration (distance_walk ?from ?to))
	:condition (and
		(at start (connected ?from ?to))
		(at start (at ?d ?from)))
	:effect (and
		(at start (not (at ?d ?from)))
		(at end (at ?d ?to)))
)


(:durative-action drive
	:parameters (?dr - driver ?tk - truck ?from ?to - waypoint)
	:duration ( = ?duration (distance_drive ?from ?to))
	:condition (and
		(at start (connected ?from ?to))
		(at start (at ?dr ?from))
		(at start (at ?tk ?from)))
	:effect (and
		(at start (not (at ?dr ?from)))
		(at start (not (at ?tk ?from)))
		(at end (at ?dr ?to))
		(at end (at ?tk ?to)))
)

(:durative-action sail
	:parameters (?sh - ship ?from ?to - place)
	:duration ( = ?duration (distance ?from ?to))
	:condition (and
		(at start (at ?sh ?from))
		(at start (sea_connected ?from ?to)))
	:effect (and
		(at start (not (at ?sh ?from)))
		(at end (at ?sh ?to)))
)

(:durative-action fly
	:parameters (?ap - airplane ?from ?to - place)
	:duration ( = ?duration (distance ?from ?to))
	:condition (and
		(at start (at ?ap ?from))
		(at start (sky_connected ?from ?to)))
	:effect (and
		(at start (not (at ?ap ?from)))
		(at end (at ?ap ?to)))
)

(:durative-action load
	:parameters (?t - transport ?pk - packages ?pl - place)
	:duration ( = ?duration 10)
	:condition (and
		(over all (at ?t ?pl))
		(at start (at ?pk ?pl)))
	:effect (and
		(at start (not (at ?pk ?pl)))
		(at end (at ?pk ?t))
		(at end (loaded ?pk)))
)

(:durative-action unload
	:parameters (?t - transport ?pk - packages ?pl - place)
	:duration ( = ?duration 10)
	:condition (and
		(over all (at ?t ?pl))
		(at start (at ?pk ?t))
		(at start (loaded ?pk)))
	:effect (and
		(at start (not (at ?pk ?t)))
		(at end (at ?pk ?pl))
		(at start (not (loaded ?pk)))
		(at end (unloaded ?pk ?pl)))
)


)
