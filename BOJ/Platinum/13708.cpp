#include <bits/stdc++.h>
#define ll long long int
#define lDoub long double
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13708: 모든 점을 포함하는 원
//난이도: 플레1

struct Point{
	lDoub x, y;
};

const ll mx = 1000001;
ll N;
ll i, j, k;
ll x, y;
Point center = {0L,0L};
lDoub maxDist, weight=0.1L, lr=0.9999;
ll pointIdx;
vector<Point> V;
lDoub radius;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(2);
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
    	cin >> x >> y;
    	V[i].x = x, V[i].y=y;
    	center.x+=V[i].x, center.y+=V[i].y;
    }
    center.x/=(lDoub)N; center.y/=(lDoub)N;
    for(i=0;i<mx;i++) {
    	maxDist=0L;
    	for(j=0;j<N;j++) {
    		lDoub dist = sqrt((center.x-V[j].x)*(center.x-V[j].x)+(center.y-V[j].y)*(center.y-V[j].y));
    		if(dist>maxDist) {
    			maxDist = dist;
    			pointIdx = j;
    		}
    	}
    	center.x += weight*(V[pointIdx].x-center.x);
    	center.y += weight*(V[pointIdx].y-center.y);
    	weight*=lr;
    }
    cout << round(2.0L*maxDist*100.0L)/100.0L << '\n';
    return 0;
}