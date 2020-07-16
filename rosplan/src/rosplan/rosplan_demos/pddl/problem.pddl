(define (problem task)
(:domain delivery)
(:objects
	wp1 wp2 wp3 wp4 wp5 wp6 wp7 wp8 wp9 wp10 wp11 - waypoint
	lighthouse1 - lighthouse
	airport1 - airport
	sea1 - sea
	driver1 driver2 - driver
	truck1 truck2 - truck
	airplane1 - airplane
	ship1 - ship
	pk1 pk2 pk3 pk4 - packages
)
(:init 
	(connected wp1 wp2)
	(connected wp1 wp4)
	(connected wp1 wp5)
	(connected wp2 wp1)
	(connected wp2 wp3)
	(connected wp2 wp6)
	(connected wp3 wp2)
	(connected wp3 wp8)
	(connected wp4 wp1)
	(connected wp4 wp9)
	(connected wp5 wp1)
	(connected wp5 wp6)
	(connected wp6 wp2)
	(connected wp6 wp5)
	(connected wp6 wp7)
	(connected wp8 wp3)
	(connected wp8 wp11)
	(connected wp9 wp4)
	(connected wp9 wp10)
	(connected wp10 wp9)
	(connected wp10 wp11)
	(connected wp11 wp8)
	(connected wp11 wp10)

	(sea_connected wp7 sea1)
	(sea_connected lighthouse1 sea1)
	(sea_connected sea1 wp7)
	(sea_connected sea1 lighthouse1)
	
	(sky_connected wp2 airport1)
	(sky_connected airport1 wp2)
	(sky_connected wp4 airport1)
	(sky_connected airport1 wp4)


	(= (distance_walk wp1 wp2) 200)
	(= (distance_walk wp1 wp4) 150)
	(= (distance_walk wp1 wp5) 200)
	(= (distance_walk wp2 wp1) 200)
	(= (distance_walk wp2 wp3) 200)
	(= (distance_walk wp2 wp6) 150)
	(= (distance_walk wp3 wp2) 200)
	(= (distance_walk wp3 wp8) 150)
	(= (distance_walk wp4 wp1) 150)
	(= (distance_walk wp4 wp9) 150)
	(= (distance_walk wp5 wp1) 200)
	(= (distance_walk wp5 wp6) 100)
	(= (distance_walk wp6 wp2) 150)
	(= (distance_walk wp6 wp5) 100)
	(= (distance_walk wp6 wp7) 100)
	(= (distance_walk wp8 wp3) 150)
	(= (distance_walk wp8 wp11) 150)
	(= (distance_walk wp9 wp4) 150)
	(= (distance_walk wp9 wp10) 200)
	(= (distance_walk wp10 wp9) 200)
	(= (distance_walk wp10 wp11) 200)
	(= (distance_walk wp11 wp8) 150)
	(= (distance_walk wp11 wp10) 200)

	(= (distance_drive wp1 wp2) 100)
	(= (distance_drive wp1 wp4) 75)
	(= (distance_drive wp1 wp5) 100)
	(= (distance_drive wp2 wp1) 100)
	(= (distance_drive wp2 wp3) 100)
	(= (distance_drive wp2 wp6) 75)
	(= (distance_drive wp3 wp2) 100)
	(= (distance_drive wp3 wp8) 75)
	(= (distance_drive wp4 wp1) 75)
	(= (distance_drive wp4 wp9) 75)
	(= (distance_drive wp5 wp1) 100)
	(= (distance_drive wp5 wp6) 50)
	(= (distance_drive wp6 wp2) 75)
	(= (distance_drive wp6 wp5) 50)
	(= (distance_drive wp6 wp7) 50)
	(= (distance_drive wp8 wp3) 75)
	(= (distance_drive wp8 wp11) 75)
	(= (distance_drive wp9 wp4) 75)
	(= (distance_drive wp9 wp10) 100)
	(= (distance_drive wp10 wp9) 100)
	(= (distance_drive wp10 wp11) 100)
	(= (distance_drive wp11 wp8) 75)
	(= (distance_drive wp11 wp10) 100)

	(= (distance wp7 sea1) 30)
	(= (distance lighthouse1 sea1) 60)
	(= (distance sea1 wp7) 30)
	(= (distance sea1 lighthouse1) 60)

	(= (distance wp2 airport1) 10)
	(= (distance wp4 airport1) 20)

	(at driver1 wp1)
	(at driver2 wp4)
	(at truck1 wp6)
	(at truck2 wp9)

	(at airplane1 airport1)
	(at ship1 sea1)

	(at pk1 wp2)
	(at pk2 wp3)
	(at pk3 wp5)
	(at pk4 wp11)

)

(:goal (and
	(unloaded pk1 wp4)
	(unloaded pk2 wp10)
	(unloaded pk4 wp1)
	(unloaded pk3 lighthouse1)
))

)
