```
The robot will figure out a path from point S to point G in the given maze using A* pathfinding algorithm.

Problem detail:

One challenge in robotics is called path planning. This is the process of the robot figuring out how to navigate between two points within some environment. In this problem we will implement a simplified path planning algorithm for a robot moving about a simple 2D environment - a rectangular room with obstacles.

We will represent a simple 2D environment as a grid of ASCII characters. 

Aspects of the environment are represented by different symbols:

= (equal) : Wall or Obstacle within the environment. The robot cannot pass obstacles
. (dot) : Empty/Open Space.
S : The start position of the robot
G : The goal point that the robot is trying to reach.

Each location in the environment is indexed by a (col, row) co-ordinate. The top-left corner of the environment

is always the co-ordinate (0,0), the col-coordinate increases right-wards, and the row-coordinate increases downwards. For the above environment, the four corners have the following co-ordinates:
(0,0) . . (9,0)
  .   . ,   ,
  .   . ,   ,
(0,8) . . (9,8)

Two dimensional environments can be designed in different ways. For this project we will use environments where:

1. There is one goal (ending) point denoted by character &quot;G&quot;.

2. The environment is always surrounded by walls.

3. The environment can contain junctions, corridors &quot;open&quot; space, loops or islands.

As for the robot, we have these following assumptions:

• The robot knows the map of the whole environment it is in at the start.

• Robot can only be located at cells marked as empty/open spaces.

• It may not be possible for the robot to reach every empty space.

• The robot can move to any one of 4 cells, that are to the left, right, up, or down from the robots

originating cell. Robot cannot move diagonally.

• The direction the robot is facing is ignored.
```