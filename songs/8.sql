-- In 8.sql, write a SQL query that lists the names of the songs that feature other artists

SELECT s.name
FROM songs AS s
LEFT JOIN artists AS a ON s.artist_id == a.id
WHERE s.name LIKE '%feat.%';