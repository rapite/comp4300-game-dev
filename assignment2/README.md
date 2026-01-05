# COMP4300 - Assignment2

## Program Specification

Produces a game called "Geometry Wars" where the player runs around to avoid enemy polygons, using a gun to shoot and destroy them as they spawn.

## Engine Architecture
Implementing an Entity Manager utilizing a vector of entities for storage and a map of entities to manage entities for quick retrieval.

## Config Specification
Spawnrate (per # frames)

Window 1280 720 60 0
Font fonts/tech.ttf 24 255 255 255
Player 32 32 5 5 5 5 255 0 0 4 8
Enemy 32 32 3 3 255 255 255 2 3 8 90 60
Bullet 10 10 20 255 255 255 255 255 255 2 20 90

## Entity Manager Specifications
The Entity Manager supports Additon (for preparing entities), Updates (to render entities), 

# Math

### Random acquisition in a range: $r = min + (rand() \\% (1+max-min))$

### Seeding: $srand(time(null)) \ \ \\&\ \ srand(0)$

### Collision Detection
#### (1) Using Sqrt: $\sqrt{D.x * D.x + D.y * D.y} < r1 + r2$
#### (2) Optimization: $DistSq = D.x * D.x + D.y * D.y$
- Collision = $DistSq < (r1+r2)*(r1+r2)$
