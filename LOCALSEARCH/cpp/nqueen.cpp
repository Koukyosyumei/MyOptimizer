#include <cmath>
#include <time.h>
#include <iostream>
using namespace std;

#define N 12

void shuffle(int ary[], int size)
{
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        int j = rand() % size;
        int t = ary[i];
        ary[i] = ary[j];
        ary[j] = t;
    }
}

bool isequal(int *state_1, int *state_2)
{
    for (int i = 0; i < N; i++)
        if (state_1[i] != state_2[i])
            return false;
    return true;
}

void copy_state(int *original_state, int *copy_state)
{
    for (int i = 0; i < N; ++i)
        copy_state[i] = original_state[i];
}

void print_state(int *state)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (state[i] == j)
                cout << "1"
                     << " ";
            else
                cout << "0"
                     << " ";
        }
        cout << endl;
    }
}

int culc_attacking_queens(int *state)
{
    int num_attacking_pair = 0;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            if (state[i] == state[j] || abs(state[i] - state[j]) == j - i)
                ++num_attacking_pair;
    return num_attacking_pair;
}

void get_best_neighbour_state(int *state)
{
    int best_value = culc_attacking_queens(state);
    int temp_value;

    int best_neighbour_state[N];
    copy_state(state, best_neighbour_state);
    int temp_neighbour_state[N];
    copy_state(state, temp_neighbour_state);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (j != state[i])
            {
                temp_neighbour_state[i] = j;
                temp_value = culc_attacking_queens(temp_neighbour_state);
                if (temp_value <= best_value)
                {
                    best_value = temp_value;
                    copy_state(temp_neighbour_state, best_neighbour_state);
                }
                copy_state(state, temp_neighbour_state);
            }
        }
    }

    copy_state(best_neighbour_state, state);
}

void nqueen_hillclimbing()
{
    int state[N]; //y2x
    int neighbour_state[N];

    for (int i = 0; i < N; ++i)
        state[i] = i;

    do
    {
        shuffle(state, N);
        copy_state(state, neighbour_state);
        do
        {
            copy_state(neighbour_state, state);
            get_best_neighbour_state(neighbour_state);
            if (isequal(state, neighbour_state))
                break;
            else if (culc_attacking_queens(state) == culc_attacking_queens(neighbour_state))
                shuffle(neighbour_state, N);
        } while (true);
    } while (culc_attacking_queens(state) != 0);
    print_state(state);
}

int main()
{
    clock_t start, end;
    nqueen_hillclimbing();
    end = clock();
    printf("time = %f[s]", (double)(end - start) / CLOCKS_PER_SEC);
}