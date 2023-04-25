#include <bits/stdc++.h>
using namespace std;

set<int> dbs;

int main()
{
    clock_t start, stop;

    int n, m;
    int num;
    char c;

    cin >> n;
    while (n--) {
        cin >> num;
        dbs.insert(num);
    }

    cin >> m;
    while (m--) {
        cin >> c >> num;
        if (c == 'i') {
            start = clock(); //開始時間
            if (dbs.count(num)) cout << "Insert Failed\n";
            else {
                dbs.insert(num);
                cout << "Insert Success\n";
            }
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
        else if (c == 's') {
            start = clock(); //開始時間
            if (dbs.count(num)) cout << "Found\n";
            else cout << "Not Found\n";
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
        else if (c == 'd') {
            start = clock(); //開始時間
            if (dbs.count(num)) {
                dbs.erase(num);
                cout << "Delete Success\n";
            }
            else cout << "Delete Failed\n";
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
    }
    return 0;
}
