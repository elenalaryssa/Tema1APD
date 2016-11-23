CC=g++
SER=g_serial
OMP=g_omp

all: $(SER) $(OMP)

serial: $(SER).cpp
	$(CC) -o $(SER) $(SER).cpp

parallel: $(OMP).cpp
	$(CC) -fopenmp -o $(OMP) $(OMP).cpp

clean:
	rm -f *.o *~ 
	rm -f $(SER) $(OMP)
