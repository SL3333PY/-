#include <bits/stdc++.h>
using namespace std;

int candy[205];
int n, sum;
bitset<20005> dp[20005];

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
            //if (j == 3) cout << dp[3] << endl;
            dp[j + candy[i]] |= dp[j];
            dp[j] |= dp[j] << candy[i];
        }
    }

    for (int i = 0; i <= sum; i++) {
        for (int j = 0; j <= sum; j++) {
            if (dp[i][j])
                min_diff = min(min_diff, find_min(i, j, sum - i - j));
                //cout << i << " " << j << " " << min_diff << endl;
        }
    }

    return min_diff;
}

int main()
{
    //ios_base::sync_with_stdio(false);
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
            dp[i].reset();
        }
        cout << "Case " << cas << ": " << solve() << "\n";
        stop = clock(); //結束時間
        //cout << "\n運算時間： " << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
    }

    return 0;
}


