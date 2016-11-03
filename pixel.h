typedef struct pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned int x;
  unsigned int y;
} pixel_t;

int distance(pixel_t p1, pixel_t p2);
