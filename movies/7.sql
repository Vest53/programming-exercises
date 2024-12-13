SELECT title, imdb_rating
FROM movies
WHERE release_year = 2010 AND imdb_rating IS NOT NULL
ORDER BY imdb_rating DESC, title ASC;
