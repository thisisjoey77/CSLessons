#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 10167: 금광
//난이도: 다이아5

struct C{
    ll x, y, w;
};

struct D{
	ll totSum, leftFixMax, rightFixMax, maxVal;
	bool isNull;
};

const ll mx = 3001;
ll N;
ll i, j, k;
ll lastIdx = 0, ans = LLONG_MIN, idx, sz;
vector<ll> coords;
vector<C> V;
D segTree[mx<<2];
D nullLeaf = {0,0,0,LLONG_MIN,true};

bool sorter(C c1, C c2) {
	return c1.x < c2.x;
}

D merging(D lower, D upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	D ans = {
		lower.totSum + upper.totSum,
		lower.leftFixMax, upper.rightFixMax,
		max(lower.maxVal, upper.maxVal),
		false
	};
	ans.maxVal = max(ans.maxVal, lower.rightFixMax + upper.leftFixMax);
	ans.leftFixMax = max(ans.leftFixMax, lower.totSum+upper.leftFixMax);
	ans.rightFixMax = max(ans.rightFixMax, upper.totSum+lower.rightFixMax);
	return ans;
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		ll newVal = segTree[node].totSum + val;
		segTree[node] = {newVal, newVal, newVal, newVal, false};
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val);
	else update(mid+1,end,node<<1|1,idx,val);
	segTree[node] = merging(segTree[node<<1],segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) segTree[i] = nullLeaf;
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
    	cin >> V[i].x >> V[i].y >> V[i].w;
    	coords.push_back(V[i].y);
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = coords.size();
    sort(V.begin(),V.end(),sorter);
    for(i=0;i<N;i++) {
    	idx = lower_bound(coords.begin(),coords.end(),V[i].y)-coords.begin();
    	update(0,sz-1,1,idx,V[i].w);
    	if(i+1==N || (i+1<N && V[i+1].x!=V[i].x)) {
    		ans = max(ans,segTree[1].maxVal);
    	    for(j=0;j<=i;j++) {
    	        idx = lower_bound(coords.begin(),coords.end(),V[j].y)-coords.begin();
    	        update(0,sz-1,1,idx,-1*V[j].w);
    	        if(j+1==N || (j+1<N && V[j+1].x != V[j].x)) {
    	            ans = max(ans,segTree[1].maxVal);
    	        }
    	    }
    	    for(k=0;k<j;k++) {
    	        idx = lower_bound(coords.begin(),coords.end(),V[k].y)-coords.begin();
    	        update(0,sz-1,1,idx,V[k].w);
    	    }
    	}
    }
    cout << ans << '\n';
    return 0;
}
