/* Author Ma Weijian 
 * 2017-8-1
 *
 * Transpose matrix in-place
 *
 * TODO $ gcc -o transposeInt transposeInt.c
 *      For transpose matrix[3][10]	$ ./tranpose 3 10
 *      For transpose matrix[100][100]	$ ./tranpose 100 100
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int M;
int N;

int ** a;
int ** aT;

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

int ** generate_int_matrixT( int **matrix, int n, int m)
{
	  int i;
	  int **matrixT;

	  if((matrixT = malloc(sizeof(int *) * n)) == NULL){
	    printf("Out of memory, exit.\n");
	    exit(1);
	  }


	  for ( i = 0 ; i < n ; i++ ) {
	    matrixT[i] = (int *)((&matrix[0][0])) + i*m;
	  }

	  return matrixT;
}

int push(int i,int n,int m)   
{
	return((i%m)*n + i/m);
}

int pull(int i,int n,int m)    
{
	return((i%n)*m + i/n);
}

void movedata(int *data, int i, int n, int m)
{
	int index;

	int temp = *(data + i);

	int cur = i;
	int pre = pull(cur, n, m);
	while(pre != i)
	{
		data[cur] = data[pre];
		cur = pre;
		pre = pull(cur, n, m);
	}
	data[cur] = temp;
}


int **transpose(int **matrix, int n, int m)
{
	if(n == m)
	{
		int i,j;
	    int temp;
	    for(i = 0; i<M ; i++)
	    	for(j = i+1; j<M ; j++)
	    	{
	    		temp = matrix[j][i];
	    		matrix[j][i] = matrix[i][j];
	    		matrix[i][j] = temp;
	    	}
	    return(matrix);
	}  

	int *data = (int *)(matrix + n);

	int i;
	for(i=0; i<n*m; i++)
	{
		int next = push(i, n, m);

		while(next > i)
		{
			next = push(next, n, m);
		}

		if(next == i)
		{
			movedata(data, i, n, m);
		}
	}

    aT = generate_int_matrixT(matrix,m,n);
    return(aT);
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

     start = clock();

    //printf("Before:\n");
    //printMatrix(a,N,M);

    aT = transpose(a, N, M);

    //printf("After:\n");
    //printMatrix(aT,M,N);

    end = clock();

    printf("Time cost = %ld us.\n",(end - start)*1000*1000/CLOCKS_PER_SEC);

    exit(0);
}


