#include <bits/stdc++.h>
#define ll long long int
#define MOD 998244353
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16124: 나는 행복합니다
//난이도: 다이아4

struct C{
	int amt[10];
	int totSum, len;
	bool isNull;
};

struct D{
	int parent[10];
	bool active;
};

const ll mx = 1000001;
ll N, Q;
ll i, j, k, sz;
ll order, iO, jO, from, to;
ll pows[mx+1] = {0,};
string S;
C segTree[mx<<2];
C nullLeaf = {{0,},0,0,true}, defLeaf = {{0,},0,0,false};
D lazy[mx<<2];

C merging(const C &lower, const C &upper) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
    C ans = defLeaf;
    ll multBy = pows[upper.len]%MOD;
    ans.totSum = (upper.totSum%MOD+(lower.totSum%MOD)*multBy%MOD)%MOD;
    for(ll n=0;n<10;n++) {
        ans.amt[n] = (upper.amt[n]%MOD+(lower.amt[n]%MOD)*multBy%MOD)%MOD;
    }
    ans.len = lower.len + upper.len;
    ans.isNull = false;
    return ans;
}

C init(ll start, ll end, ll node) {
	if(start==end) {
        segTree[node] = {{0,},S[start]-'0',1,false};
        segTree[node].amt[S[start]-'0'] = 1;
		return segTree[node];
	}
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merging(lower, upper);
}

void lazyUpdate(ll start, ll end, ll node) {
    if(!lazy[node].active) return;
    ll newAmt[10] = {0,};
    for(ll j=0;j<10;j++) {
        ll oldAmt = segTree[node].amt[j];
        ll target = lazy[node].parent[j];
        newAmt[target] = (newAmt[target]+oldAmt)%MOD;
        if (target!=j) {
            segTree[node].totSum = (segTree[node].totSum-oldAmt*j%MOD+MOD)%MOD;
            segTree[node].totSum = (segTree[node].totSum+oldAmt*target%MOD)%MOD;
        }
    }
    for(ll j=0;j<10;j++) segTree[node].amt[j] = newAmt[j];
    if(start!=end) {
        lazy[node<<1].active = true;
        lazy[node<<1|1].active = true;
        for(ll j=0;j<10;j++) {
            lazy[node<<1].parent[j] = lazy[node].parent[lazy[node<<1].parent[j]];
            lazy[node<<1|1].parent[j] = lazy[node].parent[lazy[node<<1|1].parent[j]];
        }
    }
    for(ll j=0;j<10;j++) lazy[node].parent[j] = j;
    lazy[node].active = false;
    return;
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll from, ll to) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		lazy[node].parent[from] = to;
		lazy[node].active = true;
		lazyUpdate(start,end,node);
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,from,to);
	update(mid+1,end,node<<1|1,lBound,rBound,from,to);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    pows[0] = 1;
    for(i=1;i<=mx;i++) pows[i] = pows[i-1]*10%MOD;
    cin >> S >> Q;
    sz = S.size();
    for(i=0;i<(mx<<2);i++) {
    	for(ll j=0;j<10;j++) lazy[i].parent[j] = j;
    	lazy[i].active = false;
    }
    init(0,sz-1,1);
    for(i=0;i<Q;i++) {
    	cin >> order >> iO >> jO;
    	iO --; jO --;
    	if(order==1) {
    		cin >> from >> to;
    		update(0,sz-1,1,iO,jO,from,to);
    	}
    	else {
    		cout << search(0,sz-1,1,iO,jO).totSum%MOD << '\n';
    	}
    }
    return 0;
}
