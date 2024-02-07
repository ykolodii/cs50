SELECT COUNT(*)
FROM movies
JOIN ratings ON movie_id = movies.id
WHERE rating = 10.0;
