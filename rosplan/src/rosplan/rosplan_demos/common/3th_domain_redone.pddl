(define (domain project)

	(:requirements 
	:strips 
	:typing 
	:numeric-fluents 
	:durative-actions 
	:conditional-effects 
	:equality 
	:timed-initial-literals)

	(:types
		robot
		waypoint elevator - place
		corridor doorway room sidewalk staircase	-	waypoint
		floor
		elevator
		building
	)

	(:predicates
		(robot_at 	?r - robot ?p - place)
		(robot_elevator_at 	?r - robot ?p - place ?f - floor)
		(connected	?from ?to - place)
		(isinsideof	?floor - floor ?wp - waypoint)
	)

	(:durative-action goto
		:parameters (?r - robot ?from ?to - waypoint)
		:duration ( = ?duration 60)
		:condition (and
			(at start (robot_at 	?r ?from))
			(over all (connected	?from ?to ))
		)
		:effect (and
			(at start (not (robot_at ?r ?from)))
			(at end   (robot_at ?r ?to))
		)
	)

	(:durative-action enterEV
		:parameters (?r - robot	 ?from - waypoint	?to - elevator ?floor - floor)
		:duration ( = ?duration 60)
		:condition (and
			(at start (robot_at   	?r ?from))
			(over all (isinsideof	?floor  ?from))
			(over all (connected	?from ?to ))
		)
		:effect (and
			(at start (not (robot_at ?r ?from)))
			(at end   (robot_elevator_at ?r ?to ?floor))
		)
	)

	(:durative-action leaveEV
		:parameters (?r - robot ?floor - floor ?from - elevator ?to - waypoint)
		:duration ( = ?duration 60)
		:condition (and
			(at start (robot_elevator_at   ?r ?from ?floor))
			(over all (isinsideof	?floor  ?to))
			(over all (connected	?from 	?to ))
		)
		:effect (and
			(at start (not (robot_elevator_at   ?r ?from ?floor)))
			(at end   (robot_at ?r ?to))
		)
	)

	(:durative-action moveFloor
		:parameters (?r - robot ?from - elevator ?floor1 ?floor2 - floor ?to - waypoint)
		:duration ( = ?duration 60)
		:condition (and
			(at start (robot_elevator_at   ?r ?from ?floor1))
			(over all (isinsideof	?floor2  ?to))
			(over all (connected	?from  ?to))
		)
		:effect (and
			(at start (not (robot_elevator_at   ?r ?from ?floor1)))
			(at end   (robot_elevator_at   ?r ?from ?floor2))
		)
	)	
)
