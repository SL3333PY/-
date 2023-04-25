#include <bits/stdc++.h>
using namespace std;

int n, sum;
bitset<20005> dp[205];
vector<int> v; //possible difference
int candy[205], pre[205];   //pre = prefix sum

map<int,bool> tmp[205];

bool solve(int x,int Max,int Min){
	if (x == -1)
        return 1;
	else if (!dp[x + 1][Max] || !dp[x + 1][Min])    // the set is inpossible
		return 0;
	else {
        auto it = tmp[x].find(Max * 50000 + Min);
        if (it != tmp[x].end()) {
            return it->second;
        }
        else{
            if (Max >= candy[x] && solve(x - 1, max(Max - candy[x], pre[x] - Max - Min), min(Max - candy[x], Min))) {
                tmp[x][Max * 50000 + Min] = 1;
                return 1;
            }
            if (Min >= candy[x] && solve(x - 1, Max, Min - candy[x])) {
                tmp[x][Max * 50000 + Min] = 1;
                return 1;
            }
            if (pre[x] - Max - Min >= candy[x] && solve(x - 1, Max, min(Min, pre[x] - Max - Min - candy[x]))) {
                tmp[x][Max * 50000 + Min] = 1;
                return 1;
            }
            tmp[x][Max * 50000 + Min] = 0;
            return 0;
        }
	}
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
        for(int i = 0; i <= n; i++) {
            dp[i].reset();
            pre[i] = 0;
            tmp[i].clear();
        }
        v.clear();
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            cin >> candy[i];
            sum += candy[i];
            pre[i] = sum;
            dp[i + 1] = ((dp[i] << candy[i]) | dp[i]);
        }
        start = clock(); //開始時間
        for (int i = 0; i <= sum; i++)
            if(dp[n][i]) v.push_back(i);

        int min_diff = sum; //sum = max difference

        for (int i = 0; i <= sum;i++) {   //difference from 0 to max
			for (int j = 0; j < v.size(); j++) {   //every set
				int k = sum - 2 * v[j] - i; //the rest one = sum - 2*min - diff
				if (k < 0) break;
				int a = max(v[j] + i, k);
				int b = min(v[j], k);
				if (solve(n - 1, a, b)){
					min_diff = min(min_diff, a - b);
					if (min_diff == i) break;
				}
			}
			if (min_diff == i) break;
		}

        cout << "Case " << cas << ": " << min_diff << "\n";
        stop = clock(); //結束時間
        //cout << "\n運算時間： " << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
    }

    return 0;
}


