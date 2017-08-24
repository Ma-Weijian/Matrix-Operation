/* Author Ma Weijian 
 * 2017-8-16
 *
 * Matrix multiply line by line. The program 
 * transposes the right matrix inplace before multiplication,    
 * restores the right matrix after multiplication.
 *
 * SpeedUp trick: The program transfer matrix into array. 
 *
 * TODO $ gcc -o mSpeedUPV2 matrixMulSpeedUPV2.c
 *      For multipling matrix A[10][9] and B[9][8]	$ ./mSpeedUPV2 10 9 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

int M;
int N;
int K;

int ** a;
int ** b;
int ** c;

int ** bT;

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

	int temp = data[i];

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


void transpose(int **matrix, int n, int m)
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
	}  

	int *data = (int *)(& matrix[0][0]);

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
}

void display2DIntArray(int **matrix,int n,int m)
{
    	int i;
    	int j;

    	for(i = 0; i < n; i++)
    	{   
    	    for(j = 0; j < m; j++)  
	        printf("%-10d",matrix[i][j]);
            printf("\n");
        }
}

void vectorXmatrix(int *src,int *des, int *matrixData, int RNum, int CNum)
{
    int row = 0;
    int base = 0;
    int j;

    while(row < RNum)
    {
        des[row] = 0;
        for(j=0; j <CNum ; j++){
            des[row] += matrixData[base++] * src[j]; 
        }
        row++;
    }    
}


int main(argc,argv)
int argc;
char **argv;
{
    	int i,j;
        time_t start,end;

    	N = atoi(argv[1]);
   	M = atoi(argv[2]);
    	K = atoi(argv[3]);

    	a = generate_int_matrix(N,M);
    	b = generate_int_matrix(M,K);
    	c = generate_int_matrix(N,K);

    	for(i = 0; i<N ; i++)
    	    for(j = 0; j<M ; j++)
	        a[i][j] = i;

    	for(i = 0; i<M ; i++)
    	    for(j = 0; j<K ; j++)
	        b[i][j] = j;

    	for(i = 0; i<N ; i++)
    	    for(j = 0; j<K ; j++)
	        c[i][j] = 0;

	start = clock();

    	transpose(b, M, K);  

    	int n = N;   
    	int m = M;
    	int k = K;   

    	int *aBase = &a[0][0];
    	int *bBase = &b[0][0];
    	int *cBase = &c[0][0];

    	for(i = 0; i<N ; i++)
    	{
	    vectorXmatrix(aBase,cBase, bBase, k, m);      
            aBase += m;   
	    cBase += k;    
    	}          
    
    	transpose(b, K, M);

      	end = clock();

    	display2DIntArray(c,N,K);

    	printf("Time cost = %ld us.\n",(end - start)*1000*1000/CLOCKS_PER_SEC);

    	exit(0);
}


