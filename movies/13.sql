-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

SELECT name
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (
		SELECT movies.id
		FROM movies
		JOIN people ON stars.person_id = people.id
		JOIN stars ON stars.movie_id = movies.id
		WHERE people.name = "Kevin Bacon"
			AND people.birth = 1958
		)
	AND people.name != "Kevin Bacon";