#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3

// Structure to hold thread data
struct ThreadData {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int result[MATRIX_SIZE][MATRIX_SIZE];
    int row;
    pthread_mutex_t mutex;  // Mutex for synchronization
};

// Function to calculate the square of a matrix row
void* calculateRowSquare(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    int row = data->row;

    // Calculate the square of the row
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            pthread_mutex_lock(&data->mutex);
            data->result[row][i] += data->matrix[row][j] * data->matrix[j][i];
            pthread_mutex_unlock(&data->mutex);
        }
    }

    pthread_exit(NULL);
}

int main() {
    struct ThreadData threadData[MATRIX_SIZE];
    pthread_t threads[MATRIX_SIZE];

    // Initialize the matrix and mutex
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Print the input matrix
    printf("Input matrix A is\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Create threads for each row
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            threadData[i].matrix[i][j] = matrix[i][j];
            threadData[i].result[i][j] = 0; // Initialize the result matrix
        }
        threadData[i].row = i;
        pthread_mutex_init(&threadData[i].mutex, NULL);  // Initialize the mutex
        if (pthread_create(&threads[i], NULL, calculateRowSquare, (void*)&threadData[i]) != 0) {
            fprintf(stderr, "Error creating thread\n");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&threadData[i].mutex);  // Destroy the mutex
    }

    // Print the result matrix
    printf("AxA matrix is\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%4d ", threadData[i].result[i][j]);
        }
        printf("\n");
    }

    return 0;
}