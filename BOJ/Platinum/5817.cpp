#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 5817: SNJEGULJICA
//난이도: 플레3

struct C{
	ll min, max;
};

const ll mx = 200001;
ll N, M;
ll i, j, k;
ll A[mx], locs[mx];
C locSeg[mx<<2], valSeg[mx<<2], curLoc, curVal;
ll order, t1, t2, val1, val2;
ll from, to;

C init(ll start, ll end, ll node, bool findLoc) {
	if(start==end) {
		if(findLoc) return locSeg[node] = {locs[start],locs[end]};
		return valSeg[node] = {A[start],A[end]};
	}
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1,findLoc), upper = init(mid+1,end,node<<1|1,findLoc);
	if(findLoc) return locSeg[node] = {min(lower.min,upper.min),max(lower.max,upper.max)};
	return valSeg[node] = {min(lower.min,upper.min),max(lower.max,upper.max)};
}

C search(ll start, ll end, ll node, ll lBound, ll rBound, bool findLoc) {
	if(end<lBound || rBound<start) return {LLONG_MAX,LLONG_MIN};
	if(lBound<=start && end<=rBound) return (findLoc) ? locSeg[node] : valSeg[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound,findLoc), upper = search(mid+1,end,node<<1|1,lBound,rBound,findLoc);
	return {min(lower.min,upper.min),max(lower.max,upper.max)};
}

void update(ll start, ll end, ll node, ll idx, ll val, bool findLoc) {
	if(idx<start || end<idx) return;
	if(start==end) {
		if(findLoc) locSeg[node] = {val,val};
		else valSeg[node] = {val,val};
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val,findLoc);
	else update(mid+1,end,node<<1|1,idx,val,findLoc);
	if(findLoc) {
		C lower = locSeg[node<<1], upper = locSeg[node<<1|1];
		locSeg[node] = {min(lower.min,upper.min),max(lower.max,upper.max)};
	}
	else {
		C lower = valSeg[node<<1], upper = valSeg[node<<1|1];
		valSeg[node] = {min(lower.min,upper.min),max(lower.max,upper.max)};
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    	locs[A[i]] = i;
    }
    init(0,N-1,1,true); init(0,N-1,1,false);
    for(i=0;i<M;i++) {
    	cin >> order >> t1 >> t2;
    	if(order==1) {
    		t1 --; t2 --;
    		val1 = A[t1], val2 = A[t2];
    		update(0,N-1,1,t1,val2,false); update(0,N-1,1,t2,val1,false);
    		A[t1] = val2; A[t2] = val1;
    		update(0,N-1,1,val1,t2,true); update(0,N-1,1,val2,t1,true);
    		locs[val1] = t2, locs[val2] = t1;
    	}
    	else {
    		curLoc = search(0,N-1,1,t1,t2,true);
    		from = curLoc.min, to = curLoc.max;
    		curVal = search(0,N-1,1,from,to,false);
    		cout << ((curVal.min<t1 || curVal.max>t2) ? "NO\n" : "YES\n");
    	}
    }
    return 0;
}
