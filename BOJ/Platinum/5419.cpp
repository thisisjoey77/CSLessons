#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 5419: 북서풍
//난이도: 플레3

struct C{
	ll x, y, atLoc;
};

const ll mx = 75001;
ll ans = 0;
ll N, T;
ll i, j, k;
ll maxIdx;
ll x, y;
vector<C> V;
vector<ll> yRec;
ll segTree[mx<<2] = {0,};

bool sorter(C c1, C c2) {
	if(c1.y!=c2.y) return c1.y < c2.y;
	return c1.x > c2.x;
}

bool sorterX(C c1, C c2) {
	if(c1.x != c2.x) return c1.x > c2.x;
	return c1.y < c2.y;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	return search(start,mid,node<<1,lBound,rBound) +
	search(mid+1,end,node<<1|1,lBound,rBound);
}

void update(ll start, ll end, ll node, ll idx) {
	if(idx<start || end<idx) return;
	segTree[node] ++;
	if(start==end) return;
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx);
	else update(mid+1,end,node<<1|1,idx);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    for(k=0;k<T;k++) {
    	//reset mem
    	ans = 0;
    	for(i=0;i<(mx<<2);i++) segTree[i] = 0;
    	V = {}; yRec = {};

    	//input
    	cin >> N;
    	for(i=0;i<N;i++) {
    		cin >> x >> y;
    		V.push_back({x,y,-1});
    	}

    	//preprocess
    	sort(V.begin(),V.end(),sorter);
    	for(i=0;i<N;i++) {
    		V[i].atLoc = i;
    		yRec.push_back(V[i].y);
    	}
    	sort(V.begin(),V.end(),sorterX);

    	for(i=0;i<N;i++) {
    		maxIdx = upper_bound(yRec.begin(),yRec.end(),V[i].y)-yRec.begin()-1;
    		ans += search(0,N-1,1,0,maxIdx);
    		update(0,N-1,1,V[i].atLoc);
    	}
    	cout << ans << '\n';
    }
    return 0;
}
