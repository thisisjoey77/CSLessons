#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 10070: 벽
//난이도: 다이아5

struct C{
	ll lift, cap;
	bool isNull;
};

const ll mx = 2000001;
ll N, K;
ll i, j, k;
ll opI, leftI, rightI, heightI;
C segTree[mx<<2];
C nullLeaf = {0,LLONG_MAX, true};

C merging(C c1, C c2) {
	if(c1.isNull) return c2;
	if(c2.isNull) return c1;
	if(c2.lift==c2.cap) return c2;
	C ans = c1;
	ans.lift = max(ans.lift,c2.lift);
	if(ans.lift>ans.cap) ans.cap = ans.lift;
	ans.cap = min(ans.cap,c2.cap);
	if(ans.cap<ans.lift) ans.lift = ans.cap;
	return ans;
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, C val) {
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		if(!val.isNull) {
			if(val.lift==val.cap || segTree[node].isNull) segTree[node] = val;
			else segTree[node] = merging(segTree[node],val);
		}
		return;
	}
    if(!segTree[node].isNull) {
	    segTree[node<<1] = merging(segTree[node<<1],segTree[node]);
	    segTree[node<<1|1] = merging(segTree[node<<1|1],segTree[node]);
	    segTree[node] = nullLeaf;
    }
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	return;
}

C search(ll start, ll end, ll node, ll idx) {
	if(idx<start || end<idx) return nullLeaf;
	if(start==end) return segTree[node];
	ll mid = (start+end) >> 1;
    if(!segTree[node].isNull) {
	    segTree[node<<1] = merging(segTree[node<<1],segTree[node]);
	    segTree[node<<1|1] = merging(segTree[node<<1|1],segTree[node]);
	    segTree[node] = nullLeaf;
    }
	if(idx<=mid) return search(start,mid,node<<1,idx);
	return search(mid+1,end,node<<1|1,idx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) {
    	segTree[i] = nullLeaf;
    }
    cin >> N >> K;
    for(i=0;i<K;i++) {
    	cin >> opI >> leftI >> rightI >> heightI;
    	if(opI==1) update(0,N-1,1,leftI,rightI,{heightI,LLONG_MAX,false});
    	else update(0,N-1,1,leftI,rightI,{0,heightI,false});
    }
    for(i=0;i<N;i++) {
    	cout << search(0,N-1,1,i).lift << '\n';
    }
    return 0;
}
