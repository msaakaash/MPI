#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16  // Array size

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot element
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort function
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    int data[N], local_size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_size = N / size;
    int local_data[local_size];

    // Master initializes data
    if (rank == 0) {

        printf("Original Array: ");
        for (int i = N-1; i>=0; i--) {
            data[i] = i; // Random numbers between 0-99
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    // Scatter the data among processes
    MPI_Scatter(data, local_size, MPI_INT, local_data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process sorts its portion
    quicksort(local_data, 0, local_size - 1);

    // Gather sorted subarrays back to master
    MPI_Gather(local_data, local_size, MPI_INT, data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Master merges sorted subarrays
    if (rank == 0) {
        printf("Partially Sorted (before merging): ");
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");

        // Final sorting after gather
        quicksort(data, 0, N - 1);

        printf("Final Sorted Array: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

