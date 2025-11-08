#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13557: 수열과 쿼리 10
//난이도: 다이아5

struct C{
	ll totSum, leftFixMax, rightFixMax, maxVal;
	bool isNull;
};

const ll mx = 100001;
C segTree[mx<<2];
C nullLeaf = {0,0,0,0,true};
ll N, M;
ll A[mx];
ll i, j, k;
ll xOne, yOne, xTwo, yTwo;
ll midSum, leftEnd, rightEnd;
ll ans;

C merging(C lower, C upper) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
	C ans = {
		lower.totSum + upper.totSum,
		lower.leftFixMax,
		upper.rightFixMax,
		max(lower.maxVal, upper.maxVal),
		false
	};
	ans.maxVal = max(ans.maxVal, lower.rightFixMax + upper.leftFixMax);
	ans.leftFixMax = max(ans.leftFixMax, lower.totSum + upper.leftFixMax);
	ans.rightFixMax = max(ans.rightFixMax, upper.totSum + lower.rightFixMax);
	return ans;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = {A[start],A[start],A[start],A[start],false};
	ll mid = (start+end) >> 1;
	return segTree[node] = merging(init(start,mid,node<<1), init(mid+1,end,node<<1|1));
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(lBound>rBound) return nullLeaf;
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower,upper);
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
    	cin >> xOne >> yOne >> xTwo >> yTwo;
    	xOne --; yOne --; xTwo --; yTwo --;
    	if(xTwo<=yOne) {
    		ans = max({
    			search(0,N-1,1,xTwo,yOne).maxVal,
    			search(0,N-1,1,xOne,xTwo-1).rightFixMax+search(0,N-1,1,xTwo,yTwo).leftFixMax,
    			search(0,N-1,1,yOne+1,yTwo).leftFixMax+search(0,N-1,1,xOne,yOne).rightFixMax
    		});
    		cout << ans << '\n';
    	}
    	else {
            midSum = ((yOne+1==xTwo) ? 0 : search(0,N-1,1,yOne+1,xTwo-1).totSum);
    		leftEnd = search(0,N-1,1,xOne,yOne).rightFixMax;
    		rightEnd = search(0,N-1,1,xTwo,yTwo).leftFixMax;
    		cout << leftEnd + midSum + rightEnd << '\n';
    	}
    }
    return 0;
}
