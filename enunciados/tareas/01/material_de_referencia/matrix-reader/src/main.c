// Copyright 2022 Jose Andres Mena <jose.menaarias@ucr.ac.cr>
/*
* Reads a matrix from an input file with the format:
* - Line 1 contains an integer N with the number of rows
* - Line 2 contains an integer M with the number of columns
* - The next N lines contain strings of M characters representing the matrix value
* You can send the input file as argument. Example:
*   $ ./bin/matrix-reader ./test/input00.txt
* Or you can send it using standard input. Example:
*   $ ./bin/matrix-reader < ./test/input00.txt
*/
#include "reader.h"

void print_matrix(matrix_t* matrix);

int main(int argc, char** args) {
    FILE* fptr = stdin;

    if (argc == 2) {
        fptr = fopen(args[1], "r");

        if (!fptr) {
            fprintf(stderr, "Invalid file\n");
            return EXIT_FAILURE;
        }
    }

    matrix_t *matrix = read_matrix(fptr);

    if (!matrix) {
        fprintf(stderr, "Invalid file content.\n");
        return EXIT_FAILURE;
    }

    print_matrix(matrix);

    destroy_matrix(matrix);

    return EXIT_SUCCESS;
}

void print_matrix(matrix_t* matrix) {
    for (int i = 0; i < matrix->num_rows; ++i) {
        printf("%s\n", matrix->value[i]);
    }
}
