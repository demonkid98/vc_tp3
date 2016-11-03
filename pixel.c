#include <stdlib.h>
#include "pixel.h"

float distance(pixel_t p1, pixel_t p2) {
  return (float) 1 / 255 * ((p1.red - p2.red) * (p1.red - p2.red) + (p1.green - p2.green) * (p1.green - p2.green) + (p1.blue - p2.blue) * (p1.blue - p2.blue))
   + (float) 1 / 1024 * ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
