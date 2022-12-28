-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Confirm that the incident took place on July 28, 2021 and that it took place on Humphrey Street.
-- Retrive the id for reporting purpose
SELECT id
	,description
FROM crime_scene_reports
WHERE year = 2021
	AND month = 7
	AND day = 28
	AND street LIKE '%Humphrey%';

-- POINTS:
-- Crime took place at 10:15am
-- Everyone mentioned bakery
-- Q2: Check for the date of the interview
SELECT name
	,transcript
FROM interviews
WHERE year = 2021
	AND month = 7
	AND day = 28;

-- POINTS:
-- One of the thieves withdrew money from the ATM on Leggett Street ealier that morning
-- They left the bakery about 10:25am (10 minutes later after the incident)
-- They plan to leave town with the earliest flight the following morning (from conversation < 60mins at about 10:25am)
-- Q3: Check for the person that used the atm using the info above
-- select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%leggett street%';
WITH bank_details
AS (
	SELECT DISTINCT (pe.name)
	FROM people AS pe
	JOIN bank_accounts AS ba ON pe.id = ba.person_id
	JOIN atm_transactions AS at ON ba.account_number = at.account_number
	WHERE at.account_number IN (
			SELECT account_number
			FROM atm_transactions
			WHERE year = 2021
				AND month = 7
				AND day = 28
				AND atm_location LIKE '%leggett street%'
				AND transaction_type = 'withdraw'
			)
	)
	,phone_details
AS (
	SELECT name
	FROM people
	WHERE phone_number IN (
			SELECT CALLER
			FROM phone_calls
			WHERE year = 2021
				AND month = 7
				AND day = 28
				AND duration < 60
			)
	)
	,car_details
AS (
	SELECT name
	FROM people
	WHERE license_plate IN (
			SELECT license_plate
			FROM bakery_security_logs
			WHERE year = 2021
				AND month = 7
				AND day = 28
				AND activity = 'exit'
				AND minute > 15
				AND minute <= 25
			)
	)
	,flight_details
AS (
	SELECT name
		,fl.origin_airport_id
		,fl.destination_airport_id
	FROM people AS pe
	JOIN passengers AS pa ON pe.passport_number = pa.passport_number
	JOIN flights AS fl ON pa.flight_id = fl.id
	JOIN airports AS ai ON fl.origin_airport_id = ai.id
	WHERE fl.id IN (
			SELECT id
			FROM flights
			WHERE year = 2021
				AND month = 7
				AND day = 29
			ORDER BY hour limit 1
			)
		AND origin_airport_id IN (
			SELECT id
			FROM airports
			WHERE city = 'Fiftyville'
			)
	)
	,origin_airport
AS (
	SELECT *
	FROM airports
	WHERE id IN (
			SELECT fl.origin_airport_id
			FROM flights AS fl
			-- JOIN flights AS fl ON pa.flight_id = fl.id
			JOIN airports AS ai ON fl.origin_airport_id = ai.id
			WHERE fl.id IN (
					SELECT id
					FROM flights
					WHERE year = 2021
						AND month = 7
						AND day = 29
					ORDER BY hour limit 1
					)
			)
	)
	,destination_airport
AS (
	SELECT *
	FROM airports
	WHERE id IN (
			SELECT destination_airport_id
			FROM flights AS fl
			-- JOIN flights AS fl ON pa.flight_id = fl.id
			JOIN airports AS ai ON fl.origin_airport_id = ai.id
			WHERE fl.id IN (
					SELECT id
					FROM flights
					WHERE year = 2021
						AND month = 7
						AND day = 29
					ORDER BY hour limit 1
					)
			)
	)
	,suspects
AS (
	SELECT pe.name
		,pe.phone_number
		,fd.*
	FROM people AS pe
	JOIN bank_details AS bd ON pe.name = bd.name
	JOIN phone_details AS pd ON bd.name = pd.name
	JOIN car_details AS cd ON pd.name = cd.name
	JOIN flight_details AS fd ON cd.name = fd.name
	ORDER BY pe.name
	)
-- Format suspest_table output
SELECT sp.name AS caller_name
	-- ,sp.*
	,pe.name AS receiver_name
	,oa.full_name AS origin_airport
	,da.full_name AS destination_airport
	,da.city AS city
	,pc.CALLER AS caller_number
	,pc.receiver AS receiver_name
FROM phone_calls AS pc
	,origin_airport AS oa
	,destination_airport AS da
JOIN suspects AS sp ON sp.phone_number = pc.CALLER
JOIN people AS pe ON pc.receiver = pe.phone_number
WHERE pc.year = 2021
	AND pc.month = 7
	AND pc.day = 28
	AND pc.duration < 60;
-- Result
