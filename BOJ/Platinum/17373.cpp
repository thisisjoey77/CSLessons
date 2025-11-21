#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17373: 녜힁
//난이도: 플레1

struct loc{ll val, loc;};
struct Node{
	ll l, r, val;
	Node(): l(0), r(0), val(0) {};
	Node(ll _l, ll _r, ll _val): l(_l), r(_r), val(_val) {};
};

const ll nMx = 100010, mMx = 1000010;
ll N, M, Q, K;
ll i, j, k, lastJ, idx;
bool vis[mMx]={0,};
ll A[nMx], roots[mMx], potentials[mMx]={0,};
vector<loc> V;
vector<Node> psegTree(mMx<<2);

ll init(ll start, ll end, ll node) {
	if(start==end) return psegTree[node].val = 1;
	ll mid = (start+end) >> 1;
	psegTree[node].l = node<<1; psegTree[node].r = node<<1|1;
	return psegTree[node].val = init(start,mid,node<<1) + init(mid+1,end,node<<1|1);
}

void update(ll start, ll end, ll node, ll idx) {
	if(start!=end) {
		ll mid = (start+end) >> 1;
		ll n1 = psegTree[node].l, n2 = psegTree[node].r;
		if(idx<=mid) {
			psegTree[node].l = psegTree.size();
			psegTree.push_back(Node(psegTree[n1].l,psegTree[n1].r,psegTree[n1].val-1));
			update(start,mid,psegTree[node].l,idx);
		}
		else {
			psegTree[node].r = psegTree.size();
			psegTree.push_back(Node(psegTree[n2].l,psegTree[n2].r,psegTree[n2].val-1));
			update(mid+1,end,psegTree[node].r,idx);
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

ll query(ll start, ll end, ll node, ll target) {
	if(start==end) return start;
	ll mid = (start+end) >> 1;
	ll leftIdx = psegTree[node].l, compVal = psegTree[leftIdx].val;
	if(target<=compVal) return query(start,mid,psegTree[node].l,target);
	return query(mid+1,end,psegTree[node].r,target-compVal);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<mMx;i++) roots[i] = LLONG_MAX;
    cin >> N >> M >> Q;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    	if(!vis[A[i]]) {
    		vis[A[i]] = true;
    		V.push_back({A[i],i});
    	}
    }
    init(1,M,1);
    for(i=0;i<mMx;i++) vis[i] = false;
    lastJ = V.size()-1, idx = V[lastJ].val, roots[idx] = 1;
    for(i=N-1;i>=0;i--) {
    	if(i==V[lastJ].loc) {
    		lastJ --;
    		if(lastJ>=0) {
    			ll prevRoot = roots[idx];
    			idx = V[lastJ].val;
    			roots[idx] = psegTree.size();
    			psegTree.push_back(psegTree[prevRoot]);
    		}
    	}
    	if(i && !vis[A[i]]) {
    		vis[A[i]] = true;
    		psegTree[roots[idx]].val --;
    		update(1,M,roots[idx],A[i]);
    	}
    }
    for(i=1;i<=M;i++) {
    	if(roots[i]!=LLONG_MAX) potentials[i] = psegTree[roots[i]].val+potentials[i-1];
    	else potentials[i] = M+potentials[i-1];
    }
    for(i=0;i<Q;i++) {
    	cin >> K;
    	if(potentials[M]<K) {
    	    cout << "-1 -1\n";
    	    continue;
    	}
    	idx = lower_bound(potentials,potentials+M,K)-potentials;
    	K -= potentials[idx-1];
    	cout << idx << ' ' << ((roots[idx]==LLONG_MAX) ? K : query(1,M,roots[idx],K)) << '\n';
    }
    return 0;
}
