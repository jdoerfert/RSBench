#include "rsbench.h"

// JRT 
int * generate_n_poles( Input input )
{
	int total_resonances = input.avg_n_poles * input.n_nuclides;

	int * R = (int *) calloc( input.n_nuclides, sizeof(int));

	for( int i = 0; i < total_resonances; i++ )
	{
		R[rand() % input.n_nuclides]++;
	}

	// Ensure all nuclides have at least 1 resonance
	for( int i = 0; i < input.n_nuclides; i++ )
		if( R[i] == 0 )
			R[i] = 1;
	
	/* Debug	
	for( int i = 0; i < input.n_nuclides; i++ )
		printf("R[%d] = %d\n", i, R[i]);
	*/
	
	return R;
}

int * generate_n_windows( Input input )
{
	int total_resonances = input.avg_n_windows * input.n_nuclides;

	int * R = (int *) calloc( input.n_nuclides, sizeof(int));

	for( int i = 0; i < total_resonances; i++ )
	{
		R[rand() % input.n_nuclides]++;
	}

	// Ensure all nuclides have at least 1 resonance
	for( int i = 0; i < input.n_nuclides; i++ )
		if( R[i] == 0 )
			R[i] = 1;
	
	/* Debug	
	for( int i = 0; i < input.n_nuclides; i++ )
		printf("R[%d] = %d\n", i, R[i]);
	*/
	
	return R;
}

// 
Pole ** generate_poles( Input input, int * n_poles )
{
	// Allocating 2D contiguous matrix
	Pole ** R = (Pole **) malloc( input.n_nuclides * sizeof( Pole *));
	Pole * contiguous = (Pole *) malloc( input.n_nuclides * input.avg_n_poles * sizeof(Pole));

	int k = 0;
	for( int i = 0; i < input.n_nuclides; i++ )
	{
		R[i] = &contiguous[k];
		k += n_poles[i];
	}
	
	// fill with data
	for( int i = 0; i < input.n_nuclides; i++ )
	{
		for( int j = 0; j < n_poles[i]; j++ )
		{
			//R[i][j].MP_EA = (double) rand() / RAND_MAX + (double) rand() / RAND_MAX * _Complex_I;
			//R[i][j].MP_RT = (double) rand() / RAND_MAX + (double) rand() / RAND_MAX * _Complex_I;
			//R[i][j].MP_RA = (double) rand() / RAND_MAX + (double) rand() / RAND_MAX * _Complex_I;
			//R[i][j].MP_RF = (double) rand() / RAND_MAX + (double) rand() / RAND_MAX * _Complex_I;
			R[i][j].MP_EA.real = (double) rand() / RAND_MAX;
			R[i][j].MP_EA.imag = (double) rand() / RAND_MAX;
			R[i][j].MP_RT.real = (double) rand() / RAND_MAX;
			R[i][j].MP_RT.imag = (double) rand() / RAND_MAX;
			R[i][j].MP_RA.real = (double) rand() / RAND_MAX;
			R[i][j].MP_RA.imag = (double) rand() / RAND_MAX;
			R[i][j].MP_RF.real = (double) rand() / RAND_MAX;
			R[i][j].MP_RF.imag = (double) rand() / RAND_MAX;
			R[i][j].l_value = rand() % input.numL;
		}
	}
	
	/* Debug
	for( int i = 0; i < input.n_nuclides; i++ )
		for( int j = 0; j < n_poles[i]; j++ )
			printf("R[%d][%d]: Eo = %lf lambda_o = %lf Tn = %lf Tg = %lf Tf = %lf\n", i, j, R[i][j].Eo, R[i][j].lambda_o, R[i][j].Tn, R[i][j].Tg, R[i][j].Tf);
	*/

	return R;
}

Window ** generate_window_params( Input input, int * n_windows, int * n_poles )
{
	// Allocating 2D contiguous matrix
	Window ** R = (Window **) malloc( input.n_nuclides * sizeof( Window *));
	Window * contiguous = (Window *) malloc( input.n_nuclides * input.avg_n_windows * sizeof(Window));

	int k = 0;
	for( int i = 0; i < input.n_nuclides; i++ )
	{
		R[i] = &contiguous[k];
		k += n_windows[i];
	}
	
	// fill with data
	for( int i = 0; i < input.n_nuclides; i++ )
	{
		int space = n_poles[i] / n_windows[i];
		int remainder = n_poles[i] - space * n_windows[i];
		int ctr = 0;
		for( int j = 0; j < n_windows[i]; j++ )
		{
			R[i][j].T = (double) rand() / RAND_MAX;
			R[i][j].A = (double) rand() / RAND_MAX;
			R[i][j].F = (double) rand() / RAND_MAX;
			R[i][j].start = ctr; 
			R[i][j].end = ctr + space - 1;

			ctr += space;

			if ( j < remainder )
			{
				ctr++;
				R[i][j].end++;
			}
		}
	}

	return R;
}

double ** generate_pseudo_K0RS( Input input )
{
	double ** R = (double **) malloc( input.n_nuclides * sizeof( double * ));
	double * contiguous = (double *) malloc( input.n_nuclides * input.numL * sizeof(double));

	for( int i = 0; i < input.n_nuclides; i++ )
		R[i] = &contiguous[i*input.numL];

	return R;
}

int * load_poles_idx( int n_nuclides, int * n_poles )
{
	int * poles_idx = (int *) malloc(n_nuclides * sizeof(int));

	int j = 0;
	for (int i=0; i<n_nuclides; i++)
	{
		poles_idx[i] = j;
		j += n_poles[i];
	}

	return poles_idx;
}

int * load_windows_idx( int n_nuclides, int * n_windows )
{
	int * windows_idx = (int *) malloc(n_nuclides * sizeof(int));

	int j = 0;
	for (int i=0; i<n_nuclides; i++)
	{
		windows_idx[i] = j;
		j += n_windows[i];
	}

	return windows_idx;
}
