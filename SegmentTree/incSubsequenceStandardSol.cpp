#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000000007
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//백준 17411 풀이 2 (정해)

//풀이 2: 오프라인 쿼리 포함, 값 및 인덱스 기준 정렬
//앞 인덱스들 페어들 세그를 기반으로 업데이트
//이 문제에선 더 직관적

struct C{
	ll len, possibilities;
};

struct Q{
    ll val, atLoc;
};

const ll mx = 1000001;
ll N;
ll i, j, k;
ll A[mx];
C segTree[mx<<2];
C nullLeaf = {0,0}, prevs;
vector<Q> V;
Q cur;

bool sorter(Q q1, Q q2) {
    if(q1.val!=q2.val) return q1.val<q2.val;
    return q1.atLoc > q2.atLoc;
}

C merging(const C &lower, const C &upper) {
	if(lower.len!=upper.len) return (lower.len>upper.len) ? lower:upper;
	return {lower.len,(lower.possibilities+upper.possibilities)%MOD};
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll idx, C val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		segTree[node] = val;
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
    for(i=0;i<(mx<<2);i++) segTree[i] = {0,0};
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
        V.push_back({A[i],i});
    }
    sort(V.begin(),V.end(),sorter);
    for(i=0;i<N;i++) {
        cur = V[i];
    	prevs = search(0,N-1,1,0,cur.atLoc-1); 
        prevs = {prevs.len+1,(prevs.possibilities ? prevs.possibilities:1)};
    	update(0,N-1,1,cur.atLoc,prevs);
    }
    cout << segTree[1].len << ' ' << segTree[1].possibilities << '\n';
    return 0;
}