SELECT m.title
FROM movies m
JOIN movie_cast mc ON m.id = mc.movie_id
JOIN people p ON mc.person_id = p.id
WHERE p.name = 'Chadwick Boseman'
ORDER BY m.audience_rating DESC
LIMIT 5;
