#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16357: Circuits
//난이도: 플레1

struct C{
	ll yFrom, yTo, firstSpike;
};

const ll mx = 200001;
ll N;
ll i, j, k;
ll ux, uy, vx, vy;
ll sz;
ll ans=0;
vector<ll> coords;
vector<C> V;
ll segTree[mx<<2] = {0,}, lazy[mx<<2] = {0,};

bool sorter(C c1, C c2) {
	return c1.yFrom < c2.yFrom;
}

void lazyUpdate(ll start, ll end, ll node) {
	if(!lazy[node]) return;
	segTree[node] += lazy[node];
	if(start!=end) {
		lazy[node<<1] += lazy[node];
		lazy[node<<1|1] += lazy[node];
	}
	lazy[node] = 0;
	return;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	ll lower = search(start,mid,node<<1,lBound,rBound);
	ll upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return max(lower, upper);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		lazy[node] += val;
		lazyUpdate(start,end,node);
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	segTree[node] = max(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> ux >> uy >> vx >> vy;
    	V.push_back({vy,uy,0});
    	coords.push_back(uy);
    	coords.push_back(vy);
    }
    sort(V.begin(),V.end(),sorter);
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = coords.size();
    ll fromIdx, toIdx;
    for(i=0;i<N;i++) {
    	fromIdx = lower_bound(coords.begin(),coords.end(),V[i].yFrom)-coords.begin();
    	toIdx = lower_bound(coords.begin(),coords.end(),V[i].yTo)-coords.begin();
    	update(0,sz-1,1,fromIdx,toIdx,1);
        V[i].firstSpike = search(0,sz-1,1,fromIdx,fromIdx);
    }
    ll curVal;
    for(i=0;i<N;i++) {
    	curVal = V[i].firstSpike;
    	fromIdx = lower_bound(coords.begin(),coords.end(),V[i].yFrom)-coords.begin();
    	toIdx = lower_bound(coords.begin(),coords.end(),V[i].yTo)-coords.begin();
    	update(0,sz-1,1,fromIdx,toIdx,-1);
    	ans = max(ans,curVal+search(0,sz-1,1,fromIdx+1,sz-1));
    }
    cout << ans << '\n';
    return 0;
}
