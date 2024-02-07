SELECT title, rating
FROM movies
JOIN ratings ON movie_id = movies.id
WHERE year = 2010 AND rating IS NOT NULL
ORDER BY rating DESC, title;
