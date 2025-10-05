#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 3002: 아날로그 다이얼
//난이도: 플레2

struct C{
	ll vals[10];
};

const ll mx = 250001;
ll N, M;
ll i, j, k;
ll from, to;
C segTree[mx<<2];
C nullNode = {{0,}}, curAns;
ll curSum;
ll lazy[mx<<2] = {0,};
string txt;

C merging(C lower, C upper) {
	C ans;
	for(ll k=0;k<10;k++) {
		ans.vals[k] = lower.vals[k] + upper.vals[k];
	}
	return ans;
}

void lazyUpdate(ll start, ll end, ll node) {
	if(lazy[node]) {
		C newLeaf;
		for(ll k=0;k<10;k++) {
			newLeaf.vals[(k+lazy[node])%10] = segTree[node].vals[k];
		}
		segTree[node] = newLeaf;
		if(start!=end) {
			lazy[node<<1] += lazy[node];
			lazy[node<<1|1] += lazy[node];
		}
		lazy[node] = 0;
	}
	return;
}

C init(ll start, ll end, ll node) {
	C leaf;
	for(ll k=0;k<10;k++) leaf.vals[k] = 0;
	if(start==end) {
		leaf.vals[txt[start]-'0'] ++;
		return segTree[node] = leaf;
	}
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1);
	C upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merging(lower,upper);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(end<lBound || rBound<start) return nullNode;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower,upper);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
	lazyUpdate(start,end,node);
	if(end<lBound || rBound<start) return;
	if(lBound<=start && end<=rBound) {
		C newLeaf;
		for(ll k=0;k<10;k++) {
			newLeaf.vals[(k+val)%10] = segTree[node].vals[k];
		}
		if(start!=end) {
			lazy[node<<1] += val;
			lazy[node<<1|1] += val;
		}
		segTree[node] = newLeaf;
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	C lower = segTree[node<<1], upper = segTree[node<<1|1];
	segTree[node] = merging(lower,upper);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> txt;
    init(0,N-1,1);
    for(i=0;i<M;i++) {
    	cin >> from >> to;
    	from --; to --;
    	curSum = 0;
    	curAns = search(0,N-1,1,from,to);
    	for(k=0;k<10;k++) {
    		curSum += curAns.vals[k]*k;
    	}
    	cout << curSum << '\n';
    	update(0,N-1,1,from,to,1);
    }
    return 0;
}
