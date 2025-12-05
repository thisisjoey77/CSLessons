#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000000007
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//백준 17411 풀이 1 (정해 ㄴㄴ)

//풀이 1: 오프라인 쿼리 아님, 순서대로 처리
//세그 기준은 좌표압축된 A[i] 값들
//체감상 더 복잡하고 덜 직관적

struct C{
	ll len, possibilities;
};

const ll mx = 1000001;
ll N;
ll i, j, k;
ll A[mx];
ll sz, idx;
C segTree[mx<<2];
C nullLeaf = {0,0}, cur, prevs;
vector<ll> coords;

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
    	coords.push_back(A[i]);
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = coords.size();
    for(i=0;i<N;i++) {
    	idx = lower_bound(coords.begin(),coords.end(),A[i])-coords.begin();
    	prevs = search(0,sz-1,1,0,idx-1); prevs.len++;
        if(prevs.len==1) prevs.possibilities = 1;
    	cur = search(0,sz-1,1,idx,idx);
    	if(cur.len!=prevs.len) update(0,sz-1,1,idx,prevs);
    	else update(0,sz-1,1,idx,{cur.len,(cur.possibilities+prevs.possibilities)%MOD});
    }
    cout << segTree[1].len << ' ' << segTree[1].possibilities << '\n';
    return 0;
}