#include "utils/utils.h"
#include "math.h"
float getVectorDistance(Vector2 p1, Vector2 p2) {
  return hypot(fabs(p1.x - p2.x), fabs(p1.y - p2.y));
}
int clamp(int val, int min, int max) {
  return val < min ? min : (val > max ? max : val);
}
