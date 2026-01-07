# COMP4300 - Assignment2

## Program Specification
Produces a game called "Geometry Wars" where the player runs around to avoid enemy polygons, using a gun to shoot and destroy them as they spawn within a specified sub-box within the game window.

### Score:
- Each time an enemy spawns, it is given a score component of N*100. N = # verticies of shape. Smaller enemies are worth 2x.
- When a player bullet kills an enemy, game score is increased by the corresponding score
- The score is displayed with the font specification on the top left of the screen.

### Controls
- 'WASD' movements
- Mouse to aim, left click to shoot
- 'P' key pauses
- 'ESC' key closes

## Engine Architecture
Implementing an Entity Manager utilizing a vector of entities for storage and a map of entities to manage entities for quick retrieval.

### Drawing
- In the render, all entities are given a slow rotation
- Consider non-game altering special effects.
- Entities possess a lifespan component, measured in frames. After a set amount of frames, the alpha value of the entity decreases, eventually disappearing until it is no longer alive.

## Config Specification
The config file suggests window size, font format, player specification, enemy specification, bullet specification with the following syntax:
- Window Width Height FrameLimit FullScreen-bit
- Font File Size (R G B)
- Player Shape-Radius Collision-Radius Speed FillColor(F-RGB) OutlineColor(O-RGB) OutlineThickness(OT) ShapeVertices
- Enemy ShapeRadius CollisionRadius SpeedMin SpeedMax F-RGB O-RGB OT MinVertices MaxVertices SpawnInterval
- Bullet ShapeRadius CollisionRadius Speed F-RGB O-RGB OT V Lifespan

### Example:
Window 1280 720 60 0\
Font fonts/tech.ttf 24 255 255 255\
Player 32 32 5 5 5 5 255 0 0 4 8\
Enemy 32 32 3 3 255 255 255 2 3 8 90 60\
Bullet 10 10 20 255 255 255 255 255 255 2 20 90\

# Math
### Randomization within a range: $r = min + (rand() \\% (1+max-min))$
### Seeding: $srand(time(null)) \ \ \\&\ \ srand(0)$
### Collision Detection
#### (1) Using Sqrt: $\sqrt{D.x * D.x + D.y * D.y} < r1 + r2$
#### (2) Optimization: $DistSq = D.x * D.x + D.y * D.y$
- Collision = $DistSq < (r1+r2)*(r1+r2)$
