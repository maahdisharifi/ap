#include <iostream>
using namespace std;
int sCounter = 0;
int rowDelta[2] = {1, 0};
int colDelta[2] = {0, 1};
bool safeToGo(int row, int col, int size)
{
    if (col > row || col > size || row > size)
    {
        return false;
    }
    return true;
}

void solve(int row, int col, int size)
{
    if (row == size && col == size)
    {
        sCounter++;
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        int newRow = row + rowDelta[i];
        int newCol = col + colDelta[i];
        if (safeToGo(newRow, newCol, size))
        {
            solve(newRow, newCol, size);
        }
    }
}

int main()
{

    int size;
    cin >> size;
    int board[size][size];
    solve(0, 0, size);
    cout << sCounter;
    return 0;
}