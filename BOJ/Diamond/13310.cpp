#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13310: 먼 별
//난이도: 다이아5

struct C{ll x, y, dy, dx;};
struct Point{ll x, y;};

ll N, T;
ll i, j, k;
vector<C> V;
Point origin, a, b;

ll ccw(Point a, Point b, Point c) {
	return (b.x-a.x)*(c.y-a.y)-((c.x-a.x)*(b.y-a.y));
}

ll ccw2(Point a, Point b, Point c, Point d) {
	d.x -= (c.x-b.x);
	d.y -= (c.y-b.y);
	return ccw(a,b,d);
}

ll dist(Point a, Point b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

bool ySort(Point p1, Point p2) {
	if(p1.x==p2.x) return p1.y < p2.y;
	return p1.x < p2.x;
}

bool sorter(Point p1, Point p2) {
	ll c = ccw(origin,p1,p2);
	if(!c) return dist(origin,p1) < dist(origin,p2);
	return c>0;
}

ll convex(ll day) {
	vector<Point> stars(N), hull;
	for(i=0;i<N;i++) {
		stars[i] = {V[i].x+V[i].dx*day, V[i].y+V[i].dy*day};
	}
	sort(stars.begin(),stars.end(),ySort);
	origin = stars[0];
	sort(stars.begin()+1,stars.end(),sorter);
	hull.push_back(stars[0]); hull.push_back(stars[1]);
	for(i=2;i<N;i++) {
		while(hull.size()>=2) {
			b = hull.back(); hull.pop_back();
			a = hull.back();
			if(ccw(stars[i],a,b)>0) {
				hull.push_back(b);
				break;
			}
		}
		hull.push_back(stars[i]);
	}
	ll sz = hull.size();
	ll pA=0, pB=1%sz, pC=1%sz, pD=2%sz, paMove=0, ans=0;
	while(1) {
		if(dist(hull[pA],hull[pC])>ans) {
			ans = dist(hull[pA],hull[pC]);
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
	return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> T;
    V.resize(N);
    for(i=0;i<N;i++) {
    	cin >> V[i].x >> V[i].y >> V[i].dx >> V[i].dy;
    }
    ll lo = 0, hi = T;
    while(hi-lo>=3) {
    	ll p = lo+(hi-lo)/3, q = hi-(hi-lo)/3;
    	if(convex(p)<=convex(q)) hi=q;
    	else lo=p;
    }
    ll ans = LLONG_MAX, day;
    for(j=lo;j<=hi;j++) {
    	ll tempAns = convex(j);
    	if(tempAns<ans) {
    		ans = tempAns;
    		day = j;
    	}
    }
    cout << day << '\n' << ans << '\n';
    return 0;
}