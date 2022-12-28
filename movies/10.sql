-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0

WITH artists
AS (
	SELECT p.name
		,d.movie_id
	FROM directors AS d
	LEFT JOIN people AS p ON d.person_id = p.id
	)
SELECT DISTINCT (a.name)
FROM artists AS a
LEFT JOIN ratings AS r ON a.movie_id = r.movie_id
WHERE r.rating >= 9.0;