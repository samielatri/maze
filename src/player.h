/*
* Player structure representing a player.
* The player has an x and y coordinates.
* He has a widht and height.
* He can rotate (go left or right) by a certain angle and, also, walk. 
* Therefore, he has rotationDirection, rotationAngle and walkDirection,
* as well as walkSpeed and turnSpeed.
* 
*/
struct Player {
  float x;
  float y;
  float width;
  float height;
  int rotationDirection;  // left or right : -1 to go left, +1 to go right
  int walkDirection;  // forward or backward : -1 to go backward, +1 to go forward
  float rotationAngle;  // by how many degrees i rotate
  float walkSpeed;
  float turnSpeed;
}

typedef struct Player player;
