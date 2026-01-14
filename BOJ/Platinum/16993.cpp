#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16993: 연속합과 쿼리
//난이도: 플레1

struct C{
	bool isNull;
	ll maxSum, maxLeft, maxRight, totSum;
};

const ll mx = 100001;
ll N, M;
ll A[mx];
ll i, j, k;
ll from, to;
C segTree[mx<<2];
C nullLeaf = {true,0,0,0,0};

C merging(const C &lower, const C &upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	C ans;
	ans.totSum = lower.totSum + upper.totSum;
	ans.maxLeft = max(lower.maxLeft, lower.totSum+upper.maxLeft);
	ans.maxRight = max(upper.maxRight, upper.totSum+lower.maxRight);
	ans.maxSum = max({lower.maxSum, upper.maxSum, lower.maxRight+upper.maxLeft});
	ans.isNull = false;
	return ans;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {false,A[start],A[start],A[start],A[start]};
	ll mid = (start+end) >> 1;
	init(start,mid,node<<1); init(mid+1,end,node<<1|1);
	return segTree[node] = merging(segTree[node<<1], segTree[node<<1|1]);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    cin >> M;
    for(i=0;i<M;i++) {
    	cin >> from >> to;
    	from --; to --;
    	cout << search(0,N-1,1,from,to).maxSum << '\n';
    }
    return 0;
}