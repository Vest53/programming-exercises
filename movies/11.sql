SELECT m.title
FROM movies m
JOIN directors d ON m.id = d.movie_id
JOIN people p ON d.person_id = p.id
WHERE p.name = 'Chadwick Boseman'
ORDER BY m.id DESC  -- Ajuste
