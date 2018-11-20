#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "data_setup.h"

#define LATTICE_ROWS 40
#define LATTICE_COLS 40

typedef struct
{
    int x, y; // Coordinates in node lattice.
    double weights[N_ATTRIBUTES]; // Weights of the node.
} koho_node;

koho_node* init_koho_node(int x, int y, int n_weights);
double euclid_dist(int n, double x[n], double y[n]);
double gauss_neigh_func(lr_rate, std_dev, lattice_dist);
void train(int epochs, int n_weights, int rows, int cols, koho_node *kn_lattice, iris_du *idu_array);
void training_round(int n_weights, int n_rows, int n_cols, koho_node *kn_lattice[n_rows*n_cols],
		    iris_du *input_example);

int main(int argc, char *argv[])
{
    n_nodes = LATTICE_ROWS * LATTICE_COLS;
    koho_node *kn_lattice[n_nodes];
    int i, j, w;

    srand(time(NULL));
    koho_node *kn = init_koho_node(0, 0, N_ATTRIBUTES);
    printf("x: %d, y: %d\n", kn->x, kn->y);
    for (i =  0; i < N_ATTRIBUTES; i++)
        printf("w%d: %f\n", i, kn->weights[i]);
    
    iris_du *idu_array[N_ENTRIES];
    init_iris_data(idu_array);
    
    double dtemp[4];
    memcpy(dtemp, idu_array[20]->input, N_ATTRIBUTES*sizeof(double));
    printf("%f %f %f %f", dtemp[1], dtemp[1], dtemp[2], dtemp[3]);
    printf("edist: %f", euclid_dist(N_ATTRIBUTES, kn->weights, dtemp));

    w = 0;
    for (i = 0; i < LATTICE_ROWS; i++)
    {
        for (j = 0; j < LATTICE_COLS; j++)
	{
	    kn_lattice[w] = init_koho_node(i, j, N_ATTRIBUTES);
	}
    }
}

void train(int epochs, int n_weights, int rows, int cols, koho_node *kn_lattice, iris_du *idu_array)
{
    int i;
    for (i = 0; i < epochs; i++)
    {
        training_round(n_weights, rows, cols, kn_lattice);
    }
}

void training_round(int n_weights, int n_rows, int n_cols, koho_node *kn_lattice[n_rows*n_cols],
		    iris_du *input_example)
{
    int i, j, w, bmu_i;
    double tmp_dist, smallest_dist;

    // Find index of BMU.
    w = 0;
    smallest_dist = 0.0;
    for (i = 0; i < n_rows; i++)
    {
        for (j = 0; j < n_cols, j++)
	{
	    tmp_dist = euclid_dist(n_weights, kn_lattice[w]->weights, input_example->input);
	    if (tmp_dist < smallest_dist)
		    smallest_dist = tmp_dist;
	            bmu_i = w;
	    w++;
	}
    }
}

double gauss_neigh_func(double lr_rate, double std_dev, double lattice_dist)
{
    double a;
    double exp_arg;

    exp_arg = ( pow(lattice_dist, 2.0) / (2 * pow(std_dev, 2.0)) );
    a = lr_rate * exp(exp_args);

    return a;

}

koho_node* init_koho_node(int x, int y, int n_weights)
{
    int i;
    double tmp_w;

    koho_node *kn = malloc(sizeof(koho_node));

    kn->x = x;
    kn->y = y;

    for (i = 0; i < n_weights; i++)
    {
        tmp_w = (double) rand() / RAND_MAX;
        kn->weights[i] = tmp_w; 
    }
    return kn;
}

double euclid_dist(int n, double x[n], double y[n]){
    
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += pow(x[i] - y[i], 2.0);
    }
    return sqrt(sum);
}
