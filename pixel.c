#include <stdlib.h>
#include "pixel.h"

int distance(pixel_t p1, pixel_t p2) {
  return (p1.red - p2.red) * (p1.red - p2.red) + (p1.green - p2.green) * (p1.green - p2.green) + (p1.blue - p2.blue) * (p1.blue - p2.blue)
   + (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
