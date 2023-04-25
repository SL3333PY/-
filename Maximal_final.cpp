/*
Maximal Points Problem (3D)

在一個空間中有 p 和 q 兩個點，當 p.x >= q.x、p.y >= q.y 以及 p.z >= q.z 成立時稱為 p dominates q。
當一個在點集合 S 中的 p 點不被任何其他屬於 S 的點 dominates 時，
該 p 點就被稱作為一個 maximal point。

目標：將所有屬於 S 的 maximal points 找出來。

*/


#include <bits/stdc++.h>
using namespace std;

int n;


typedef struct
{
    double x;
    double y;
    double z;
}point;

vector<point> all;


bool cmp(point a, point b) //降序
{
    if (a.x > b.x) return true;
    else if (a.x == b.x && a.y > b.y) return true;
    else if (a.x == b.x && a.y == b.y && a.z > b.z) return true;
    return false;
}

bool cmp2d(point a, point b)
{
    if (a.y > b.y) return true;
    else if (a.y == b.y && a.z > b.z) return true;
    else if (a.y == b.y && a.z == b.z && a.x > b.x) return true;
    return false;
}

namespace std
{
template <>
    struct less<point>
    {
    public:
        bool operator() (const point &a, const point &b)
        {
            if (a.y > b.y) return true;
            else if (a.y == b.y && a.z > b.z) return true;
            else if (a.y == b.y && a.z == b.z && a.x > b.x) return true;
            return false;
        }
    };
}

map<point, bool> domin;
map<point, char> m;

void dc(int p, int q)
{
    if (p < q) {
        int mid = (p + q) / 2;


        for (int i = p; i <= mid; i++) {
            m[all[i]] = 'a';
        }
        for (int i = mid + 1; i <= q; i++) {
            m[all[i]] = 'b';
        }

/*
        for (const auto& s : m) {
            cout << "point: " << s.first.x << " " << s.first.y << " " << s.first.z << ", set: " << s.second << "\n";
        }
*/


        point ma;
        ma.z = -10000005;
        //cout << "\n"<<ma.z<<"\n";


        for (int i = p; i < q + 1; i++) {
            auto it = m.begin();
            //cout << "\n"<<it->first.z<<"\n";
            if (it->second == 'a' && it->first.z > ma.z) {
                ma = it->first;

                m.erase(it);
            }
            else if (it->second == 'b' && it->first.z <= ma.z) {
                point tem = it->first;
                domin[tem] = 1;
                //cout << tem.x << " " << tem.y << " " << tem.z << "\n";
                m.erase(it);
                //cout << "\n1\n";
            }
            else m.erase(it);
        }

        dc(p, mid);
        dc(mid+1, q);

        //cout << p << " " << q << "\n";
    }

}

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) {
        point temp;
        cin >> temp.x >> temp.y >> temp.z;
        all.push_back(temp);
        domin[temp] = 0;
    }

    double START,END;
	START = clock();

    sort(all.begin(), all.end(), cmp);


    dc(0, n - 1);


    //cout << "\n";
    for (int i = 0; i < n; i++) {
        if(!domin[all[i]]) cout << all[i].x << " " << all[i].y << " " << all[i].z << "\n";
    }

    //cout << ma.x << " " << ma.y << " " << ma.z << "\n";

    END = clock();
    cout << endl << "進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    return 0;

}
