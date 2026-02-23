//2131 - 3121
#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 4181: Convex Hull
//난이도: 플레4

struct Point{
	ll x, y;
};

const ll mx = 100001;
ll N;
ll i, j, k;
ll sz;
char c;
vector<Point> V;
Point a, b;
stack<Point> S, hull;

ll ccw(Point a, Point b, Point c) {
	return (b.x-a.x)*(c.y-a.y)-((c.x-a.x)*(b.y-a.y));
}

ll dist(Point a, Point b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

bool sorter(Point a, Point b) {
	ll c = ccw(V[0],a,b);
	if (c == 0) {
		if (a.x == b.x) return a.y > b.y;
		else {
			if (a.y == b.y) return a.x < b.x;
			else return a.y > b.y; 
		}
	}
	return c>0;
}

bool ySort(Point a, Point b) {
	return (a.x==b.x) ? a.y<b.y : a.x<b.x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> a.x >> a.y >> c;
    	if(c=='Y') V.push_back({a.x,a.y});
    }
    sz = V.size();
    sort(V.begin(),V.end(),ySort);
    sort(V.begin()+1,V.end(),sorter);
    S.push(V[0]); S.push(V[1]);
    sz = V.size();
    for(i=2;i<sz;i++) {
    	while(S.size()>=2) {
    		b = S.top(); S.pop();
    		a = S.top();
    		if(ccw(V[i],a,b)>=0) {
    			S.push(b);
    			break;
    		}
    	}
    	S.push(V[i]);
    }
    while(S.size()) {
    	hull.push(S.top());
    	S.pop();
    }
    cout << hull.size() << '\n';
    while(hull.size()) {
    	cout << hull.top().x << ' ' << hull.top().y << '\n';
    	hull.pop();
    }
    return 0;
}
