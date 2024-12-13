SELECT m.title
FROM movies m
JOIN ratings r ON m.id = r.movie_id
WHERE m.id IN (
    SELECT movie_id
    FROM directors d
    WHERE d.person_id = (
        SELECT id
        FROM people p
        WHERE p.name = 'Chadwick Boseman'
    )
)
ORDER BY r.rating DESC
LIMIT 5;  -- Ajuste o limite conforme necessário
