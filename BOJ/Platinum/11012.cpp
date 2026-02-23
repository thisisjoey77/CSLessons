#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 11012: Egg
//난이도: 플레2

struct Node{
	ll l, r, val;
	Node(): l(0), r(0), val(0) {};
	Node(ll _l, ll _r, ll _val): l(_l), r(_r), val(_val) {};
};

const ll mx = 100001;
ll N, T, M;
ll i, j, k;
ll x, y, l, r, b, t;
ll sz, ans;
ll roots[mx+1];
vector<Node> psegTree;
vector<vector<ll>> yCoords;

void init() {
	ll tsz = mx>>1;
	for(ll j=1;j<=sz;j++) {
		psegTree[j].l = j<<1;
		psegTree[j].r = j<<1|1;
	}
	return;
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(start!=end) {
		ll mid = (start+end) >> 1;
		ll n1 =psegTree[node].l, n2 = psegTree[node].r;
		if(idx<=mid) {
			psegTree[node].l = psegTree.size();
			psegTree.push_back(Node(psegTree[n1].l, psegTree[n1].r, psegTree[n1].val+val));
			update(start,mid,psegTree[node].l,idx,val);
		}
		else {
			psegTree[node].r = psegTree.size();
			psegTree.push_back(Node(psegTree[n2].l,psegTree[n2].r,psegTree[n2].val+val));
			update(mid+1,end,psegTree[node].r,idx,val);
		}
	}
	return;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return psegTree[node].val;
	ll mid = (start+end) >> 1;
	ll n1 = psegTree[node].l, n2 = psegTree[node].r;
	return search(start,mid,n1,lBound,rBound) + search(mid+1,end,n2,lBound,rBound);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) {
    	psegTree = vector<Node>(mx<<2);
    	yCoords = vector<vector<ll>>(mx+1);
    	init();
    	cin >> N >> M;
    	for(i=0;i<N;i++) {
    		cin >> x >> y;
    		yCoords[++x].push_back(++y);
    	}
    	roots[0] = 1;
    	for(i=1;i<=mx;i++) {
    		roots[i] = psegTree.size();
    		ll prevRoot = roots[i-1];
    		psegTree.push_back(psegTree[prevRoot]);
    		sz = yCoords[i].size();
    		for(j=0;j<sz;j++) {
    			psegTree[roots[i]].val ++;
    			update(1,mx,roots[i],yCoords[i][j],1);
    		}
    	}
    	ans = 0;
    	for(i=0;i<M;i++) {
    		cin >> l >> r >> b >> t;
    		r++; b++; t++;
    		ans += search(1,mx,roots[r],b,t)-search(1,mx,roots[l],b,t);
    	}
    	cout << ans << '\n';
    }
    return 0;
}
