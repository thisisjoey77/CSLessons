#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 34207: 상자 보관
//난이도: 플레2

struct C{
	ll s, c;
};

const ll mx = 400001;
ll N;
ll i, j, k;
ll sz;
ll segTree[mx<<2] = {0,}, lazy[mx<<2] = {0,};
ll from, to;
vector<ll> coords;
vector<C> V;

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

void update(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		lazy[node] ++;
		lazyUpdate(start,end,node);
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound);
	update(mid+1,end,node<<1|1,lBound,rBound);
	segTree[node] = max(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
    	cin >> V[i].s >> V[i].c;
    	coords.push_back(V[i].c);
    	coords.push_back(V[i].s);
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = coords.size();
    for(i=0;i<N;i++) {
    	from = lower_bound(coords.begin(),coords.end(),V[i].c)-coords.begin();
    	to = lower_bound(coords.begin(),coords.end(),V[i].s)-coords.begin()-1;
    	update(0,sz-1,1,from,to);
    	cout << segTree[1] << '\n';
    }
    return 0;
}