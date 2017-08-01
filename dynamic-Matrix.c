/* Author Ma Weijian 
 * 2017-8-1
 *
 * Generate dynamic matrix
 *
 * TODO $ gcc -o dynamic-Matrix dynamic-Matrix.c
 *      For generating matrix[3][10]	$ ./dynamic-Matrix 3 10
 *      For generating matrix[100][100]	$ ./dynamic-Matrix 100 100
 */

#include <stdio.h>
#include <stdlib.h>

int M;
int N;

int ** a;

int ** generate_int_matrix( int n, int m)
{
  int i;
  int **matrix;

  if((matrix = malloc(sizeof(int) * n * m +
		      sizeof(int *) * n	 )) == NULL){
    printf("Out of memory, exit.\n");
    exit(1);
  }
  for ( i = 0 ; i < n ; i++ ) {
    matrix[i] = (int *)(matrix + n) + i*m;
  }
  return matrix;
}

void printMatrix(int ** matrix,int n,int m)
{
	int i;
	int j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			printf("%d\t",matrix[i][j]);
		}
		printf("\n");
	}
}

int main(argc,argv)
int argc;
char **argv;
{
    int i,j,k;
    time_t start,end;

    N = atoi(argv[1]);
    M = atoi(argv[2]);

    a = generate_int_matrix(N,M);

    int count = 0;

    for(i = 0; i<N ; i++)
    	for(j = 0; j<M ; j++)
 	{
	    a[i][j] = count++;
	}

    printMatrix(a,N,M);

    exit(0);
}


