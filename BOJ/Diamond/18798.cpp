#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 18798: OR과 쿼리
//난이도: 다이아5

struct C{
	ll allOne;
	ll isK;
};

const ll mx = 250001;
ll N, K, M;
ll i, j, k;
ll order, l, r, x;
ll A[mx];
C segTree[mx<<2];
C nullLeaf = {-1,0};

C merging(C lower, C upper) {
	if(lower.allOne<0) return upper;
	if(upper.allOne<0) return lower;
	C ans = {
		(lower.allOne&upper.allOne),
		lower.isK + upper.isK
	};
	return ans;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {A[start],(A[start]==K ? 1 : 0)};
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merging(lower,upper);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		if((segTree[node].allOne&val)==val) return;
		segTree[node].allOne |= val;
		if(start==end) {
			if(segTree[node].allOne==K) segTree[node].isK = 1;
			else segTree[node].isK = 0;
			return;
		}
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	segTree[node] = merging(segTree[node<<1],segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    cin >> M;
    for(i=0;i<M;i++) {
    	cin >> order;
    	if(order==1) {
    		cin >> l >> r >> x;
    		l --; r --;
    		update(0,N-1,1,l,r,x);
    	}
    	else {
    		cin >> l >> r;
    		l --; r --;
    		cout << search(0,N-1,1,l,r).isK << '\n';
    	}
    }
    return 0;
}
