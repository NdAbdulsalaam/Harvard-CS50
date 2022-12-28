-- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012

SELECT avg(r.rating)
FROM movies AS m
LEFT JOIN ratings AS r ON m.id = r.movie_id
WHERE m.year = 2012;