-- In 7.sql, write a SQL query that returns the average energy of songs that are by Drake

SELECT avg(s.energy)
FROM songs AS s
LEFT JOIN artists AS a ON s.artist_id == a.id
WHERE a.name == "Drake";