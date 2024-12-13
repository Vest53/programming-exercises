SELECT DISTINCT p.name
FROM people p
JOIN movie_cast mc ON p.id = mc.person_id
JOIN movies m ON mc.movie_id = m.id
WHERE m.release_year = 2004
ORDER BY p.birth_year;
