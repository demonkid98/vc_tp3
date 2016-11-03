#include <stdlib.h>
#include "pixel.h"

int distance(pixel_t p1, pixel_t p2) {
  return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue);
}
