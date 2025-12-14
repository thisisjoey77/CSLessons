#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16670: King Kog's Reception
//난이도: 다이아5

struct C{
	ll start, time, totSum;
	bool isNull;
};

struct order{
	char order;
	ll t, d, i;
};

const ll mx = 300001;
ll N, Q;
ll i, j, k;
ll idx, sz, ansTime;
vector<ll> coords;
vector<order> V;
order cur;
C segTree[mx<<2];
C defLeaf = {0,0,0,false}, nullLeaf = {0,0,0,true}, result;

C merging(const C &lower, const C &upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	C ans = {
		upper.start, upper.time, lower.totSum+upper.totSum,false
	};
	if(lower.time+upper.totSum-upper.time>upper.start-lower.start) {
		ans.start = lower.start;
		ans.time = upper.totSum+lower.time;
	}
	return ans;
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		segTree[node] = {coords[idx],segTree[node].time+val,segTree[node].totSum+val};
		segTree[node].isNull = !segTree[node].totSum;
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val);
	else update(mid+1,end,node<<1|1,idx,val);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) segTree[i] = nullLeaf;
    cin >> Q;
    V.resize(Q);
    for(i=0;i<Q;i++) {
    	cin >> V[i].order;
    	if(V[i].order=='+') {
    		cin >> V[i].t >> V[i].d;
    		coords.push_back(V[i].t);
    	}
    	else if(V[i].order=='-') {
    		cin >> V[i].i;
    		V[i].i --;
    	}
    	else {
    		cin >> V[i].t;
    	}
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = coords.size();
    for(i=0;i<Q;i++) {
    	cur = V[i];
    	if(cur.order=='+') {
    		idx = lower_bound(coords.begin(),coords.end(),V[i].t)-coords.begin();
    		update(0,sz-1,1,idx,V[i].d);
    	}
    	else if(cur.order=='-') {
    		idx = lower_bound(coords.begin(),coords.end(),V[V[i].i].t)-coords.begin();
    		update(0,sz-1,1,idx,-1*V[V[i].i].d);
    	}
    	else {
    		idx = upper_bound(coords.begin(),coords.end(),V[i].t)-coords.begin()-1;
    		if(idx==-1) {
    			cout << "0\n";
    			continue;
    		}
    		result = search(0,sz-1,1,0,idx);
    		ansTime = result.start+result.time-V[i].t;
    		cout << max(0LL,ansTime) << '\n';
    	}
    }
    return 0;
}