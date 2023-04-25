#include <bits/stdc++.h>
using namespace std;

int n, m;
int group[55];

int getlead(int a)
{
    if (group[a] != a) {
        group[a] = getlead(group[a]);
    }
    return group[a];
}

struct edge
{
    int node1;
    int node2;
    int weight;
};

vector<edge> all, trying, mincut;
int minc, tryminc;

int main()
{
    clock_t start, stop;
    while (cin >> n >> m && !(!n && !m)) {
        // initialization
        all.clear();
        minc = 0x7fffffff;
        int try_time = 10;
        //
        while (m--) {
            edge tmp;
            cin >> tmp.node1 >> tmp.node2 >> tmp.weight;
            if (tmp.node1 > tmp.node2) swap(tmp.node1, tmp.node2);
            all.push_back(tmp);
        }
        start = clock(); //開始時間
        srand (unsigned (time(0)));


        // 要重複的部分
        while (try_time--) {
            random_shuffle(all.begin(), all.end());
            tryminc = 0;
            trying.clear();
            for (int i = 1; i <= n; i++) {
                group[i] = i;
            }

            for (int i = 0; i < all.size(); i++) {
                int a = getlead(all[i].node1);
                int b = getlead(all[i].node2);
                if (!(a == 1 && b == 2) && !(a == 2 && b == 1)) {
                    if (a < b) group[b] = a;
                    else if (b < a) group[a] = b;
                }
                else {
                    trying.push_back(all[i]);
                    tryminc += all[i].weight;
                }
            }
            //cout << tryminc << endl;
            /*
            for (int i = 0; i < trying.size(); i++)
                printf("%d ", trying[i].weight);
            cout << "\n";
            */
            if (tryminc < minc) {
                minc = tryminc;
                mincut = trying;
            }
        }

        //

        for (int i = 0; i < mincut.size(); i++)
            printf("%d %d\n", mincut[i].node1, mincut[i].node2);
        cout << "\n";
        //cout << minc << endl;
        stop = clock(); //結束時間
        cout << "\n運算時間： " << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
    }

    return 0;
}

