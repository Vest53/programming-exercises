SELECT m.title
FROM movies m
WHERE m.id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id IN (
        SELECT id
        FROM people
        WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
    )
    GROUP BY movie_id
    HAVING COUNT(DISTINCT person_id) = 2
);
