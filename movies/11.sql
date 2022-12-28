-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in,starting with the highest rated

WITH artists
AS (
	SELECT st.movie_id
		,pe.name
	FROM stars AS st
	LEFT JOIN people AS pe ON st.person_id = pe.id
	WHERE pe.name = 'Chadwick Boseman'
	)
	,movie_rating
AS (
	SELECT mo.id
		,mo.title
		,ra.rating
	FROM movies AS mo
	LEFT JOIN ratings AS ra ON mo.id = ra.movie_id
	)
SELECT mr.title
FROM artists AS ar
LEFT JOIN movie_rating AS mr ON ar.movie_id = mr.id
ORDER BY mr.rating DESC limit 5;