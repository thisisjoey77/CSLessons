#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//Segment Tree Template
//세그트리 템플릿 (구간합 세그)

//크기 N 배열, 구간합 쿼리 M개
//쿼리 1: from번째 인덱스에서 to번째 인덱스까지 구간합 (1-based indexing)
//쿼리 2: idx번째 인덱스 값을 x로 변환

struct C{
	ll val;
	bool isNull;
};

const ll mx = 2000001;
ll N, M;
ll A[mx];
ll i, j, k;
ll order, from, to, idx, x;
C segTree[mx<<2];
C nullLeaf = {0,true};

C merging(C c1, C c2) {
	if(c1.isNull) return c2;
	if(c2.isNull) return c1;
	C ans = {
		c1.val + c2.val,
		false
	};
	return ans;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {A[start],false};
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merging(lower,upper);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		segTree[node] = {val,false};
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,idx,val);
	update(mid+1,end,node<<1|1,idx,val);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) {
    	segTree[i] = nullLeaf;
    }
    cin >> N >> M;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<M;i++) {
    	cin >> order;
    	if(order==1) {
    		cin >> from >> to;
    		from --; to --;
    		cout << search(0,N-1,1,from,to).val << '\n';
    	}
    	else {
    		cin >> idx >> x;
    		idx --;
    		update(0,N-1,1,idx,x);
    	}
    }
    return 0;
}
