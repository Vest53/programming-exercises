SELECT DISTINCT d.name
FROM people d
JOIN movies m ON d.id = m.director_id
WHERE m.imdb_rating >= 9.0;
