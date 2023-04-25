#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    double x;
    double y;
    double z;
}point;

bool cmp(point a, point b) //���ǱƦC
{
    if (a.x > b.x) return true;
    else if (a.x == b.x && a.y > b.y) return true;
    else if (a.x == b.x && a.y == b.y && a.z > b.z) return true;
    return false;
}

point all[10000000];

int main()
{
    int n;
    cin >> n;

    vector<point> maximal;

    for (int i = 0; i < n; i++) {
        cin >> all[i].x >> all[i].y >> all[i].z;
    }

    //�p��ɶ�
    double START,END;
	START = clock();

    for (int i = 0; i < n; i++) {
        bool maxi = 1;
        for (int j = 0; j < n; j++) {
            if (all[j].x >= all[i].x && all[j].y >= all[i].y && all[j].z >= all[i].z && j != i) {
                maxi = 0;
                //break; //�p�G���O maximal �N�����~���F
            }
        }
        if (maxi) maximal.push_back(all[i]);
    }

    sort(maximal.begin(), maximal.end(), cmp);


/*    for (int i = 0; i < n; i++) {
        cout << all[i].x << " " << all[i].y << " " << all[i].z << "\n";
    }
*/
    //cout << "\n";


    for (int i = 0; i < maximal.size(); i++) {
        cout << maximal[i].x << " " << maximal[i].y << " " << maximal[i].z << "\n";
    }

    END = clock();
    cout << endl << "�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    return 0;
}
