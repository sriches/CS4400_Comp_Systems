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
 * 17 Change ... As suggested by a TA, I deleted my 1st through 16th tries to speed the program up. Seemed to work quite a bit, given I deleted over 3,000 lines of code...
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
 * First change 
 */
char motion1_descr[] = "motion1: bring everything into one function";
void motion1(pixel *src, pixel *dst) 
{
	int i, j;
	int dim = src->dim;

 	for (i = 0; i < dim; i++)
    	for (j = 0; j < dim; j++)
		{
			int ii, jj;
			pixel_sum sum;
			pixel current_pixel;
			double weights[3][3] = { { 0.60, 0.03, 0.00 },
						               { 0.03, 0.30, 0.03 },
						               { 0.00, 0.03, 0.10 } };

			sum.red = sum.green = sum.blue = 0;

		  	for (ii=0; ii < 3; ii++)
			{
			 	for (jj=0; jj < 3; jj++) 
				{
					if ((i + ii < dim) && (j + jj < dim))
					{
						pixel p = src[RIDX(i+ii,j+jj,dim)];

						double weight = weights[ii][jj];


					  	sum.red += (int) p.red * weight;
						sum.green += (int) p.green * weight;
						sum.blue += (int) p.blue * weight;
						
		  			}
				}
			}

		  current_pixel.red = (unsigned short)sum.red;
		  current_pixel.green = (unsigned short)sum.green;
		  current_pixel.blue = (unsigned short)sum.blue;
			
			dst[RIDX(i, j, dim)] = current_pixel;
		}
}




/*
 * Second change 
 */
char motion2_descr[] = "motion2: 1..then getting values for each rgb * 0.03, manually looping through weights.";
void motion2(pixel *src, pixel *dst) 
{
	int i, j;
	int dim = src->dim;

	// Store RGB values for * 0.03
	int R_xp03[dim][dim];
	int G_xp03[dim][dim];
	int B_xp03[dim][dim];

	// Calculate all RGB values times 0.03
	for(i = 0; i < dim; i++)
		for(j = 0; j < dim; j++)
		{
			pixel *p = &src[RIDX(i, j, dim)];
			
			R_xp03[i][j] = (int) (p->red * 0.03);
			G_xp03[i][j] = (int) (p->green * 0.03);
			B_xp03[i][j] = (int) (p->blue * 0.03);
		}

 	for (i = 0; i < dim; i++)
    	for (j = 0; j < dim; j++)
		{
			int ii, jj;
			pixel_sum sum;
			pixel current_pixel;
			pixel p;

			// Initialize RGB values to 0
			sum.red = sum.green = sum.blue = 0;

			// Get top left
			if ((i < dim) && (j < dim))
			{
				p = src[RIDX(i,j,dim)];

				double weight = 0.60;

			  	sum.red 		+= (int) p.red * weight;
				sum.green 	+= (int) p.green * weight;
				sum.blue 	+= (int) p.blue * weight;
				
  			}

			// Get middle-middle
			if ((i + 1 < dim) && (j + 1 < dim))
			{
				p = src[RIDX(i+1,j+1,dim)];

				double weight = 0.30;


			  	sum.red 		+= (int) p.red * weight;
				sum.green 	+= (int) p.green * weight;
				sum.blue 	+= (int) p.blue * weight;
				
  			}

			// Get bottom right
			if ((i + 2 < dim) && (j + 2 < dim))
			{
				p = src[RIDX(i+2,j+2,dim)];

				double weight = 0.10;

			  	sum.red 		+= (int) p.red * weight;
				sum.green 	+= (int) p.green * weight;
				sum.blue 	+= (int) p.blue * weight;
				
  			}

			////////////////////////////////////////////
			//   All four 0.03 accesses are similar	//
			////////////////////////////////////////////

			// Get top middle
			if ((i < dim) && (j + 1 < dim))
			{
				p = src[RIDX(i,j+1,dim)];

				sum.red 		+= R_xp03[i][j+1];
				sum.green 	+= G_xp03[i][j+1];
				sum.blue 	+= B_xp03[i][j+1];	
  			}

			// Get middle left
			if ((i + 1 < dim) && (j < dim))
			{
				p = src[RIDX(i+1,j,dim)];

				sum.red 		+= R_xp03[i+1][j];
				sum.green 	+= G_xp03[i+1][j];
				sum.blue 	+= B_xp03[i+1][j];	
  			}

			// Get middle right
			if ((i + 1 < dim) && (j + 2 < dim))
			{
				p = src[RIDX(i+1,j+jj,dim)];

				sum.red 		+= R_xp03[i+1][j+2];
				sum.green 	+= G_xp03[i+1][j+2];
				sum.blue 	+= B_xp03[i+1][j+2];	
  			}

			// Get middle bottom
			if ((i + 2 < dim) && (j + 1 < dim))
			{
				p = src[RIDX(i+2,j+1,dim)];

				sum.red 		+= R_xp03[i+2][j+1];
				sum.green 	+= G_xp03[i+2][j+1];
				sum.blue 	+= B_xp03[i+2][j+1];	
  			}


			current_pixel.red = (unsigned short)sum.red;
			current_pixel.green = (unsigned short)sum.green;
			current_pixel.blue = (unsigned short)sum.blue;

			dst[RIDX(i, j, dim)] = current_pixel;
		}
}



/*
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(pixel *src, pixel *dst) 
{
  motion2(src, dst);
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
  add_motion_function(motion1, motion1_descr);
  add_motion_function(motion2, motion2_descr);
}
