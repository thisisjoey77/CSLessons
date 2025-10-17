#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000000007
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13925: 수열과 쿼리 13
//난이도: 다이아5

struct C{
	ll multiply, add;
	pair<bool,ll> reset;
};

const ll mx = 100001;
ll N, M;
ll i, j, k;
ll order, x, y, v;
ll A[mx];
C lazy[mx<<2];
C nullLeaf = {1,0,{false,0}};
ll segTree[mx<<2] = {0,};

ll init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = A[start];
	ll mid = (start+end) >> 1;
	return segTree[node] = (init(start,mid,node<<1) + init(mid+1,end,node<<1|1))%MOD;
}


void lazyUpdate(ll start, ll end, ll node) {
	if(lazy[node].reset.first) {
	    lazy[node].reset.second %= MOD;
		segTree[node] = (lazy[node].reset.second*(end-start+1))%MOD;
		if(start!=end) {
			lazy[node<<1] = nullLeaf; lazy[node<<1|1] = nullLeaf;
			lazy[node<<1].reset = lazy[node].reset;
			lazy[node<<1|1].reset = lazy[node].reset;
		}
		lazy[node].reset = make_pair(false,0);
	}
	segTree[node] %= MOD;
	lazy[node].multiply %= MOD;
	segTree[node] = (segTree[node]*lazy[node].multiply)%MOD;
    if(start!=end) {
    	lazy[node<<1].multiply %= MOD; lazy[node<<1|1].multiply %= MOD;
    	lazy[node<<1].add %= MOD; lazy[node<<1|1].add %= MOD;
    	lazy[node<<1].multiply = (lazy[node<<1].multiply*lazy[node].multiply)%MOD;
    	lazy[node<<1|1].multiply = (lazy[node<<1|1].multiply*lazy[node].multiply)%MOD;
    	lazy[node<<1].add = (lazy[node<<1].add*lazy[node].multiply)%MOD;
    	lazy[node<<1|1].add = (lazy[node<<1|1].add*lazy[node].multiply)%MOD;
    }
    segTree[node] %= MOD;
    lazy[node].add %= MOD;
	segTree[node] = (segTree[node]%MOD+(lazy[node].add*(end-start+1))%MOD);
    if(start!=end) {
    	lazy[node<<1].add %= MOD; lazy[node<<1|1].add %= MOD;
        lazy[node<<1].add = (lazy[node<<1].add+lazy[node].add)%MOD;
        lazy[node<<1|1].add = (lazy[node<<1|1].add+lazy[node].add)%MOD;
    }
	lazy[node].add = 0; lazy[node].multiply = 1;
	return;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node]%MOD;
	ll mid = (start+end) >> 1;
	return (search(start,mid,node<<1,lBound,rBound)+search(mid+1,end,node<<1|1,lBound,rBound))%MOD;
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, pii val) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		if(val.first==1) {
			segTree[node] = (segTree[node]+((end-start+1)*val.second)%MOD)%MOD;
			if(start!=end) {
                lazy[node<<1].add %= MOD; lazy[node<<1|1].add %= MOD;
				lazy[node<<1].add = (lazy[node<<1].add+val.second)%MOD;
				lazy[node<<1|1].add = (lazy[node<<1|1].add+val.second)%MOD;
			}
		}
		else if(val.first==2) {
			segTree[node] = (segTree[node]*val.second)%MOD;
			if(start!=end) {
                lazy[node<<1].add %= MOD; lazy[node<<1|1].add %= MOD;
    	        lazy[node<<1].multiply = (lazy[node<<1].multiply*lazy[node].multiply)%MOD;
				lazy[node<<1].multiply = (lazy[node<<1].multiply*val.second)%MOD;
				lazy[node<<1|1].multiply = (lazy[node<<1|1].multiply*val.second)%MOD;
                lazy[node<<1].add = (lazy[node<<1].add*val.second)%MOD;
    	        lazy[node<<1|1].add = (lazy[node<<1|1].add*val.second)%MOD;
			}
		}
		else {
			segTree[node] = ((end-start+1)*val.second)%MOD;
            if(start!=end) {
                lazy[node<<1] = nullLeaf; lazy[node<<1|1] = nullLeaf;
    			lazy[node<<1].reset = make_pair(true,val.second);
    			lazy[node<<1|1].reset = make_pair(true,val.second);
            }
		}
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	segTree[node] = (segTree[node<<1]%MOD + segTree[node<<1|1]%MOD);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) lazy[i] = nullLeaf;
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    cin >> M;
    for(i=0;i<M;i++) {
    	cin >> order >> x >> y;
    	x --; y --;
    	if(order==4) {
    		cout << search(0,N-1,1,x,y) << '\n';
    		continue;
    	}
    	cin >> v;
    	update(0,N-1,1,x,y,make_pair(order, v%MOD));
    }
    return 0;
}
