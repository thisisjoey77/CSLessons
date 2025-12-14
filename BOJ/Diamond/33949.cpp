#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 33949:🍕😋🤮
//난이도: 다이아5

struct C{
	ll leftMax, rightMax, totMax;
	ll leftMin, rightMin, totMin;
	ll totSum;
	bool isNull;
};

const ll mx = 200001;
ll N, Q;
ll i, j, k;
ll order, a, b;
ll ans;
C segTree[mx<<2];
C nullLeaf={}, defLeaf={};

C merging(C lower, C upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	C ans = {
		max(lower.leftMax,lower.totSum+upper.leftMax),
		max(upper.rightMax,upper.totSum+lower.rightMax),
		max({lower.totMax,upper.totMax,lower.rightMax+upper.leftMax}),
		min(lower.leftMin,lower.totSum+upper.leftMin),
		min(upper.rightMin,upper.totSum+lower.rightMin),
		min({lower.totMin,upper.totMin,lower.rightMin+upper.leftMin}),
		lower.totSum+upper.totSum,
		false
	};
	return ans;
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		C cur = segTree[node];
		segTree[node] = {
			cur.leftMax+val, cur.rightMax+val, cur.totMax+val,
			cur.leftMin+val, cur.rightMin+val, cur.totMin+val,
			cur.totSum+val,
			false
		};
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
    cin >> N >> Q;
	for(i=0;i<(N<<2);i++) segTree[i] = defLeaf;
	for(i=(N<<2);i<(mx<<2);i++) segTree[i] = nullLeaf;
    while(Q --) {
    	cin >> order;
    	if(order==1) {
    		cin >> a >> b;
    		a --;
    		update(0,N-1,1,a,b);
    	}
    	else {
    		ans = segTree[1].totMax;
    		if(segTree[1].totMin!=segTree[1].totSum) ans = max(ans,segTree[1].totSum-segTree[1].totMin);
    		cout << ans << '\n';
    	}
    }
    return 0;
}