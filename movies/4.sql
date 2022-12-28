--  In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.

SELECT COUNT(*)
FROM movies AS m
LEFT JOIN ratings AS r ON m.id = r.movie_id
WHERE r.rating = 10;