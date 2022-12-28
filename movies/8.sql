-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story
WITH artists
AS (
	SELECT p.name
		,s.movie_id
	FROM people AS p
	LEFT JOIN stars AS s ON p.id = s.person_id
	)
SELECT a.name
FROM movies AS m
LEFT JOIN artists AS a ON m.id = a.movie_id
WHERE m.title = 'Toy Story';