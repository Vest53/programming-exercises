SELECT p.name
FROM people p
JOIN movie_cast mc ON p.id = mc.person_id
JOIN movies m ON mc.movie_id = m.id
WHERE m.title = 'Toy Story';
