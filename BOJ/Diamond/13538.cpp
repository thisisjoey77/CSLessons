#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13538: XOR 쿼리
//난이도: 다이아4

struct Node{
	ll l, r, val, onCnt;
	Node(): l(0), r(0), val(0), onCnt(0) {};
	Node(ll _l, ll _r, ll _val, ll _onCnt): l(_l), r(_r), val(_val), onCnt(_onCnt) {};
};

const ll mx = 600000, nMx = 524287;
ll M;
ll i, j, k;
ll order, L, R, x, lastJ=1, sz, roots[mx];
string bits, defaultOnes;
vector<Node> psegTree(mx<<2);

ll query4(ll start, ll end, ll node1, ll node2, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return psegTree[node2].val-psegTree[node1].val;
	ll mid = (start+end) >> 1;
	ll lower = query4(start,mid,psegTree[node1].l,psegTree[node2].l,lBound,rBound);
	ll upper = query4(mid+1,end,psegTree[node1].r,psegTree[node2].r,lBound,rBound);
	return lower + upper;
}

ll query5(ll start, ll end, ll node1, ll node2, ll target) {
	if(start==end) return start;
	ll mid = (start+end) >> 1;
	ll n1 = psegTree[node1].l, n2 = psegTree[node2].l;
	ll compVal = psegTree[n2].val - psegTree[n1].val;
	if(target<=compVal) return query5(start,mid,n1,n2,target);
	return query5(mid+1,end,psegTree[node1].r,psegTree[node2].r,target-compVal);
}

ll query2(ll start, ll end, ll node1, ll node2, string val, ll idx) {
	if(start==end) return start;
	ll mid = (start+end) >> 1;
	if(val[idx]-'0') {
		ll n1 = psegTree[node1].l, n2 = psegTree[node2].l;
		ll compVal = psegTree[n2].val - psegTree[n1].val;
		if(compVal) return query2(start,mid,n1,n2,val,idx+1);
		return query2(mid+1,end,psegTree[node1].r,psegTree[node2].r,val,idx+1);
	}
	else {
		ll n1 = psegTree[node1].r, n2 = psegTree[node2].r;
		ll compVal = psegTree[n2].val - psegTree[n1].val;
		if(compVal) return query2(mid+1,end,n1,n2,val,idx+1);
		return query2(start,mid,psegTree[node1].l,psegTree[node2].l,val,idx+1);
	}
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(start==end) {
		psegTree[node].onCnt = ((psegTree[node].val) ? 1:0);
		return;
	}
	ll mid = (start+end) >> 1;
	ll n1 = psegTree[node].l, n2 = psegTree[node].r;
	if(idx<=mid) {
		psegTree[node].l = psegTree.size();
		psegTree.push_back(Node(psegTree[n1].l,psegTree[n1].r,psegTree[n1].val+val,0));
		update(start,mid,psegTree[node].l,idx,val);
	}
	else {
		psegTree[node].r = psegTree.size();
		psegTree.push_back(Node(psegTree[n2].l,psegTree[n2].r,psegTree[n2].val+val,0));
		update(mid+1,end,psegTree[node].r,idx,val);
	}
	psegTree[node].onCnt = psegTree[psegTree[node].l].onCnt + psegTree[psegTree[node].r].onCnt;
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<19;i++) defaultOnes += '0';
    for(i=1;i<(nMx<<1);i++) psegTree[i] = Node(i<<1,i<<1|1,0,0);
    roots[0] = 1;
    cin >> M;
    while(M--) {
    	cin >> order;
    	if(order==1) {
    		cin >> x;
    		roots[lastJ] = psegTree.size();
    		psegTree.push_back(psegTree[roots[lastJ-1]]);
    		psegTree[roots[lastJ]].val ++;
    		update(0,nMx,roots[lastJ],x,1);
    		lastJ ++;
    	}
    	else if(order==2) {
    		cin >> L >> R >> x;
    		bits = defaultOnes;
    		j=bits.size()-1;
    		while(x) {
    			bits[j] += (x%2);
    			x >>= 1;
    			j--;
    		}
    		cout << query2(0,nMx,roots[L-1],roots[R],bits,0) << '\n';
    	}
    	else if(order==3) {
    		cin >> k;
    		lastJ -= k;
    	}
    	else if(order==4) {
    		cin >> L >> R >> x;
    		cout << query4(0,nMx,roots[L-1],roots[R],0,x) << '\n';
    	}
    	else {
    		cin >> L >> R >> k;
    		cout << query5(0,nMx,roots[L-1],roots[R],k) << '\n';
    	}
    }
    return 0;
}
