SELECT DISTINCT p.name
FROM people p
JOIN directors d ON p.id = d.person_id
JOIN movies m ON d.movie_id = m.id
JOIN directors kb_d ON m.id = kb_d.movie_id
JOIN people kb ON kb_d.person_id = kb.id
WHERE kb.name = 'Kevin Bacon' AND kb.birth = 1958 AND p.name != 'Kevin Bacon';
