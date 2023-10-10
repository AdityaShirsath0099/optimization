#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Include sys/time.h for gettimeofday
#include <pthread.h>

// Function for computing the product of an array of n double-precision numbers
// NO loop unrolling
double mult(double* a, int len) {
    volatile double result = 1.0;

    for (int i = 0; i < len; i++) {
        result *= a[i];
    }
    return result;
}

// Function for computing the product of an array of n double-precision numbers
// utilizing 3x loop unrolling
double multWithLoop3xUnrolling(double* a, int len) {
    volatile double result = 1.0;

    for (int i = 0; i < len; i++) {
        result *= a[i];
    }
    return result;
}


// Function for computing the product of an array of n double-precision numbers
// utilizing 5x loop unrolling
double multiplyWith5xLoopUnrolling(double* a, int len) {
    volatile double result = 1.0;

    for (int i = 0; i < len; i++) {
        result *= a[i];
    }
    return result;
}


// Function for computing the product of an array of n double-precision numbers
// utilizing 7x loop unrolling
double multiplyWith7xLoopUnrolling(double* a, int len) {
    volatile double result = 1.0;

    for (int i = 0; i < len; i++) {
        result *= a[i];
    }
    return result;
}

void* thread1_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
    return result_ptr;
}

// Function to simulate Thread 2
void* thread2_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
    return result_ptr;
}

void* thread3_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
    return result_ptr;
}

void without() {
           printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
    volatile double result = 1.0;
    volatile double result2 = 1.0;
    volatile double result3 = 1.0;
    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }
    for (int i = 0; i < 100000000; i++) {
        result3 *= 11.0;
    }
    for (int i = 0; i < 100000000; i++) {
        result2 *= 11.0;
    }
     printf("Process 1, 2, 3 done\n");
            printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
    return result + result2 + result3;
}

int main() {
    // Create an array with the same data as in your Java code
 
    int SIZE = 100000000;
    double* arr = (double*)malloc(SIZE * sizeof(double));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 1.00001;
    }

    // Create another array with your desired data
    int SIZE2 = 100000000;
    double* arr2 = (double*)malloc(SIZE2 * sizeof(double));
    for (int i = 0; i < SIZE2; i++) {
        // Insert your array elements here
        arr2[i] = 2.0;
    }

    // Call the functions with the first set of data
    printf("Calling functions with first set of data:\n");


       printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
    struct timeval start_time1, end_time1;
    struct timeval final1;

        gettimeofday(&final1, NULL);
    gettimeofday(&start_time1, NULL);
    mult(arr, SIZE);
    gettimeofday(&end_time1, NULL);
    double tdiff1 = (double)(end_time1.tv_usec - start_time1.tv_usec) / 1000000.0 +
                     (double)(end_time1.tv_sec - start_time1.tv_sec);
    printf("  %f seconds elapsed for function with NO loop unrolling\n", tdiff1);

    struct timeval start_time3x1, end_time3x1;
    gettimeofday(&start_time3x1, NULL);
    multWithLoop3xUnrolling(arr, SIZE);
    gettimeofday(&end_time3x1, NULL);
    double tdiff3x1 = (double)(end_time3x1.tv_usec - start_time3x1.tv_usec) / 1000000.0 +
                      (double)(end_time3x1.tv_sec - start_time3x1.tv_sec);
    printf("  %f seconds elapsed for function with 3x loop unrolling\n", tdiff3x1);

    struct timeval start_time5x1, end_time5x1;
    gettimeofday(&start_time5x1, NULL);
    multiplyWith5xLoopUnrolling(arr, SIZE);
    gettimeofday(&end_time5x1, NULL);
    double tdiff5x1 = (double)(end_time5x1.tv_usec - start_time5x1.tv_usec) / 1000000.0 +
                      (double)(end_time5x1.tv_sec - start_time5x1.tv_sec);
    printf("  %f seconds elapsed for function with 5x loop unrolling\n", tdiff5x1);

    struct timeval start_time7x1, end_time7x1;
    gettimeofday(&start_time7x1, NULL);
    multiplyWith7xLoopUnrolling(arr, SIZE);
    gettimeofday(&end_time7x1, NULL);
    double tdiff7x1 = (double)(end_time7x1.tv_usec - start_time7x1.tv_usec) / 1000000.0 +
                      (double)(end_time7x1.tv_sec - start_time7x1.tv_sec);
    printf("  %f seconds elapsed for function with 7x loop unrolling\n", tdiff7x1);
           printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");

   printf("Process 4.1, 5.1 , 6.1, 7.1 done\n");
          printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
    // Call the functions with another set of data (arr2)
    printf("\nCalling functions with another set of data:\n");
  
    struct timeval start_time3, end_time3;
    gettimeofday(&start_time3, NULL);
    mult(arr2, SIZE2);
    gettimeofday(&end_time3, NULL);
    double tdiff3 = (double)(end_time3.tv_usec - start_time3.tv_usec) / 1000000.0 +
                    (double)(end_time3.tv_sec - start_time3.tv_sec);
    printf("  %f seconds elapsed for function with NO loop unrolling\n", tdiff3);

    struct timeval start_time3x3, end_time3x3;
    gettimeofday(&start_time3x3, NULL);
    multWithLoop3xUnrolling(arr2, SIZE2);
    gettimeofday(&end_time3x3, NULL);
    double tdiff3x3 = (double)(end_time3x3.tv_usec - start_time3x3.tv_usec) / 1000000.0 +
                      (double)(end_time3x3.tv_sec - start_time3x3.tv_sec);
    printf("  %f seconds elapsed for function with 3x loop unrolling\n", tdiff3x3);

    struct timeval start_time5x3, end_time5x3;
    gettimeofday(&start_time5x3, NULL);
    multiplyWith5xLoopUnrolling(arr2, SIZE2);
    gettimeofday(&end_time5x3, NULL);
    double tdiff5x3 = (double)(end_time5x3.tv_usec - start_time5x3.tv_usec) / 1000000.0 +
                      (double)(end_time5x3.tv_sec - start_time5x3.tv_sec);
    printf("  %f seconds elapsed for function with 5x loop unrolling\n", tdiff5x3);

    struct timeval start_time7x3, end_time7x3;
    gettimeofday(&start_time7x3, NULL);
    multiplyWith7xLoopUnrolling(arr2, SIZE2);
    gettimeofday(&end_time7x3, NULL);
    double tdiff7x3 = (double)(end_time7x3.tv_usec - start_time7x3.tv_usec) / 1000000.0 +
                      (double)(end_time7x3.tv_sec - start_time7x3.tv_sec);
    printf("  %f seconds elapsed for function with 7x loop unrolling\n", tdiff7x3);
           printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
     printf("Process 4.2, 5.2 ,6.2, 7.2 done\n");
            printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");

    // Free allocated memory
    free(arr);
    free(arr2);

  
   struct timeval s1,e1;

    // Now without threads
       gettimeofday(&s1, NULL);
    without();
     gettimeofday(&e1, NULL);
    double t2 = (e1.tv_sec - s1.tv_sec) + (e1.tv_sec - s1.tv_sec) / 1e9;
    printf("Calling function without Threading\n");
    printf("  %lf seconds elapsed\n", t2);
           printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");

    printf(" Overall time used by code is : %f " ,((double)(e1.tv_usec - final1.tv_usec) / 1000000.0 + (double)(e1.tv_sec - final1.tv_sec)));
             printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
   printf("\n");
        while (1) {
        if (_kbhit()) {
            char c = _getch();
            if (c == 'd' || c == 'D') {
                break; // Exit the loop when 'd' is pressed
            }
        }
    }

    
  
    return 0;
}
