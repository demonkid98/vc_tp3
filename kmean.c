#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Util.h"
#include "pixel.h"

int assign_cluster(pixel_t p, pixel_t *centers, int num_clusters) {
  int min_dist = INT_MAX;
  int cluster_id = -1;
  for (int i = 0; i < num_clusters; i++) {
    int dist = distance(p, centers[i]);
    if (dist < min_dist) {
      min_dist = dist;
      cluster_id = i;
    }
  }

  return cluster_id;
}


int main(int argc, char* argv[]) {
  FILE* ifp;
  pixel_t *pixels;
  int ich1, ich2, rows, cols, bitcols, maxval=255, is_raw;
  int num_clusters;
  int i, j;
  int *cluster_size;
  unsigned char *out;

  /* Arguments */
  if ( argc != 3 ){
    printf("\nUsage: %s file \n\n", argv[0]);
    exit(0);
  }

  // num_clusters = atoi(argv[2]);
  num_clusters = 3;
  pixel_t *centers = malloc(num_clusters * sizeof(pixel_t));
  pixel_t **clusters;

  // hand-picked centers
  centers[0].red = 255;
  centers[0].green = 105;
  centers[0].blue = 208;

  centers[1].red = 211;
  centers[1].green = 219;
  centers[1].blue = 22;

  centers[2].red = 0;
  centers[2].green = 0;
  centers[2].blue = 0;

  /* Opening */
  ifp = fopen(argv[1],"r");
  if (ifp == NULL) {
    printf("error in opening file %s\n", argv[1]);
    exit(1);
  }

  /*  Magic number reading */
  ich1 = getc( ifp );
  if ( ich1 == EOF )
      pm_erreur( "EOF / read error / magic number" );
  ich2 = getc( ifp );
  if ( ich2 == EOF )
      pm_erreur( "EOF /read error / magic number" );
  if(ich2 != '3' && ich2 != '6')
    pm_erreur(" wrong file type ");
  else
    if(ich2 == '3')
      is_raw = 0;
    else is_raw = 1;

  /* Reading image dimensions */
  cols = pm_getint( ifp );
  rows = pm_getint( ifp );
  bitcols = cols * 3;
  maxval = pm_getint( ifp );

  /* Memory allocation  */
  out = malloc (bitcols * rows *sizeof(unsigned char));
  pixels = malloc(cols * rows * sizeof(pixel_t));
  clusters = malloc(num_clusters * sizeof(pixel_t *));
  for (i = 0; i < num_clusters; i++) {
    clusters[i] = malloc(rows * cols * sizeof(pixel_t));
  }
  cluster_size= malloc(num_clusters * sizeof(int) );



  /* Reading */
  for(i=0; i < rows; i++) {
    for(j=0; j < cols; j++) {
      pixel_t pixel;
      if(is_raw) {
        pixel.red = pm_getrawbyte(ifp);
        pixel.green = pm_getrawbyte(ifp);
        pixel.blue = pm_getrawbyte(ifp);
      } else {
        pixel.red = pm_getint(ifp);
        pixel.green = pm_getint(ifp);
        pixel.blue = pm_getint(ifp);
      }
      pixel.x = i;
      pixel.y = j;
      pixels[i * cols + j] = pixel;
    }
  }




for (int z=0;z<10;z++)
{

for(i=0;i<num_clusters;i++)
    cluster_size[i]=0;

  // Assing point to cluster

for(i= 0;i < rows* cols;i++){

 int id= assign_cluster(pixels[i],centers, num_clusters);
 int current_size=cluster_size[id];
 clusters[id][current_size] = pixels[i];
 cluster_size[id]++;

}

//Find the new center

for (i=0; i< num_clusters ; i++){
  int red,blue,green;
  pixel_t mean;

for(j=0; j< cluster_size[i];j++)
{
  red+= clusters[i][j].red;
  blue+= clusters[i][j].blue;
  green+= clusters[i][j].green;
}

red /= cluster_size[i];
blue /= cluster_size[i];
green /= cluster_size[i];

  mean.red = red;
  mean.blue = blue;
  mean.green = green;

  centers[i]=mean;
}


}
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < cluster_size[i]; j++) {
      int x = clusters[i][j].x;
      int y = clusters[i][j].y;

      out[x * bitcols + y * 3] = centers[i].red;
      out[x * bitcols + y * 3 + 1] = centers[i].green;
      out[x * bitcols + y * 3 + 2] = centers[i].blue;
    }
  }

  /* Writing */
  printf("P6\n");

  printf("%d %d \n", cols, rows);
  printf("%d\n", maxval);

  for (i = 0; i < rows; i++) {
    for (j = 0; j < bitcols; j++) {
      printf("%c", out[i * bitcols + j]);
    }
  }


  /* Closing */
  fclose(ifp);
  return 0;
}
