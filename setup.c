#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_WEIGHTS 4

typedef struct
{
    int x, y; // Coordinates in node lattice.
    double weights[N_WEIGHTS]; // Weights of the node.
} koho_node;

koho_node* init_koho_node(int x, int y, int n_weights);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    koho_node *kn = init_koho_node(0, 0, N_WEIGHTS);
    printf("x: %d, y: %d\n", kn->x, kn->y);
    int i;
    for (i =  0; i < N_WEIGHTS; i++)
        printf("w%d: %f\n", i, kn->weights[i]);
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
