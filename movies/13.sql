SELECT DISTINCT p.name
FROM people p
JOIN movie_cast mc ON p.id = mc.person_id
JOIN movies m ON mc.movie_id = m.id
JOIN movie_cast kb_mc ON m.id = kb_mc.movie_id
JOIN people kb ON kb_mc.person_id = kb.id
WHERE kb.name = 'Kevin Bacon' AND kb.birth_year = 1958 AND p.name != 'Kevin Bacon';
