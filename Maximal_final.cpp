/*
Maximal Points Problem (3D)

�b�@�ӪŶ����� p �M q ����I�A�� p.x >= q.x�Bp.y >= q.y �H�� p.z >= q.z ���߮ɺ٬� p dominates q�C
��@�Ӧb�I���X S ���� p �I���Q�����L�ݩ� S ���I dominates �ɡA
�� p �I�N�Q�٧@���@�� maximal point�C

�ؼСG�N�Ҧ��ݩ� S �� maximal points ��X�ӡC

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


bool cmp(point a, point b) //����
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
    cout << endl << "�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    return 0;

}
