#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 10254: 고속도로
//난이도: 플레2

struct Point{
    ll x, y;
};

ll N, T;
ll i, j, k;
ll sz;
vector<Point> V, hull;
Point a, b;
ll pA, pB, pC, pD;
ll ans, paMove;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y)-((c.x-a.x)*(b.y-a.y));
}

ll ccw2(Point a, Point b, Point c, Point d) {
    d.y -= c.y-b.y;
    d.x -= c.x-b.x;
    return ccw(a, b, d);
}

ll dist(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

bool ySort(Point a, Point b) {
    return (a.x==b.x) ? a.y<b.y : a.x<b.x;
}

bool sorter(Point a, Point b) {
    ll c = ccw(V[0],a,b);
    if(!c) {
        return dist(V[0],a) < dist(V[0],b);
    }
    return c>0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T --) {
        V.resize(0); hull.resize(0);
        cin >> N;
        V.resize(N);
        for(i=0;i<N;i++) {
            cin >> V[i].x >> V[i].y;
        }
        sort(V.begin(),V.end(),ySort);
        sort(V.begin()+1,V.end(),sorter);
        hull.push_back(V[0]); hull.push_back(V[1]);
        for(i=2;i<N;i++) {
            while(hull.size()>=2) {
                b = hull.back(); hull.pop_back();
                a = hull.back();
                if(ccw(V[i],a,b)>0) {
                    hull.push_back(b);
                    break;
                }
            }
            hull.push_back(V[i]);
        }
        sz = hull.size();
        pA = 0%sz, pB = 1%sz, pC = 1%sz, pD = 2%sz;
        ans = 0, paMove = 0;
        while(1) {
            if(dist(hull[pA],hull[pC])>ans) {
                ans = dist(hull[pA],hull[pC]);
                a = hull[pA], b = hull[pC];
            }
            if(ccw2(hull[pA],hull[pB],hull[pC],hull[pD])>0) {
                pC ++; pD ++;
                pC %= sz; pD %= sz;
            }
            else {
                pA ++; pB ++;
                pA %= sz; pB %= sz;
                if(++paMove>=sz) break;
            }
        }
        cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << '\n';
    }
    return 0;
}
