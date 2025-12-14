#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17474: 수열과 쿼리 26
//난이도: 다이아1

struct C{
	ll mx, mx2, mxCnt, totSum;
	bool isNull;
};

const ll mx = 1000001;
ll N, Q;
ll i, j, k;
pii lazy[mx<<2];
C segTree[mx<<2];
C nullLeaf = {0,0,0,0,true}, cur;
ll A[mx];
ll order, l, r, x;

C merging(C lower, C upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	C ans;
	ans.totSum = lower.totSum + upper.totSum;
	ans.isNull = false;
	if(lower.mx!=upper.mx) {
		if(lower.mx>upper.mx) {
			ans.mx = lower.mx, ans.mxCnt = lower.mxCnt;
			ans.mx2 = max(upper.mx,lower.mx2);
		}
		else {
			ans.mx = upper.mx, ans.mxCnt = upper.mxCnt;
			ans.mx2 = max(lower.mx,upper.mx2);
		}
	}
	else {
		ans.mx = lower.mx;
		ans.mx2 = max(lower.mx2,upper.mx2);
		ans.mxCnt = lower.mxCnt + upper.mxCnt;
	}
	return ans;
}

void lazyUpdate(ll start, ll end, ll node) {
	if(lazy[node].first) {
		if(segTree[node].mx>lazy[node].second) {
			segTree[node].totSum -= segTree[node].mxCnt*(segTree[node].mx-lazy[node].second);
			segTree[node].mx = lazy[node].second;
		}
		if(start!=end) {
			lazy[node<<1] = {1,min(lazy[node<<1].second,lazy[node].second)};
			lazy[node<<1|1] = {1,min(lazy[node<<1|1].second,lazy[node].second)};
		}
		lazy[node] = {0,LLONG_MAX};
	}
	return;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {A[start],LLONG_MIN,1,A[start],false};
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merging(lower, upper);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	lazyUpdate(start,end,node);
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound || segTree[node].mx<=val) return;
	if(lBound<=start && end<=rBound && segTree[node].mx2<val) {
		lazy[node] = {1,val};
		lazyUpdate(start,end,node);
		return;
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
    for(i=0;i<(mx<<2);i++) lazy[i] = {0,LLONG_MAX};
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    cin >> Q;
    for(i=0;i<Q;i++) {
    	cin >> order;
    	if(order==1) {
    		cin >> l >> r >> x;
    		l --; r --;
    		update(0,N-1,1,l,r,x);
    	}
    	else {
    		cin >> l >> r;
    		l --; r --;
    		cur = search(0,N-1,1,l,r);
    		cout << ((order==2) ? cur.mx : cur.totSum) << '\n';
    	}
    }
    return 0;
}