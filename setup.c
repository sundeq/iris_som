#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOUBLE_STR_LEN 3
#define MAX_TYPE_LEN 15
#define N_ATTRIBUTES 4

// A unit of data from iris dataset.
typedef struct
{
    char type[MAX_TYPE_LEN];
    double input[N_ATTRIBUTES];
} iris_du;

void parse_csv_line(iris_du *idu, char *line);

int main(int argc, char *argv[])
{
    char test_line[] = "6.1,3.0,4.6,1.4,Iris-versicolor";
    iris_du *idu = malloc(sizeof(iris_du));
    parse_csv_line(idu, test_line);
    printf("%s\n", idu->type);
    for (int i = 0; i < 4; i++)
        printf("inp_i: %f\n", idu->input[i]);
}

void parse_csv_line(iris_du *idu, char *line)
{
    int i;
    printf("Test line: %s\n", line);

    char *p;
    p = strtok(line, ",");

    i = 0;
    while (p != NULL)
    {
	if (i == N_ATTRIBUTES)
	{
	    strcpy(idu->type, p);
	}
	else
	{
	    idu->input[i] = (double) atof(p);
	    i++;
	}
	printf("p: %s\n", p);
        p = strtok(NULL, ",");
    }
}
