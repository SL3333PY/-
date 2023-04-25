#include <bits/stdc++.h>
using namespace std;

int n, m;
int cost[55][55], flow[55][55], x[505], y[505];
int parent[55], a[55];  //the flow at each vertex

void max_flow(int s, int t)
{
    queue<int> q;
    memset(flow, 0, sizeof(flow));
    int mf = 0;
    while (1) {
        memset(a, 0, sizeof(a));
        a[s] = 0xfffffff;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 1; v <= n; v++) {
                if (!a[v] && flow[u][v] < cost[u][v]) {
                    parent[v] = u;
                    a[v] = min(a[u], cost[u][v] - flow[u][v]);
                    q.push(v);
                }
            }
        }
        if (a[t] == 0) break;
        for (int v = t; v != s; v = parent[v]) {
            flow[parent[v]][v] += a[t];
            flow[v][parent[v]] -= a[t];
        }
        mf += a[t];
    }
    //cout << mf << endl;
}


int main()
{
    clock_t start, stop;
    while (cin >> n >> m && !(!n && !m)) {
        memset(cost, 0, sizeof(cost));

        for (int i = 0; i < m; i++) {
            int w;
            cin >> x[i] >> y[i] >> w;
            cost[x[i]][y[i]] = cost[y[i]][x[i]] = w;
        }
        start = clock(); //開始時間
        max_flow(1, 2);

        for (int i = 0; i < m; i++) {
            if ((!a[x[i]] && a[y[i]]) || (a[x[i]] && !a[y[i]]))
                    cout << x[i] << " " << y[i] << "\n";
        }
        cout << "\n";
        stop = clock(); //結束時間
        cout << "\n運算時間： " << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
    }

    return 0;
}
