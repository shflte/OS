#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREAD 20

using namespace std;

# define MAX 500

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

long long sum_add[NUM_THREAD] = {0};
long long sum_mul[NUM_THREAD] = {0};

long long sum_C = 0, sum_D = 0;
int part = 0;

void* add_mul(void* arg)
{
    // Each thread computes sum of 1/4th of array
    int thread_part = part++;

    cout << "thread part: " << thread_part << endl;

    for (int i = thread_part * (MAX / NUM_THREAD); i < (thread_part + 1) * (MAX / NUM_THREAD); i++) {
        // addition
        for (int j = 0; j < MAX; j++){
            sum_add[thread_part] += matA[i][j] + matB[i][j];
        }   
        // multiplication
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                sum_mul[thread_part] += matA[i][k] * matB[k][j];
            }
        }
    }

    return (void*)NULL;
}

int main()
{
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    pthread_t threads[NUM_THREAD];

    // create threads
    for (int i = 0; i < NUM_THREAD; i++)
        pthread_create(&threads[i], NULL, add_mul, (void*)NULL);

    // join threads
    for (int i = 0; i < NUM_THREAD; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < NUM_THREAD; i++) {
        cout << "add: " << sum_add[i] << "; mult: " <<  sum_mul[i] << endl;
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        sum_C += sum_add[i];
        sum_D += sum_mul[i];
    }

    cout << sum_C << endl;
    cout << sum_D << endl;

    return 0;
}
