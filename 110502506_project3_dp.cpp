#include <bits/stdc++.h>
using namespace std;

int candy[205];
int n, sum;
bool dp[20005][20005];

int find_min(int a, int b, int c)
{
    return max(max(a, b), c) - min(min(a, b), c);
}

int solve()
{
    int min_diff = 1000000;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = sum; j >= 0; j--) {
            for (int k = sum; k >= 0; k--) {
                if (dp[j][k]) {
                    dp[j][k + candy[i]] = 1;
                    dp[j + candy[i]][k] = 1;
                }
            }
        }
    }

    for (int i = 0; i <= sum; i++) {
        for (int j = 0; j <= sum; j++) {
            if (dp[i][j])
                min_diff = min(min_diff, find_min(i, j, sum - i - j));
        }
    }

    return min_diff;
}

int main()
{
    cin.tie(0);
    clock_t start, stop;

    int t;
    cin >> t;
    for (int cas = 1; cas <= t; cas++) {
        //memset(dp, 0, sizeof(dp));
        sum = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> candy[i];
            sum += candy[i];
        }
        start = clock(); //開始時間
        for(int i = 0; i <= sum; i++) {
            dp[i][i] = 0;
        }
        cout << "Case " << cas << ": " << solve() << "\n";
        stop = clock(); //結束時間
        //cout << "\n運算時間： " << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
    }

    return 0;
}

