#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16136: 준하의 정수론 과제 (Divmaster)
//난이도: 플레2

struct C{
	ll sum;
	bool areFixed;
};

const ll mx = 100001, numMx = 1000001;
ll N, Q;
ll i, j, k;
C segTree[mx<<2];
ll A[mx]={0,}, primes[numMx] = {0,};
ll order, s, e;

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {A[start],((A[start]<=2) ? true : false)};
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
	return segTree[node] = {lower.sum+upper.sum, lower.areFixed && upper.areFixed};
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return {0,true};
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return {
	    lower.sum+upper.sum,
	    lower.areFixed && upper.areFixed
	};
}

void update(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return;
	if(segTree[node].areFixed) return;
	if(start==end) {
		segTree[node].sum = primes[segTree[node].sum];
		if(segTree[node].sum<=2) segTree[node].areFixed = true;
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound);
	update(mid+1,end,node<<1|1,lBound,rBound);
	segTree[node] = {
		segTree[node<<1].sum + segTree[node<<1|1].sum,
		segTree[node<<1].areFixed && segTree[node<<1|1].areFixed
	};
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    for(i=1;i<numMx;i++) {
    	for(j=i;j<numMx;j+=i) {
    		primes[j] ++;
    	}
    }
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<Q;i++) {
    	cin >> order >> s >> e;
    	s --; e --;
    	if(order==1) {
    		update(0,N-1,1,s,e);
    	}
    	else {
    		cout << search(0,N-1,1,s,e).sum << '\n';
    	}
    }
    return 0;
}
