-- In 12.sql, write a SQL query to list the titles of all movies in which both
-- Johnny Depp and Helena Bonham Carter starred

SELECT title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp"
	AND title IN (
		SELECT title
		FROM movies
		JOIN stars ON stars.movie_id = movies.id
		JOIN people ON stars.person_id = people.id
		WHERE people.name = "Helena Bonham Carter"
		);