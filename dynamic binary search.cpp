#include <bits/stdc++.h>
using namespace std;

vector<int> dbs[64];
int last = 0;
pair<int, int> found; //i, index
int del[64] = {0};

void insertNum(int a)
{
    int i = 0;
    vector<int> temp;
    temp.push_back(a);
    while (!dbs[i].empty()) {
        vector<int> merged(dbs[i].size() + temp.size());
        merge(temp.begin(), temp.end(), dbs[i].begin(), dbs[i].end(), merged.begin());
        //cout << "test";
        temp = move(merged);
        //cout << i << endl;
        dbs[i].clear();
        i++;
    }
    dbs[i] = move(temp);
    if (i > last) last = i;

    /*
    for (int j: dbs[0]) {
        cout << "0 " << j << endl;
    }
    */
    //cout << "t\n";
}

bool searchNum(int a)
{
    int i = 0;
    while (i <= last) {
        //cout << i << " 2 \n";
        int left = 0;
        int right = dbs[i].size() - 1; // array 長度 -1
        while (left <= right) {
            int mid = (left + right) / 2; // 用 int 的性質做無條件捨去
            if (dbs[i].at(mid) > a) {
                right = mid - 1;
            }
            else if (dbs[i].at(mid) < a) {
                left = mid + 1;
            }
            else {
                found.first = i;
                found.second = mid;
                return 1; // 剛好找到 a
            }
        }
        //cout << i << " 1 \n";
        i++;
    }
    return 0;
}

void deleteNum(int a)
{
    int i = found.first;
    int index = found.second;
    int none = -0xfffffff;
    dbs[i].at(index) = none;
    del[i]++;
    if (del[i] >= pow(2, i) / 2) {
        del[i] = 0;
        vector<int> temp(pow(2, i-1)); //暫存去掉none的數
        vector<int>::iterator it = copy_if(
            begin(dbs[i]), end(dbs[i]), begin(temp), [none](const int t) { return t != none; });
        temp.erase(it, temp.end());
        dbs[i].clear();

        /*
        for (int j: temp) {
            cout << " " << j << endl;
        }
        */
        if (dbs[i-1].empty()) {
            dbs[i-1] = move(temp);
        }
        else {
            merge(temp.begin(), temp.end(), dbs[i-1].begin(), dbs[i-1].end(), back_inserter(dbs[i]));
            dbs[i-1].clear();
        }
    }
    /*
    for (int j: dbs[i-1]) {
        cout << "i-1 " << j << endl;
    }
    for (int j: dbs[i]) {
        cout << "i " << j << endl;
    }
    */
}

int main()
{

    clock_t start, stop;

    int n, m;
    int num;
    char c;

    cin >> n;
    while (n--) {
        cin >> num;
        insertNum(num);
    }

    cin >> m;
    while (m--) {
        cin >> c >> num;
        if (c == 'i') {
            start = clock(); //開始時間
            if (searchNum(num)) cout << "Insert Failed\n";
            else {
                insertNum(num);
                cout << "Insert Success\n";
            }
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
        else if (c == 's') {
            start = clock(); //開始時間
            if (searchNum(num)) cout << "Found\n";
            else cout << "Not Found\n";
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
        else if (c == 'd') {
            start = clock(); //開始時間
            if (searchNum(num)) {
                deleteNum(num);
                cout << "Delete Success\n";
            }
            else cout << "Delete Failed\n";
            stop = clock(); //結束時間
            cout << double(stop - start) / CLOCKS_PER_SEC << " s" << endl;
        }
    }
    return 0;
}
