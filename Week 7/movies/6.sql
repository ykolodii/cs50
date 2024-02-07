SELECT AVG(rating)
FROM movies
JOIN ratings ON movie_id = movies.id
WHERE year = 2012;
