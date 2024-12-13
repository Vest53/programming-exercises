SELECT m.title
FROM movies m
JOIN movie_cast mc1 ON m.id = mc1.movie_id
JOIN people p1 ON mc1.person_id = p1.id
JOIN movie_cast mc2 ON m.id = mc2.movie_id
JOIN people p2 ON mc2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';
