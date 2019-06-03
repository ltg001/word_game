#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    int ans = 1 + rand() % 999;
    int guess = -1;

    while (guess != ans)
    {
        cin >> guess;
        //cout << guess << endl;
        if (guess == 1001)
        {
            cout << "the answer " << ans << endl;
            return 0;
        }
        if (guess > 1000 || guess <= 0)
        {
            cout << "invalid input" << endl;
            continue;
        }
        if (guess > ans)
            cout << "it is larger than the answer" << endl;
        else
            cout << "it is smaller than the answer" << endl;
    }
    cout << "you got the answer" << ans << endl;
    return 0;
}
