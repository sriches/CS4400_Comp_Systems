/* Blocking ... Split up quadrants into smaller pieces. Looking at naive pinwheel implementation,
	it will look like 6 nested loops instead of 4.... 

	Also, Instead of accessing R, G, B separately from memory, just get the whole pixel, then extract the
	RGB from there, and then save the pixel to destination rather than saving the R,G,B separately.

*/




#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Spenser Riches",     /* Full name */
  "u1072910@utah.edu",  /* Email address */

};






/******************************************************
 * PINWHEEL KERNEL
 *
 * Your different versions of the pinwheel kernel go here
 ******************************************************/

/* 
 * naive_pinwheel - The naive baseline version of pinwheel 
 */
char naive_pinwheel_descr[] = "naive_pinwheel: baseline implementation";
void naive_pinwheel(pixel *src, pixel *dest)
{
  int qi, qj, i, j;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */
      for (i = 0; i < src->dim/2; i++)
        for (j = 0; j < src->dim/2; j++) {
          int s_idx = RIDX((qj * src->dim/2) + i,
                           j + (qi * src->dim/2), src->dim);
          int d_idx = RIDX((qj * src->dim/2) + src->dim/2 - 1 - j,
                           i + (qi * src->dim/2), src->dim);
          dest[d_idx].red = (src[s_idx].red
                             + src[s_idx].green
                             + src[s_idx].blue) / 3;
          dest[d_idx].green = (src[s_idx].red
                               + src[s_idx].green
                               + src[s_idx].blue) / 3;
          dest[d_idx].blue = (src[s_idx].red
                              + src[s_idx].green
                              + src[s_idx].blue) / 3;
        }
}


/* 
 * First Change
 */
char pinwheel1_descr[] = "pinwheel1: Replaced src memory grabs with local variables";
void pinwheel1(pixel *src, pixel *dest)
{
  	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */
      for (i = 0; i < half_src_dim; i++)
        for (j = 0; j < half_src_dim; j++) {
          
		int s_idx = RIDX((qj * half_src_dim) + i,
                           j + (qi * half_src_dim), src_dim);
          
		int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
                           i + (qi * half_src_dim), src_dim);
		
		// Get values for source red, green and blue
		int src_red   = src[s_idx].red;
		int src_green = src[s_idx].green;
		int src_blue  = src[s_idx].blue;

		int src_avg = (src_red
                         + src_green
                         + src_blue) / 3;

		// Set source RGB to average
		dest[d_idx].red = src_avg;
          dest[d_idx].green = src_avg;
          dest[d_idx].blue = src_avg;
        }
}

/* 
 * Second Change
 */
char pinwheel2_descr[] = "pinwheel2:  Switch i and j loops.";
void pinwheel2(pixel *src, pixel *dest)
{
  	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */

      for (j = 0; j < half_src_dim; j++)
      	for (i = 0; i < half_src_dim; i++) {
          
			int s_idx = RIDX((qj * half_src_dim) + i,
		                        j + (qi * half_src_dim), src_dim);
		       
			int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
		                        i + (qi * half_src_dim), src_dim);
		
			// Get values for source red, green and blue
			int src_red   = src[s_idx].red;
			int src_green = src[s_idx].green;
			int src_blue  = src[s_idx].blue;

			int src_avg = (src_red
		                      + src_green
		                      + src_blue) / 3;

			// Set source RGB to average
			dest[d_idx].red = src_avg;
          dest[d_idx].green = src_avg;
          dest[d_idx].blue = src_avg;
        }
}

/* 
 * Third Change
 */
char pinwheel3_descr[] = "pinwheel3:  Add to pinwheel 2...Loop Unroll jx4 ";
void pinwheel3(pixel *src, pixel *dest)
{
    	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */





	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
		for (qj = 0; qj < 2; qj++)
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=4)
				for (i = 0; i < half_src_dim; i++){

					{
						int s_idx = RIDX((qj * half_src_dim) + i,
								  j + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
								  i + (qi * half_src_dim), src_dim);


						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						int jPlusOne = j + 1;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusOne + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusOne,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						int jPlusTwo = j + 2;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusTwo + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusTwo,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						int jPlusThree = j + 3;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusThree + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusThree,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}
}


/* 
 * Forth Change
 */
char pinwheel4_descr[] = "pinwheel4:  .pinwheel3 then added....changed some multiplication into local vars ";
void pinwheel4(pixel *src, pixel *dest)
{
    	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */

	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
		for (qj = 0; qj < 2; qj++)
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					int qj_X_half_src_dim = qj * half_src_dim;
					int qi_X_half_src_dim = qi * half_src_dim;
					int ridxDestaAg2 = i + (qi_X_half_src_dim);


					{
						int s_idx = RIDX((qj_X_half_src_dim) + i,
								  j + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - j,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						int jPlusOne = j + 1;

						int s_idx = RIDX((qj_X_half_src_dim) + i,
								  jPlusOne + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusOne,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						int jPlusTwo = j + 2;

						int s_idx = RIDX((qj_X_half_src_dim) + i,
								  jPlusTwo + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusTwo,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						int jPlusThree = j + 3;

						int s_idx = RIDX((qj_X_half_src_dim) + i,
								  jPlusThree + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusThree,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}
}


/* 
 * Fifth Change
 */
char pinwheel5_descr[] = "pinwheel5:  From 2....unroll ix4";
void pinwheel5(pixel *src, pixel *dest)
{
  	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */

      for (j = 0; j < half_src_dim; j++)
      	for (i = 0; i < half_src_dim; i+=4) {
          
				/* Loop: i, j  */
				{
					int s_idx = RIDX((qj * half_src_dim) + i,
										   j + (qi * half_src_dim), src_dim);
					 
					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
										   i + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
										 + src_green
										 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}

				/* Loop: i+1, j  */
				{
					int s_idx = RIDX((qj * half_src_dim) + i+1,
										   j + (qi * half_src_dim), src_dim);
					 
					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
										   i+1 + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
										 + src_green
										 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}

				/* Loop: i+2, j  */
				{
					int s_idx = RIDX((qj * half_src_dim) + i+2,
										   j + (qi * half_src_dim), src_dim);
					 
					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
										   i+2 + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
										 + src_green
										 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}

				/* Loop: i+3, j  */
				{
					int s_idx = RIDX((qj * half_src_dim) + i+3,
										   j + (qi * half_src_dim), src_dim);
					 
					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
										   i+3 + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
										 + src_green
										 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}


        }
}



/* 
 * Sixth Change
 */
char pinwheel6_descr[] = "pinwheel6:  .pinwheel4 then added....replaced RIDX with actual logic ";
void pinwheel6(pixel *src, pixel *dest)
{
    	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */

	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
		for (qj = 0; qj < 2; qj++)
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					int qj_X_half_src_dim = qj * half_src_dim;
					int qi_X_half_src_dim = qi * half_src_dim;
					int ridxDestaAg2 = i + (qi_X_half_src_dim);
					int ridxSrcArg1 = (qj_X_half_src_dim) + i;

					{
						int s_idx = RIDX(ridxSrcArg1,
								  j + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - j,
								  ridxDestaAg2, src_dim);


						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						int jPlusOne = j + 1;

						int s_idx = RIDX(ridxSrcArg1,
								  jPlusOne + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusOne,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						int jPlusTwo = j + 2;

						int s_idx = RIDX(ridxSrcArg1,
								  jPlusTwo + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusTwo,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						int jPlusThree = j + 3;

						int s_idx = RIDX(ridxSrcArg1,
								  jPlusThree + (qi_X_half_src_dim), src_dim);

						int d_idx = RIDX((qj_X_half_src_dim) + half_src_dim - 1 - jPlusThree,
								  ridxDestaAg2, src_dim);

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}
}


/* 
 * Seventh Change
 */
char pinwheel7_descr[] = "pinwheel7:  Add to pinwheel 4... Each quadrant in their own loop and replaced RIDX with actual calculation";
void pinwheel7(pixel *src, pixel *dest)
{
    	int i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */



	/* Loop over 1st quadrant:    qi = 0    qj = 0*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/*  RIDX(i,j,n) ((i)*(n)+(j)+1)  */
					int s_idx = i*src_dim+j+1;

					/* FIRST LOOP */
					{

						int d_idx = (half_src_dim - 1 - j)*src_dim + i +1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{

						/* RIDX(i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i , src_dim); */
						int d_idx = (half_src_dim - j-2)* src_dim + i + 1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{						
						/* RIDX(i, jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (half_src_dim - j-3) * src_dim + i + 1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 2nd quadrant:    qi = 0    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + j+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j,  i, src_dim); */
						int d_idx = (src_dim - j-1)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne,  i, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 3rd quadrant:    qi = 1    qj = 0*/

			
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(i,  j + half_src_dim, src_dim); */
					int s_idx = i*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(half_src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-1)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 4th quadrant:    qi = 1    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j + half_src_dim, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - 1 - j)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}
}   /* END SEVENTH CHANGE */










/* 
 * Eighth Change
 */
char pinwheel8_descr[] = "pinwheel8:  Add to pinwheel 7... Unroll loop x8 instead of x4";
void pinwheel8(pixel *src, pixel *dest)
{
    	int i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */



	/* Loop over 1st quadrant:    qi = 0    qj = 0*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=8)
				for (i = 0; i < half_src_dim; i++){

					/*  RIDX(i,j,n) ((i)*(n)+(j)+1)  */
					int s_idx = i*src_dim+j+1;

					/* FIRST LOOP */
					{
						int d_idx = (half_src_dim - j-1)*src_dim + i +1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{

						/* RIDX(i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i , src_dim); */
						int d_idx = (half_src_dim - j-2)* src_dim + i + 1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{						
						/* RIDX(i, jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (half_src_dim - j-3) * src_dim + i + 1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FIFTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-5)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SIXTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-6)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SEVENTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-7)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* EIGHTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-8)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 2nd quadrant:    qi = 0    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=8)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + j+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j,  i, src_dim); */
						int d_idx = (src_dim - j-1)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne,  i, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FIFTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-5)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SIXTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-6)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SEVENTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-7)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* EIGHTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-8)*src_dim + i+1;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 3rd quadrant:    qi = 1    qj = 0*/

			
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=8)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(i,  j + half_src_dim, src_dim); */
					int s_idx = i*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(half_src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-1)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FIFTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-5)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SIXTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-6)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SEVENTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-7)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* EIGHTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-8)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}



/* Loop over 4th quadrant:    qi = 1    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=8)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j + half_src_dim, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - 1 - j)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* FIFTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-5)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SIXTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-6)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* SEVENTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-7)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
					/* EIGHTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-8)*src_dim + half_src_dim_plus_i_plus_one;

						// Get values for source red, green and blue
						int src_red   = src[s_idx].red;
						int src_green = src[s_idx].green;
						int src_blue  = src[s_idx].blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						dest[d_idx].red = src_avg;
						dest[d_idx].green = src_avg;
						dest[d_idx].blue = src_avg;
					}
				}
}
/* END EIGHTH CHANGE */


/* 
 * NINTH Change
 */
char pinwheel9_descr[] = "pinwheel9:  From pinwheel 2, then unrolled inner i loop x2.";
void pinwheel9(pixel *src, pixel *dest)
{
  	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */

      for (j = 0; j < half_src_dim; j++)
			for (i = 0; i < half_src_dim; i+=2) {
				/* First loop */
				{
					int s_idx = RIDX((qj * half_src_dim) + i,
									j + (qi * half_src_dim), src_dim);

					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
									i + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
								 + src_green
								 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}
				/* Second loop */
				{
					int s_idx = RIDX((qj * half_src_dim) + i+1,
									j + (qi * half_src_dim), src_dim);

					int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
									i+1 + (qi * half_src_dim), src_dim);

					// Get values for source red, green and blue
					int src_red   = src[s_idx].red;
					int src_green = src[s_idx].green;
					int src_blue  = src[s_idx].blue;

					int src_avg = (src_red
								 + src_green
								 + src_blue) / 3;

					// Set source RGB to average
					dest[d_idx].red = src_avg;
					dest[d_idx].green = src_avg;
					dest[d_idx].blue = src_avg;
				}
				
			}
}
/* END NINTH CHANGE */




/* 
 * TENTH Change
 */
char pinwheel10_descr[] = "pinwheel10:  Add to pinwheel 7... Access whole pixel and save whole pixel rather than separate rgb access/writes";
void pinwheel10(pixel *src, pixel *dest)
{
    	int i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */



	/* Loop over 1st quadrant:    qi = 0    qj = 0*/
			/* Loop within quadrant: */
			pixel currentSrcPix;

			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/*  RIDX(i,j,n) ((i)*(n)+(j)+1)  */
					int s_idx = i*src_dim+j+1;

					/* FIRST LOOP */
					{

						int d_idx = (half_src_dim - 1 - j)*src_dim + i +1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* SECOND LOOP */
					{

						/* RIDX(i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i , src_dim); */
						int d_idx = (half_src_dim - j-2)* src_dim + i + 1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* THIRD LOOP */
					{						
						/* RIDX(i, jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (half_src_dim - j-3) * src_dim + i + 1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + i+1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
				}



/* Loop over 2nd quadrant:    qi = 0    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + j+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j,  i, src_dim); */
						int d_idx = (src_dim - j-1)*src_dim + i+1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne,  i, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + i+1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusTwo, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + i+1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i,  jPlusThree, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree,  i, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + i+1;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
				}



/* Loop over 3rd quadrant:    qi = 1    qj = 0*/

			
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(i,  j + half_src_dim, src_dim); */
					int s_idx = i*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(half_src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-1)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* SECOND LOOP */
					{
						/* RIDX(i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* THIRD LOOP */
					{
						/* RIDX(i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusTwo,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* FORTH LOOP */
					{
						/* RIDX(i,  jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(half_src_dim - 1 - jPlusThree,  i + half_src_dim, src_dim); */
						int d_idx = (half_src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
				}



/* Loop over 4th quadrant:    qi = 1    qj = 1*/
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* RIDX(half_src_dim + i,  j + half_src_dim, src_dim); */
					int s_idx = (half_src_dim + i)*src_dim + half_src_dim + j+1;

					int half_src_dim_plus_i_plus_one = half_src_dim + i+1;

					/* FIRST LOOP */
					{

						/* RIDX(src_dim - 1 - j, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - 1 - j)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* SECOND LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusOne + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusOne, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-2)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* THIRD LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusTwo + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusTwo, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-3)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
					/* FORTH LOOP */
					{
						/* RIDX(half_src_dim + i, jPlusThree + half_src_dim, src_dim); */
						s_idx++;

						/* RIDX(src_dim - 1 - jPlusThree, i + half_src_dim, src_dim); */
						int d_idx = (src_dim - j-4)*src_dim + half_src_dim_plus_i_plus_one;

						currentSrcPix = src[s_idx];
						// Get values for source red, green and blue
						int src_red   = currentSrcPix.red;
						int src_green = currentSrcPix.green;
						int src_blue  = currentSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						currentSrcPix.red = src_avg;
						currentSrcPix.green = src_avg;
						currentSrcPix.blue = src_avg;
						
						// Set dest pixel
						dest[d_idx] = currentSrcPix;
					}
				}
}   /* END TENTH CHANGE */



/* 
 * ELEVENTH Change
 */
char pinwheel11_descr[] = "pinwheel11:  Add to pinwheel 3...Grab whole pixel rather than just RBG ";
void pinwheel11(pixel *src, pixel *dest)
{
    	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */

	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
		for (qj = 0; qj < 2; qj++)
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim-3; j+=4)
				for (i = 0; i < half_src_dim; i++){

					/* FIRST LOOP */
					{
						int s_idx = RIDX((qj * half_src_dim) + i,
								  j + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
								  i + (qi * half_src_dim), src_dim);

						pixel curSrcPix = src[s_idx];

						// Get values for source red, green and blue
						int src_red   = curSrcPix.red;
						int src_green = curSrcPix.green;
						int src_blue  = curSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						curSrcPix.red = src_avg;
						curSrcPix.green = src_avg;
						curSrcPix.blue = src_avg;

						dest[d_idx] = curSrcPix;
					}
					/* SECOND LOOP */
					{
						int jPlusOne = j + 1;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusOne + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusOne,
								  i + (qi * half_src_dim), src_dim);

						pixel curSrcPix = src[s_idx];

						// Get values for source red, green and blue
						int src_red   = curSrcPix.red;
						int src_green = curSrcPix.green;
						int src_blue  = curSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						curSrcPix.red = src_avg;
						curSrcPix.green = src_avg;
						curSrcPix.blue = src_avg;

						dest[d_idx] = curSrcPix;
					}
					/* THIRD LOOP */
					{
						int jPlusTwo = j + 2;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusTwo + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusTwo,
								  i + (qi * half_src_dim), src_dim);

						pixel curSrcPix = src[s_idx];

						// Get values for source red, green and blue
						int src_red   = curSrcPix.red;
						int src_green = curSrcPix.green;
						int src_blue  = curSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						curSrcPix.red = src_avg;
						curSrcPix.green = src_avg;
						curSrcPix.blue = src_avg;

						dest[d_idx] = curSrcPix;
					}
					/* FORTH LOOP */
					{
						int jPlusThree = j + 3;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusThree + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusThree,
								  i + (qi * half_src_dim), src_dim);

						pixel curSrcPix = src[s_idx];

						// Get values for source red, green and blue
						int src_red   = curSrcPix.red;
						int src_green = curSrcPix.green;
						int src_blue  = curSrcPix.blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						// Set source RGB to average
						curSrcPix.red = src_avg;
						curSrcPix.green = src_avg;
						curSrcPix.blue = src_avg;

						dest[d_idx] = curSrcPix;
					}
				}
}
/* END ELEVENTH CHANGE */




/* 
 * TWELVTH Change
 */
char pinwheel12_descr[] = "pinwheel12:  pinwheel 2 then access whole pixel";
void pinwheel12(pixel *src, pixel *dest)
{
  	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */

      for (j = 0; j < half_src_dim; j++)
      	for (i = 0; i < half_src_dim; i++) {
          
			int s_idx = RIDX((qj * half_src_dim) + i,
		                        j + (qi * half_src_dim), src_dim);
		       
			int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
		                        i + (qi * half_src_dim), src_dim);
		
			pixel srcPix = src[s_idx];

			// Get values for source red, green and blue
			int src_avg = (srcPix.red + srcPix.green + srcPix.blue) / 3;

			// Set source RGB to average
			srcPix.red = src_avg;
         srcPix.green = src_avg;
         srcPix.blue = src_avg;

			dest[d_idx] = srcPix;
        }
}
/* END TWELVTH CHANGE */




/* 
 * naive_pinwheel - The naive baseline version of pinwheel 
 */
char pinwheel13_descr[] = "pinwheel13: naive_pinwheel then access pixel directly";
void pinwheel13(pixel *src, pixel *dest)
{
  int qi, qj, i, j;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

  /* Loop over 4 quadrants: */
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)
      /* Loop within quadrant: */
      for (i = 0; i < src->dim/2; i++)
        for (j = 0; j < src->dim/2; j++) {
          int s_idx = RIDX((qj * src->dim/2) + i,
                           j + (qi * src->dim/2), src->dim);
          int d_idx = RIDX((qj * src->dim/2) + src->dim/2 - 1 - j,
                           i + (qi * src->dim/2), src->dim);

			pixel srcPix = src[s_idx];

			int avgRGB = (srcPix.red + srcPix.green + srcPix.blue) / 3;

			srcPix.red   = avgRGB;
			srcPix.green = avgRGB;
			srcPix.blue  = avgRGB;

         dest[d_idx] = srcPix;
        }
}




/* 
 * FORTEENTH Change
 */
char pinwheel14_descr[] = "pinwheel14:  pinwheel3, then access pixel directly.";
void pinwheel14(pixel *src, pixel *dest)
{
    	int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;

	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */

	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
		for (qj = 0; qj < 2; qj++)
			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=4)

						


				for (i = 0; i < half_src_dim; i++){

					// Variable to hold source and destination pixel pointers
					pixel *srcPix;
					pixel *destPix;

					{
						int s_idx = RIDX((qj * half_src_dim) + i,
								  j + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - j,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* SECOND LOOP */
					{
						int jPlusOne = j + 1;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusOne + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusOne,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* THIRD LOOP */
					{
						int jPlusTwo = j + 2;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusTwo + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusTwo,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* FORTH LOOP */
					{
						int jPlusThree = j + 3;

						int s_idx = RIDX((qj * half_src_dim) + i,
								  jPlusThree + (qi * half_src_dim), src_dim);

						int d_idx = RIDX((qj * half_src_dim) + half_src_dim - 1 - jPlusThree,
								  i + (qi * half_src_dim), src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
				}
}






















/* 
 * FIFTEENTH Change
 */
char pinwheel15_descr[] = "pinwheel15:  pinwheel14, calculation optimization.";
void pinwheel15(pixel *src, pixel *dest)
{
   int qi, qj, i, j;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;


	/* qi & qj are column and row of quadrant
	i & j are column and row within quadrant */

	/* Loop over 4 quadrants: */
	for (qi = 0; qi < 2; qi++)
	{
		for (qj = 0; qj < 2; qj++)
		{
			// One calc to reuse
			int qj_x_half_src_dim = qj * half_src_dim;
			int qi_x_half_src_dim = qi * half_src_dim;
			int qj_x_half_src_dim_plus_half_src_dim = qj_x_half_src_dim + half_src_dim;



			/* Loop within quadrant: */
			for (j = 0; j < half_src_dim; j+=4)
			{

				int qj_x_half_src_dim_plus_half_src_dim_minus_j = qj_x_half_src_dim_plus_half_src_dim - j;


				for (i = 0; i < half_src_dim; i++)
				{

					// Variable to hold source and destination pixel pointers
					pixel *srcPix;
					pixel *destPix;

					
						// Calculate s_idx once, then increment for the rest of the unrolled loops
						int s_idx = RIDX((qj_x_half_src_dim) + i,
								  j + (qi_x_half_src_dim), src_dim);

					/* FIRST LOOP */
					{
						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-1,
								  				i + (qi_x_half_src_dim),
												src_dim);

						

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					
					/* SECOND LOOP */
					{
						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-2,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* THIRD LOOP */
					{

						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-3,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* FORTH LOOP */
					{

						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-4,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
				}
			}
		}
	}
}
/* END FIFTEENTH CHANGE */







/*
i + (qi * src->dim/2), src->dim);
			for (qi = 0; qi < dim; qi+=32)
			{
				for (qj = 0; qj < dim; qj+=32)
				{
					 Loop within quadrant: 
					for (i = qi; i < qi+32; i++)
					{
						for (j = qj; j < qi+32; j++)
						{
						
							// #define RIDX(i,j,n) ---->  (1+(i)*(n)+(j))

							int src_i = qi+i;
							int src_j = qj+j;

							int src_index = j*dim+qi+i;

							// Destination index calculations
							int dest_i = qj+dim/2 -1 -src_j;
							int dest_j = src_i;

							int dest_index = ;


							
							int s_idx = RIDX((qj * src->dim/2) + i,
													j + (qi * src->dim/2), src->dim);

							int d_idx = RIDX((qj * src->dim/2) + src->dim/2 - 1 - j,
													i + (qi * src->dim/2), src->dim);
							

							int s_idx = src_index;
							int d_idx = dest_index;

*/












/* Loop over 4 quadrants: 
  for (qi = 0; qi < 2; qi++)
    for (qj = 0; qj < 2; qj++)

       Loop within quadrant: 
      for (i = 0; i < src->dim/2; i++)
        for (j = 0; j < src->dim/2; j++) {

							 int s_idx = RIDX((qj * half_dim) + i,
										         j + (qi * half_dim),
													src->dim);

							 int d_idx = RIDX((qj * half_dim) + half_dim - 1 - j,
										         i + (qi * half_dim),
													src->dim);
*/
/* 
 * SIXTEENTH Change
 */
char pinwheel16_descr[] = "pinwheel16:  Naive Plus Blocking";
void pinwheel16(pixel *src, pixel *dest)
{
  	int qi, qj, ii, jj, i, j;

  /* qi & qj are column and row of quadrant
     i & j are column and row within quadrant */

	int width=16;
	int half_dim = src->dim/2;

  	/* Loop over 4 quadrants: */
  	for (qi = 0; qi < 2; qi++)
	{
		int qi_x_half_dim = qi*half_dim;
		
		for (qj = 0; qj < 2; qj++)
		{

			/* Loop over blocks */
			for(ii = 0; ii < half_dim; ii += width)
			{

				for(jj = 0; jj <  half_dim; jj += width)
				{


					/* Loop within block: */
					

					for (j = jj; j < jj + width; j++)
					{
						
						int qj_x_half_dim = qj*half_dim;
						int qj_x_half_dim_plus_half_dim_minus_one_minus_j = (qj_x_half_dim) + half_dim - 1 - j;


						for (i = ii; i < ii + width; i+=4)
						{
							

							// FIRST I LOOP UNROLL
							{
								int s_idx = RIDX((qj_x_half_dim) + i,
												      j + (qi_x_half_dim),
														src->dim);

								int d_idx = RIDX(qj_x_half_dim_plus_half_dim_minus_one_minus_j,
												      i + (qi_x_half_dim),
														src->dim);


								pixel *srcPix;
								pixel *destPix;


								// Get values for source red, green and blue
								srcPix = &src[s_idx];

								int src_red   = srcPix->red;
								int src_green = srcPix->green;
								int src_blue  = srcPix->blue;

								// Calculate average
								int src_avg = (src_red
										+ src_green
										+ src_blue) / 3;

								destPix = &dest[d_idx];
						
								// Set source RGB to average
						
								destPix->red = src_avg;
								destPix->green = src_avg;
								destPix->blue = src_avg;
							}
							// SECOND I LOOP UNROLL
							{
								int s_idx = RIDX((qj_x_half_dim) + i+1,
												      j + (qi_x_half_dim),
														src->dim);

								int d_idx = RIDX(qj_x_half_dim_plus_half_dim_minus_one_minus_j,
												      i+1 + (qi_x_half_dim),
														src->dim);


								pixel *srcPix;
								pixel *destPix;


								// Get values for source red, green and blue
								srcPix = &src[s_idx];

								int src_red   = srcPix->red;
								int src_green = srcPix->green;
								int src_blue  = srcPix->blue;

								// Calculate average
								int src_avg = (src_red
										+ src_green
										+ src_blue) / 3;

								destPix = &dest[d_idx];
						
								// Set source RGB to average
						
								destPix->red = src_avg;
								destPix->green = src_avg;
								destPix->blue = src_avg;
							}
							// THIRD I LOOP UNROLL
							{
								int s_idx = RIDX((qj_x_half_dim) + i+2,
												      j + (qi_x_half_dim),
														src->dim);

								int d_idx = RIDX(qj_x_half_dim_plus_half_dim_minus_one_minus_j,
												      i+2 + (qi_x_half_dim),
														src->dim);


								pixel *srcPix;
								pixel *destPix;


								// Get values for source red, green and blue
								srcPix = &src[s_idx];

								int src_red   = srcPix->red;
								int src_green = srcPix->green;
								int src_blue  = srcPix->blue;

								// Calculate average
								int src_avg = (src_red
										+ src_green
										+ src_blue) / 3;

								destPix = &dest[d_idx];
						
								// Set source RGB to average
						
								destPix->red = src_avg;
								destPix->green = src_avg;
								destPix->blue = src_avg;
							}
							// FORTH I LOOP UNROLL
							{
								int s_idx = RIDX((qj_x_half_dim) + i+3,
												      j + (qi_x_half_dim),
														src->dim);

								int d_idx = RIDX(qj_x_half_dim_plus_half_dim_minus_one_minus_j,
												      i+3 + (qi_x_half_dim),
														src->dim);


								pixel *srcPix;
								pixel *destPix;


								// Get values for source red, green and blue
								srcPix = &src[s_idx];

								int src_red   = srcPix->red;
								int src_green = srcPix->green;
								int src_blue  = srcPix->blue;

								// Calculate average
								int src_avg = (src_red
										+ src_green
										+ src_blue) / 3;

								destPix = &dest[d_idx];
						
								// Set source RGB to average
						
								destPix->red = src_avg;
								destPix->green = src_avg;
								destPix->blue = src_avg;
							}







						}
					}
				}
			}
		}
	}
}   /* END SIXTEENTH CHANGE */




































/* 
 * 17 Change
 */
char pinwheel17_descr[] = "pinwheel17:  Unroll J loop";
void pinwheel17(pixel *src, pixel *dest)
{
  	int qi, qj, ii, jj, i, j;

	int width=16;

	// Get the dimention and half dimention of the source
	int src_dim = src->dim;
	int half_src_dim = src_dim/2;


  	/* Loop over 4 quadrants: */
  	for (qi = 0; qi < 2; qi++)
	{
		//int qi_x_half_dim = qi*half_dim;
		
		for (qj = 0; qj < 2; qj++)
		{
			//int qj_x_half_dim = qj*half_dim;

			int qj_x_half_src_dim = qj * half_src_dim;
			int qi_x_half_src_dim = qi * half_src_dim;
			int qj_x_half_src_dim_plus_half_src_dim = qj_x_half_src_dim + half_src_dim;

			/* Loop over blocks */
			for(ii = 0; ii < half_src_dim; ii += width)
			{
				for(jj = 0; jj <  half_src_dim; jj += width)
				{


					for (j = jj; j < (jj + width)-1; j+=4)
					{
						int qj_x_half_src_dim_plus_half_src_dim_minus_j = qj_x_half_src_dim_plus_half_src_dim - j;
						
						for (i = ii; i < ii + width; i++)
						{


												// Variable to hold source and destination pixel pointers
					pixel *srcPix;
					pixel *destPix;

					
						// Calculate s_idx once, then increment for the rest of the unrolled loops
						int s_idx = RIDX((qj_x_half_src_dim) + i,
								  j + (qi_x_half_src_dim), src_dim);

					/* FIRST LOOP */
					{
						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-1,
								  				i + (qi_x_half_src_dim),
												src_dim);

						

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					
					/* SECOND LOOP */
					{
						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-2,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* THIRD LOOP */
					{

						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-3,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}
					/* FORTH LOOP */
					{

						s_idx++;

						int d_idx = RIDX(qj_x_half_src_dim_plus_half_src_dim_minus_j-4,
								  				i + (qi_x_half_src_dim),
												src_dim);

						// Get values for source red, green and blue
						srcPix = &src[s_idx];

						int src_red   = srcPix->red;
						int src_green = srcPix->green;
						int src_blue  = srcPix->blue;

						// Calculate average
						int src_avg = (src_red
								+ src_green
								+ src_blue) / 3;

						destPix = &dest[d_idx];
						
						// Set source RGB to average
						destPix->red = src_avg;
						destPix->green = src_avg;
						destPix->blue = src_avg;
					}


							




						}
					}
				}
			}
		}
	}
}   /* END 17 CHANGE */













/* 
 * pinwheel - Your current working version of pinwheel
 * IMPORTANT: This is the version you will be graded on
 */
char pinwheel_descr[] = "pinwheel: Current working version";
void pinwheel(pixel *src, pixel *dest)
{
  pinwheel17(src, dest);
}

/*********************************************************************
 * register_pinwheel_functions - Register all of your different versions
 *     of the pinwheel kernel with the driver by calling the
 *     add_pinwheel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_pinwheel_functions() {
  add_pinwheel_function(&pinwheel, pinwheel_descr);
  //add_pinwheel_function(&naive_pinwheel, naive_pinwheel_descr);

  add_pinwheel_function(&pinwheel1, pinwheel1_descr);
	add_pinwheel_function(&pinwheel2, pinwheel2_descr);
	add_pinwheel_function(&pinwheel3, pinwheel3_descr);
	add_pinwheel_function(&pinwheel4, pinwheel4_descr);
	add_pinwheel_function(&pinwheel5, pinwheel5_descr);
	add_pinwheel_function(&pinwheel6, pinwheel6_descr);
	add_pinwheel_function(&pinwheel7, pinwheel7_descr);
	add_pinwheel_function(&pinwheel8, pinwheel8_descr);
	add_pinwheel_function(&pinwheel9, pinwheel9_descr);
	add_pinwheel_function(&pinwheel10, pinwheel10_descr);
	add_pinwheel_function(&pinwheel11, pinwheel11_descr);
	add_pinwheel_function(&pinwheel12, pinwheel12_descr);
	add_pinwheel_function(&pinwheel13, pinwheel13_descr);
	add_pinwheel_function(&pinwheel14, pinwheel14_descr);

	add_pinwheel_function(&pinwheel15, pinwheel15_descr);

	add_pinwheel_function(&pinwheel16, pinwheel16_descr);
	add_pinwheel_function(&pinwheel17, pinwheel17_descr);

}



























/***************************************************************
 * MOTION KERNEL
 * 
 * Starts with various typedefs and helper functions for the motion
 * function, and you may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_weighted_sum(pixel_sum *sum, pixel p, double weight) 
{
  sum->red += (int) p.red * weight;
  sum->green += (int) p.green * weight;
  sum->blue += (int) p.blue * weight;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned short)sum.red;
  current_pixel->green = (unsigned short)sum.green;
  current_pixel->blue = (unsigned short)sum.blue;
}

/* 
 * weighted_combo - Returns new pixel value at (i,j) 
 */
static pixel weighted_combo(int dim, int i, int j, pixel *src) 
{
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;
  double weights[3][3] = { { 0.60, 0.03, 0.00 },
                           { 0.03, 0.30, 0.03 },
                           { 0.00, 0.03, 0.10 } };

  initialize_pixel_sum(&sum);
  for (ii=0; ii < 3; ii++)
    for (jj=0; jj < 3; jj++) 
      if ((i + ii < dim) && (j + jj < dim))
        accumulate_weighted_sum(&sum,
                                src[RIDX(i+ii,j+jj,dim)],
                                weights[ii][jj]);
  
  assign_sum_to_pixel(&current_pixel, sum);

  return current_pixel;
}

/******************************************************
 * Your different versions of the motion kernel go here
 ******************************************************/

/*
 * naive_motion - The naive baseline version of motion 
 */
char naive_motion_descr[] = "naive_motion: baseline implementation";
void naive_motion(pixel *src, pixel *dst) 
{
  int i, j;
    
  for (i = 0; i < src->dim; i++)
    for (j = 0; j < src->dim; j++)
      dst[RIDX(i, j, src->dim)] = weighted_combo(src->dim, i, j, src);
}

/*
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(pixel *src, pixel *dst) 
{
  naive_motion(src, dst);
}

/********************************************************************* 
 * register_motion_functions - Register all of your different versions
 *     of the motion kernel with the driver by calling the
 *     add_motion_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_motion_functions() {
  add_motion_function(&motion, motion_descr);
  add_motion_function(&naive_motion, naive_motion_descr);
}
