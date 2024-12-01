#include <iostream>
#include <mpi.h>
#include <cstring>

#define ROOT 0

#define MAX 500
#define MIN -500

void print_matrix(const int* matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            std::cout << matrix[i*columns+j] << " ";
        }
        std::cout << std::endl;
    }
}
void print_array(const int *array, int count, char sep = ' ') {
    for(int i = 0; i < count; i++) {
        std::cout << array[i] << sep;
    }
    std::cout << std::endl;
}

void fill_matrix(int* matrix, int rows, int columns) {
    srand(time(NULL));
    for(int i = 0; i < rows*columns; i++) {
        matrix[i] = rand() % (MAX - MIN) + MIN;
    }
}

int main(int argc, char** argv) {
    int *matrix = nullptr;
    int *min = nullptr;
    int ROWS = 4;
    int COLUMNS = 8;
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == ROOT) {
        if (argc == 3) {
            if(std::strcmp(argv[1], "-r") == 0) {
                ROWS = atoi(argv[2]);
            } else if(std::strcmp(argv[1], "-c") == 0) {
                COLUMNS = atoi(argv[2]);
            } else {
                std::cout << argv[1] << " unknown argument\n";
            }
        } else if(argc == 5) {
            if(std::strcmp(argv[1], "-r") == 0) {
                ROWS = atoi(argv[2]);
                if(std::strcmp(argv[3], "-c") == 0) {
                    COLUMNS = atoi(argv[4]);
                }
            } else if(std::strcmp(argv[1], "-c") == 0) {
                COLUMNS = atoi(argv[2]);
                if(std::strcmp(argv[3], "-r") == 0) {
                    ROWS = atoi(argv[4]);
                }
            }
        }
    }
    MPI_Bcast(&ROWS, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    MPI_Bcast(&COLUMNS, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    if(ROWS % size != 0) {
        if(rank == ROOT) {
            printf("%d(number of rows) must be divisible by %d (number of processes) with no remainder",ROWS, size);
        }
        MPI_Finalize();
        return -1;
    }
    if(rank == ROOT) {
        printf("Init matrix\n");
        matrix = new int[ROWS*COLUMNS];
        min = new int[ROWS];
        fill_matrix(matrix, ROWS, COLUMNS);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int true_rows = ROWS/size;
    int *local_min = new int[true_rows];
    int *local_matrix = new int[true_rows * COLUMNS];

    MPI_Scatter(matrix, true_rows * COLUMNS, MPI_INT, local_matrix, true_rows * COLUMNS, MPI_INT, ROOT, MPI_COMM_WORLD);


    for(int i = 0; i < true_rows; i++) {
        int row = rank*true_rows+i;
        local_min[i] = MAX;
        for(int j = 0; j < COLUMNS; j++) {
            if(local_matrix[i*COLUMNS+j] < local_min[i])
                local_min[i] = local_matrix[i*COLUMNS+j];
        }
//        printf("Rank: %d, min at index %d is %d\n", rank, row, local_min[row]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(local_min, true_rows, MPI_INT, min, true_rows, MPI_INT, ROOT, MPI_COMM_WORLD);
//    MPI_Reduce(local_min, min, ROWS, MPI_INT, MPI_MIN, ROOT, MPI_COMM_WORLD);
    delete[] local_matrix;
    delete[] local_min;
    if(rank == ROOT) {
        std::cout << "Matrix:" << std::endl;
        print_matrix(matrix, ROWS, COLUMNS);
        std::cout << "\nMIN:" << std::endl;
        print_array(min, ROWS, '\n');
        delete[] matrix;
        delete[] min;
    }
    MPI_Finalize();
    return 0;
}
