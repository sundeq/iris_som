#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ENTRIES 150
#define DOUBLE_STR_LEN 3
#define MAX_CSV_LINE_LEN 32
#define MAX_TYPE_LEN 15
#define N_ATTRIBUTES 4

// A unit of data from iris dataset.
typedef struct
{
    char label[MAX_TYPE_LEN];
    double input[N_ATTRIBUTES];
} iris_du;

void parse_csv_line(iris_du *idu, char *line);
void get_csv_lines(char *csv_lines[], int max_line_len, char *csv_file);

int main(int argc, char *argv[])
{
    int i;
    char *csv_file = "resources/iris.data";
    char *csv_lines[N_ENTRIES];
    iris_du *idu_array[N_ENTRIES];
    
    get_csv_lines(csv_lines, MAX_CSV_LINE_LEN, csv_file);
    
    for (i = 0; i < N_ENTRIES; i++)
    {
	idu_array[i] = malloc(sizeof(iris_du));
        parse_csv_line(idu_array[i], csv_lines[i]);
    }

}

void get_csv_lines(char *csv_lines[], int max_line_len, char *csv_file)
{
    int i;
    char line_buffer[max_line_len];
    FILE *file;
    file = fopen(csv_file, "r");
    i = 0;
    if (file)
    {
        while ( fgets(line_buffer, max_line_len, file) != NULL)
	{
	    if (strlen(line_buffer) != 1)
	    {
		csv_lines[i] = malloc(max_line_len*sizeof(char));
	        strcpy(csv_lines[i], line_buffer);
	        i++;
	    }
	}
    }
}

void parse_csv_line(iris_du *idu, char *line)
{
    int i;

    char *p;
    p = strtok(line, ",");

    i = 0;
    while (p != NULL)
    {
	if (i == N_ATTRIBUTES)
	{
	    strcpy(idu->label, p);
	}
	else
	{
	    idu->input[i] = (double) atof(p);
	    i++;
	}
        p = strtok(NULL, ",");
    }
}
