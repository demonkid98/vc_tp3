#include <stdlib.h>
#include <stdio.h>
#include "Util.h"
#include "pixel.h"



int main(int argc, char* argv[])
    {
    FILE* ifp, *ofp_gray;
    bit* colormap;
    int ich1, ich2, rows, cols, bitcols, maxval=255, is_raw;
    int i, j;



    /* Arguments */
    if ( argc != 2 ){
      printf("\nUsage: %s file \n\n", argv[0]);
      exit(0);
    }

    /* Opening */
    ifp = fopen(argv[1],"r");
    if (ifp == NULL) {
      printf("error in opening file %s\n", argv[1]);
      exit(1);
    }

    ofp_gray = fopen("./gray.out", "w");
    if (ofp_gray == NULL) {
      printf("error in creating/overiding file gray.out\n");
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
    colormap = (bit *) malloc(bitcols * rows * sizeof(bit));

    /* Reading */
    for(i=0; i < rows; i++)
      for(j=0; j < bitcols; j++)
        if(is_raw)
           colormap[i * bitcols + j] = pm_getrawbyte(ifp) ;
        else
           colormap[i * bitcols + j] = pm_getint(ifp);

    /* Writing */
    fprintf(ofp_gray, "P5\n");

    fprintf(ofp_gray, "%d %d \n", cols, rows);
    fprintf(ofp_gray, "%d\n",maxval);

    for (i = 0; i < rows; i++) {
      for (j = 0; j < bitcols; j++) {
        if (j % 3 == 0) {
          int coordinate = i * bitcols + j;
          char intensity = (char) (((int) colormap[coordinate] + (int) colormap[coordinate + 1] + (int) colormap[coordinate + 2]) / 3);
          fprintf(ofp_gray, "%c", intensity);
        }
      }
    }


      /* Closing */
      fclose(ifp);
      return 0;
}
