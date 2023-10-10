#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Include sys/time.h for gettimeofday
#include <pthread.h>
#include <unistd.h>

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

    int i = 0;

    // Perform 3x loop unrolling
    for (; i < len - 2; i += 3) {
        result *= a[i] * a[i + 1] * a[i + 2];
    }

    // Handle any remaining elements
    for (; i < len; i++) {
        result *= a[i];
    }

    return result;
}

// Function for computing the product of an array of n double-precision numbers
// utilizing 5x loop unrolling
double multiplyWith5xLoopUnrolling(double* a, int len) {
    volatile double result = 1.0;

    int i = 0;

    // Perform 5x loop unrolling
    for (; i < len - 4; i += 5) {
        result *= a[i] * a[i + 1] * a[i + 2] * a[i + 3] * a[i + 4];
    }

    // Handle any remaining elements
    for (; i < len; i++) {
        result *= a[i];
    }

    return result;
}

// Function for computing the product of an array of n double-precision numbers
// utilizing 7x loop unrolling
double multiplyWith7xLoopUnrolling(double* a, int len) {
    volatile double result = 1.0;

    int i = 0;

    // Perform 7x loop unrolling
    for (; i < len - 6; i += 7) {
        result *= a[i] * a[i + 1] * a[i + 2] * a[i + 3] * a[i + 4] * a[i + 5] * a[i + 6];
    }

    // Handle any remaining elements
    for (; i < len; i++) {
        result *= a[i];
    }

    return result;
}

//Function for the first thread
void* thread1_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
     printf("Process 1 done\n");
                    printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");

    return result_ptr;
}

//Function for the second thread
void* thread2_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
        printf("Process 2 done\n");
                       printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");

    
    return result_ptr;
}

//Function for the third thread
void* thread3_function(void* arg) {
    volatile double result = 1.0;

    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }

    // To return a double value, you can allocate memory for it and return a pointer
    double* result_ptr = (double*)malloc(sizeof(double));
    *result_ptr = result;
          printf("Process 3 done\n");
                         printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
          

    
    return result_ptr;
}

#define POOL_SIZE 200000000  // Total size of the memory pool
#define CHUNK_SIZE 100000000  // Size of each memory chunk (int array)

// Memory pool structure
typedef struct MemoryPool {
    int* pool;
    int chunkSize;
    int numChunks;
    int* freeList;
    int freeIndex;
} MemoryPool;

// Function to create a memory pool
MemoryPool* createMemoryPool(int poolSize, int chunkSize) {
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    pool->pool = (double*)malloc(poolSize * sizeof(double));
    pool->chunkSize = chunkSize;
    pool->numChunks = poolSize / chunkSize;
    pool->freeList = (int*)malloc(pool->numChunks * sizeof(int));
    for (int i = 0; i < pool->numChunks; i++) {
        pool->freeList[i] = i;
    }
    pool->freeIndex = 0;
    return pool;
}

// Function to allocate memory from the memory pool
int* allocateFromPool(MemoryPool* pool) {
    if (pool->freeIndex >= pool->numChunks) {
        return NULL; // Memory pool is exhausted
    }
    int index = pool->freeList[pool->freeIndex++];
    return &(pool->pool[index * pool->chunkSize]);
}

// Function to deallocate memory back to the memory pool
void deallocateToPool(MemoryPool* pool, int* ptr) {
    if (ptr == NULL) {
        return; // Invalid pointer
    }
    int* p = ptr;
    int index = (p - pool->pool) / pool->chunkSize;
    if (index < 0 || index >= pool->numChunks) {
        return; // Pointer does not belong to this pool
    }
    pool->freeList[--pool->freeIndex] = index;
}

// Function to destroy the memory pool
void destroyMemoryPool(MemoryPool* pool) {
    free(pool->freeList);
    free(pool->pool);
    free(pool);
}

//Function for the fourth thread
MemoryPool* pool ;  double* arr1; double* arr2;
void* thread4_function(void* arg) {
  //pool = 
    // Allocate and use memory from the pool
          struct timeval s1, e1;
    double ty = 0.0;
    
    gettimeofday(&s1, NULL);
    mult(arr1, CHUNK_SIZE);
    mult(arr2, CHUNK_SIZE);
    gettimeofday(&e1, NULL);
    ty = (double)(e1.tv_usec - s1.tv_usec) / 1000000.0 +
                     (double)(e1.tv_sec - s1.tv_sec);
    printf("  %f seconds elapsed for function with NO loop unrolling\n", ty);
        printf("Process 4.1 done\n");
           printf("Process 4.2 done\n");
                  printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");


}

//Function for the fifth thread
void* thread5_function(void* arg) {
         struct timeval s1, e1;
    double ty = 0.0;
    gettimeofday(&s1, NULL);
    multWithLoop3xUnrolling(arr1, CHUNK_SIZE);
    multWithLoop3xUnrolling(arr2, CHUNK_SIZE);
    gettimeofday(&e1, NULL);
    ty = (double)(e1.tv_usec - s1.tv_usec) / 1000000.0 +
                      (double)(e1.tv_sec - s1.tv_sec);
    printf("  %f seconds elapsed for function with 3x loop unrolling\n", ty);
        printf("Process 5.1 done\n");
           printf("Process 5.2 done\n");
               printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");

}

void* thread6_function(void* arg) {
         struct timeval s1, e1;
    double ty = 0.0;
    gettimeofday(&s1, NULL);
    multiplyWith5xLoopUnrolling(arr1, CHUNK_SIZE);
   multiplyWith5xLoopUnrolling(arr2, CHUNK_SIZE);
    gettimeofday(&e1, NULL);
    ty = (double)(e1.tv_usec - s1.tv_usec) / 1000000.0 +
                      (double)(e1.tv_sec - s1.tv_sec);
    printf("  %f seconds elapsed for function with 5x loop unrolling\n", ty);
         printf("Process 6.1 done\n");
            printf("Process 6.2 done\n");
                printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");


}

void* thread7_function(void* arg) {
         struct timeval s1, e1;
    double ty = 0.0;
    gettimeofday(&s1, NULL);
    multiplyWith7xLoopUnrolling(arr1, CHUNK_SIZE);
    multiplyWith7xLoopUnrolling(arr2, CHUNK_SIZE);
    gettimeofday(&e1, NULL);
    ty = (double)(e1.tv_usec - s1.tv_usec) / 1000000.0 +
                      (double)(e1.tv_sec - s1.tv_sec);
    printf("  %f seconds elapsed for function with 7x loop unrolling\n", ty);
         printf("Process 7.1 done\n");
            printf("Process 7.2 done\n");
                printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");


}

//Function without any threading
void without() {
    volatile double result = 1.0;
    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }
    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }
    for (int i = 0; i < 100000000; i++) {
        result *= 11.0;
    }
    return result;
}

int main() {
               printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
    //Threading 
    pthread_t thread1, thread2,thread3,thread4,thread5,thread6,thread7;
    pool = createMemoryPool(POOL_SIZE, CHUNK_SIZE);
    arr1 = allocateFromPool(pool);
    arr2 = allocateFromPool(pool);
    for (int i = 0; i < 100000000; i++) {
        arr1[i] = 1.00001;
        arr2[i] = 1.00001;
    }
    struct timeval s1, e1;
    // Create  threads
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);
    pthread_create(&thread3, NULL, thread3_function, NULL);
    pthread_create(&thread4, NULL, thread4_function, NULL);
    pthread_create(&thread5, NULL, thread5_function, NULL);
    pthread_create(&thread6, NULL, thread6_function, NULL);
    pthread_create(&thread7, NULL, thread7_function, NULL);

    //Overall time calculation 
    gettimeofday(&s1, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);

    gettimeofday(&e1, NULL);
                   printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
printf(" Overall time used by code is : %f " ,((double)(e1.tv_usec - s1.tv_usec) / 1000000.0 + (double)(e1.tv_sec - s1.tv_sec)));
               printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
    deallocateToPool(pool, arr1);
    deallocateToPool(pool, arr2);

    

         while (1) {
        if (_kbhit()) {
            char c = _getch();
            if (c == 'd' || c == 'D') {
                break; // Exit the loop when 'd' is pressed
            }
        }
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("\n");
    return 0;
}