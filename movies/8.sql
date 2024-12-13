SELECT p.name
FROM people p
JOIN directors d ON p.id = d.person_id
JOIN movies m ON d.movie_id = m.id
WHERE m.title = 'Toy Story';
