#include <iostream>
#include <fstream>
#include <omp.h>

#define OMP_NUM_THREADS 8

using namespace std;


int main(int argc, char *argv[])
{	
	//int omp_set_num_threads();
	int C, L, N;
	int i, j, k;
	int neigh, x = 0, chunk = 100;

	if (argc != 4)
	{
		printf("Incorrect number of arguments\n");
		return 0;
	}

	sscanf(argv[2], "%d", &N);

	ifstream rfile;
	ofstream wfile;
	rfile.open(argv[1]);
	wfile.open(argv[3]);
		
	if (!rfile.is_open()) 
	{
		wfile << "Unable to open file";
		return 0;
	}

	rfile >> L >> C;
	L += 2;
	C += 2;
	char **matrix = new char*[L];
	char **temp_matrix = new char*[L];
	


	for (i = 0; i < L; i++)
	{
		matrix[i] = new char[C];
		temp_matrix[i] = new char[C];
	}

//read matrix from file
	for(i = 1; i < L-1; i++){
		for(j = 1; j < C-1; j++)
		{
			rfile >> matrix[i][j];
		}
	}
		//omp_set_num_threads(OMP_NUM_THREADS);
	for(k = 0; k < N; k++)
	{
		#pragma omp parallel shared(neigh, matrix, temp_matrix) private(i,j)
		{
			//omp_set_num_threads(OMP_NUM_THREADS);
			//copy matrix
			#pragma omp for collapse(2)
				for (i = 0; i < L; i++)
					for (j = 0; j < C; j++)
						if (x == 0) 
							temp_matrix[i][j] = matrix[i][j];
					
						else
							matrix[i][j] = temp_matrix[i][j];
				x = 1;
				#pragma omp for private(j) reduction(+:neigh)
				for (i = 1; i < L-1; i++)
				{
					for (j = 1; j < C-1; j++)
					{
						neigh = 0;
						if (matrix[i-1][j-1] == 'X')
							neigh++;
						if (matrix[i-1][j] == 'X')
							neigh++;
						if (matrix[i-1][j+1] == 'X')
							neigh++;
						if (matrix[i+1][j-1] == 'X')
							neigh++;
						if (matrix[i+1][j] == 'X')
							neigh++;
						if (matrix[i+1][j+1] == 'X')
							neigh++;
						if (matrix[i][j-1] == 'X')
							neigh++;
						if (matrix[i][j+1] == 'X')
							neigh++;
						if ((matrix[i][j] == 'X' || matrix[i][j] == '.') && neigh < 2)
							temp_matrix[i][j] = '.';
						if (matrix[i][j] == 'X' && (neigh == 2 || neigh == 3))
							temp_matrix[i][j] = 'X';
						if ((matrix[i][j] == 'X' || matrix[i][j] == '.') && neigh > 3)
							temp_matrix[i][j] = '.';
						if (matrix[i][j] == '.' && neigh == 3)
							temp_matrix[i][j] = 'X';
					}
				}
				//BORDER

			#pragma omp for
			for (i = 0; i < C; i++)
			{
				temp_matrix[0][i] = temp_matrix[L-2][i]; //linia de sus
				temp_matrix[L-1][i] = temp_matrix[1][i]; //linia de jos
			}
			#pragma omp for
			for (i = 0; i < L; i++)
			{
				temp_matrix[i][0] = temp_matrix[i][C-2]; //linia din stanga
				temp_matrix[i][C-1] = temp_matrix[i][1]; //linia din dreapta
			}
		}
	}

//write matrix to file
	for(i = 1; i < L-1; i++)
	{
		for(j = 1; j < C-1; j++)
			wfile << temp_matrix[i][j] << " ";
		wfile << "\n";
	}
	
	for (i = 0; i < L; ++i)
	{
		delete [] matrix[i];
		delete [] temp_matrix[i];
	}

	delete [] matrix;
	delete [] temp_matrix;

	rfile.close();
	wfile.close();

	return 0;
}
