#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int numOfRow = 7;
const int numOfCol = 7;
int board[numOfRow][numOfCol];
int rowDelta[4] = {0, 0, -2, 2};
int colDelta[4] = {2, -2, 0, 0};
struct pawns
{
    int col;
    int row;
};
struct moves
{
    int Row;
    int Col;
    int moveNumber;
};
void answerConvertor(const vector<moves> &answer)
{
    for (int i = 0; i < answer.size(); i++)
    {
        switch (answer[i].Row)
        {
        case 0:
            cout << 'A';
            break;
        case 1:
            cout << 'B';
            break;
        case 2:
            cout << 'C';
            break;
        case 3:
            cout << 'D';
            break;
        case 4:
            cout << 'E';
            break;
        case 5:
            cout << 'F';
            break;
        case 6:
            cout << 'G';
            break;
        }
        cout << answer[i].Col + 1 << ' ';
        switch (answer[i].moveNumber)
        {
        case 0:
            cout << "RIGHT" << endl;
            break;
        case 1:
            cout << "LEFT" << endl;
            break;
        case 2:
            cout << "UP" << endl;
            break;
        case 3:
            cout << "DOWN" << endl;
            break;
        }
    }
}
int numOfPawns()
{
    int counter = 0;
    for (int i = 0; i < numOfRow; i++)
    {
        for (int j = 0; j < numOfCol; j++)
        {
            if (board[i][j] == 1)
            {
                counter++;
            }
        }
    }
    return counter;
}
bool solve(int curRow, int curCol, int pawnsCounter, vector<moves> &answer)
{
    int result = numOfPawns();
    if (board[3][3] == 1 && result == 1)
    {

        return true;
    }
    for (int i = 0; i < 4; i++)
    {
        int newRow = rowDelta[i] + curRow;
        int newCol = colDelta[i] + curCol;
        if (newRow >= numOfRow || newCol >= numOfCol)
        {
            continue;
        }
        if (board[newRow][newCol] != 0)
        {
            continue;
        }
        if (i == 0 && board[newRow][newCol - 1] != 1)
        {
            continue;
        }
        if (i == 1 && board[newRow][newCol + 1] != 1)
        {
            continue;
        }
        if (i == 2 && board[newRow + 1][newCol] != 1)
        {
            continue;
        }
        if (i == 3 && board[newRow - 1][newCol] != 1)
        {
            continue;
        }
        board[newRow][newCol] = 1;

        board[curRow][curCol] = 0;
        struct moves move;
        move.Col = curCol;
        move.Row = curRow;
        switch (i)
        {
        case 0:
            board[newRow][newCol - 1] = 0;
            move.moveNumber = 0;
            break;
        case 1:
            board[newRow][newCol + 1] = 0;
            move.moveNumber = 1;
            break;
        case 2:
            board[newRow + 1][newCol] = 0;
            move.moveNumber = 2;
            break;
        case 3:
            board[newRow - 1][newCol] = 0;
            move.moveNumber = 3;
            break;
        }
        answer.push_back(move);
        for (int i = 0; i < numOfRow; i++)
        {
            for (int j = 0; j < numOfCol; j++)
            {
                if (board[i][j] == 1)
                {

                    if (solve(i, j, pawnsCounter, answer))
                    {
                        return true;
                    }
                }
            }
        }
        board[newRow][newCol] = 0;
        board[curRow][curCol] = 1;
        answer.pop_back();
        switch (i)
        {
        case 0:
            board[newRow][newCol - 1] = 1;
            break;
        case 1:
            board[newRow][newCol + 1] = 1;
            break;
        case 2:
            board[newRow + 1][newCol] = 1;
            break;
        case 3:
            board[newRow - 1][newCol] = 1;
            break;
        }
    }

    return false;
}
int main()
{
    int i = 0;
    string input;
    int pawnsCounter = 0;
    vector<moves> answer;
    vector<pawns> pawn;
    for (i = 0; i < 7; i++)
    {
        getline(cin, input);
        for (int j = 0; j < numOfCol; j++)
        {
            if (input[j] == 'X')
            {
                board[i][j] = -1;
            }
            else if (input[j] == 'O')
            {
                board[i][j] = 0;
            }
            else if (input[j] == 'N')
            {
                struct pawns pawn1;
                pawn.push_back(pawn1);
                board[i][j] = 1;
                pawn[pawnsCounter].col = j;
                pawn[pawnsCounter].row = i;
                pawnsCounter++;
            }
        }
    }
    for (i = 0; i < pawn.size(); i++)
    {
        bool result = solve(pawn[i].row, pawn[i].col, pawnsCounter, answer);
        if (result)
        {
            answerConvertor(answer);
            return 0;
        }
    }

    cout << "Loser";

    return 0;
}