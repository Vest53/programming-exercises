SELECT m.title
FROM movies m
JOIN directors d1 ON m.id = d1.movie_id
JOIN people p1 ON d1.person_id = p1.id
JOIN directors d2 ON m.id = d2.movie_id
JOIN people p2 ON d2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';
