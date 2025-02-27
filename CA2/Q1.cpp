#include <iostream>
using namespace std;
int functionCounter = 0;
int max(int num1, int num2)
{

    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}
int min(int num1, int num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    return num2;
}
void solve(int nums[], int maxOrMin, int CurLocation, int preLocation, int size)
{

    if (CurLocation >= size)
    {
        return;
    }
    else if (functionCounter == 0)
    {
        cout << nums[CurLocation] << ' ';
        maxOrMin = 0;
        int tempCurLoc = CurLocation;
        CurLocation += max(0, nums[CurLocation]);
        preLocation = tempCurLoc;
        functionCounter++;
        solve(nums, maxOrMin, CurLocation, preLocation, size);
    }
    else if (maxOrMin == 1)
    {
        cout << nums[CurLocation] << ' ';
        maxOrMin = 0;
        int tempCurLoc = CurLocation;
        CurLocation += max(nums[preLocation], nums[CurLocation]);
        preLocation = tempCurLoc;
        solve(nums, maxOrMin, CurLocation, preLocation, size);
    }
    else
    {
        cout << nums[CurLocation] << ' ';
        maxOrMin = 1;
        int tempCurLoc = CurLocation;
        CurLocation += min(nums[preLocation], nums[CurLocation]);
        preLocation = tempCurLoc;
        solve(nums, maxOrMin, CurLocation, preLocation, size);
    }
}

int main()
{
    int size;
    cin >> size;
    int nums[size];
    for (int i = 0; i < size; i++)
    {
        cin >> nums[i];
    }
    int max = 1;
    int curLocation = 0;
    int preLocation = 0;
    solve(nums, max, curLocation, preLocation, size);
    return 0;
}