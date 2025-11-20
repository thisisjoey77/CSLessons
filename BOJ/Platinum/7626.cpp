#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 7626: 직사각형
//난이도: 플레1

struct C{
	ll x, yFrom, yTo, adding;
};

struct D{
	ll covered, area;
};

const ll mx = 400005;
ll N;
ll i, j, k;
ll sz;
ll xFrom, yFrom, xTo, yTo;
ll fromIdx, toIdx;
ll area = 0;
vector<C> V;
vector<ll> yCoord;
vector<pii> intervals;
D segTree[mx<<2];

bool sorter(C c1, C c2) {
	return c1.x < c2.x;
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll adding) {
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		segTree[node].covered += adding;
		if(segTree[node].covered) {
			segTree[node].area = intervals[end].second-intervals[start].first;
		}
		else if(start==end) segTree[node].area = 0;
		else segTree[node].area = segTree[node<<1].area + segTree[node<<1|1].area;
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,adding);
	update(mid+1,end,node<<1|1,lBound,rBound,adding);
	if(segTree[node].covered) segTree[node].area = intervals[end].second - intervals[start].first;
	else segTree[node].area = segTree[node<<1].area + segTree[node<<1|1].area;
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) segTree[i] = {0,0};
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> xFrom >> xTo >> yFrom >> yTo;
    	V.push_back({xFrom,yFrom,yTo,1});
    	V.push_back({xTo,yFrom,yTo,-1});
    	yCoord.push_back(yFrom);
    	yCoord.push_back(yTo);
    }
    sort(yCoord.begin(),yCoord.end());
    yCoord.erase(unique(yCoord.begin(),yCoord.end()),yCoord.end());
    sz = yCoord.size();
    for(i=0;i+1<sz;i++) {
    	intervals.push_back(make_pair(yCoord[i],yCoord[i+1]));
    }
    sort(V.begin(),V.end(),sorter);
    sz = intervals.size();
    for(i=0;i<(N<<1);i++) {
    	if(i && (V[i].x != V[i-1].x)) {
    		area += (V[i].x-V[i-1].x) * segTree[1].area;
    	}
    	fromIdx = lower_bound(yCoord.begin(),yCoord.end(),V[i].yFrom)-yCoord.begin();
    	toIdx = lower_bound(yCoord.begin(),yCoord.end(),V[i].yTo)-yCoord.begin();
    	update(0, sz-1, 1, fromIdx, toIdx-1, V[i].adding);
    }
    cout << area << '\n';
    return 0;
}
