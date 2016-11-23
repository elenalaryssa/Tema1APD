#include <iostream>
#include <fstream>

using namespace std;



int main(int argc, char *argv[])
{	
	int C, L, N;
	int i, j, k;
	int neigh, x = 0;

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



	for(k = 1; k <= N; k++)
	{
		//copy matrix
		for (i = 0; i < L; i++)
			for (j = 0; j < C; j++)
			{
				if (x == 0) {
					temp_matrix[i][j] = matrix[i][j];
				}
				else
				{
					matrix[i][j] = temp_matrix[i][j];
				}
			}
		x = 1;
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
		for (i = 0; i < C; i++)
		{
			matrix[0][i] = matrix[L-2][i]; //linia de sus
			matrix[L-1][i] = matrix[1][i]; //linia de jos
		}
		for (i = 0; i < L; i++)
		{
			matrix[i][0] = matrix[i][C-2]; //linia din stanga
			matrix[i][C-1] = matrix[i][1]; //linia din dreapta
		}
	}

//print matrix
/*	for(i = 0; i < L; i++)
	{
		for(j = 0; j < C; j++)
			cout << matrix[i][j];
		cout << "\n";
	}
*/

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
