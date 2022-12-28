-- In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year

WITH artists
AS (
	SELECT p.name
		,p.birth
		,s.movie_id
	FROM people AS p
	LEFT JOIN stars AS s ON p.id = s.person_id
	WHERE p.birth IS NOT NULL
	)
SELECT DISTINCT (a.name)
FROM movies AS m
LEFT JOIN artists AS a ON m.id = a.movie_id
WHERE m.year = 2004
ORDER BY a.birth;