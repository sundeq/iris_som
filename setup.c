#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "data_setup.h"

#define LATTICE_ROWS 4
#define LATTICE_COLS 4

typedef struct
{
    int x, y; // Coordinates in node lattice.
    double weights[N_ATTRIBUTES]; // Weights of the node.
} koho_node;


koho_node* init_koho_node(int x, int y, int n_weights);
void setup_koho_lattice(int n_nodes, int rows, int cols, int n_weights, koho_node *kn_lattice[n_nodes]);
void train(int epochs, int n_nodes, int n_weights, int rows, int cols, koho_node *kn_lattice[n_nodes], int idu_array_len, iris_du *idu_array[idu_array_len]);
double euclid_dist(int n, double x[n], double y[n]);
void training_round(int n_weights, int n_rows, int n_cols, koho_node *kn_lattice[n_rows*n_cols], iris_du *input_example);
//double gauss_neigh_func(lr_rate, std_dev, lattice_dist);

int main(int argc, char *argv[])
{
    int n_nodes = LATTICE_ROWS * LATTICE_COLS;
    int epochs = 5;

    koho_node *kn_lattice[n_nodes];
    setup_koho_lattice(n_nodes, LATTICE_ROWS, LATTICE_COLS, N_ATTRIBUTES, kn_lattice);
    
    iris_du *idu_array[N_ENTRIES];
    init_iris_data(idu_array);
    train(epochs, n_nodes, N_ATTRIBUTES, LATTICE_ROWS, LATTICE_COLS, kn_lattice, N_ENTRIES, idu_array); 
}

void setup_koho_lattice(int n_nodes, int rows, int cols, int n_weights, koho_node *kn_lattice[n_nodes])
{
    // Random seed
    srand(time(NULL));
    int i, j, w;
    w = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
	{
	    kn_lattice[w] = init_koho_node(i, j, n_weights);
	    w++;
	}
    }
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

void train(int epochs, int n_nodes, int n_weights, int rows, int cols, koho_node *kn_lattice[n_nodes], int idu_array_len, iris_du *idu_array[idu_array_len])
{
    iris_du *tmp_input_vector; 
    int i;
    
    double radius;
    double original_radius = n_rows;
    double time_constant = epochs / log(sigma_0);

    for (i = 0; i < epochs; i++)
    { 
        tmp_input_vector = idu_array[rand() % idu_array_len];
        radius = neighbourhood_radius(i, original_radius, time_constant);	
	printf("Epoch: %d, Input Vector: %f %f %f %f\n", i+1, tmp_input_vector->input[0], tmp_input_vector->input[1], tmp_input_vector->input[2], tmp_input_vector->input[3]);
        training_round(n_weights, rows, cols, kn_lattice, tmp_input_vector, radius);
    }
}

void training_round(int n_weights, int n_rows, int n_cols, koho_node *kn_lattice[n_rows*n_cols],
		    iris_du *input_example)
{
    int i, j, w, bmu_i;
    double tmp_dist, smallest_dist;

    // Find index of BMU.
    w = 0;
    smallest_dist = 1000; // Just set to a really large integer.
    for (i = 0; i < n_rows; i++)
    {
        for (j = 0; j < n_cols; j++)
	{
	    tmp_dist = euclid_dist(n_weights, kn_lattice[w]->weights, input_example->input);
	    if (tmp_dist < smallest_dist) {
		    smallest_dist = tmp_dist;
	            bmu_i = w;
	    }
	    printf("tmp_dist: %f, w:%d\n", tmp_dist, w);
	    w++;
	}
    }


}

double euclid_dist(int n, double x[n], double y[n])
{
    
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += pow(x[i] - y[i], 2.0);
    }
    return sqrt(sum);
}

void get_affected_node_indices(int n_nodes, koho_node *bmu_node, koho_node *kn_lattice[n_rows*n_cols], int node_indices[n_nodes], double neighbourhood_radius)
{
    int i;
    int w;
    double *kn;
    double tmp_x;
    double tmp_y;

    double bmu_x = (double) bmu_node->x;
    double bmu_y = (double) bmu_node->y;

    w = 0;
    for (i = 0; i < n_nodes; i++)
    {
         kn = kn_lattice[i];
	 if (euclid_dist() < neigbourhood_radius){
             node_indices[w] = i;
	     w++;
	 }

    }
}

/* Calculate current neighbourhood radius using exponential decay. */
double neigbourhood_radius(int time, double original_radius, double time_constant) {
    
    double exp_arg;
    
    exp_arg = -( time / time_constant );
    return original_radius * exp(exp_arg);	
}

/*
double gauss_neigh_func(double lr_rate, double std_dev, double lattice_dist)
{
    double a;
    double exp_arg;

    exp_arg = ( pow(lattice_dist, 2.0) / (2 * pow(std_dev, 2.0)) );
    a = lr_rate * exp(exp_args);

    return a;

}
*/
