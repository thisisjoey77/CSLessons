#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2849: 탭댄스
//난이도: 플레1

struct C{
	ll maxLen;
	char leftEnd, rightEnd;
	ll leftMaxLen, rightMaxLen;
};

const ll mx = 200001;
ll N, Q;
ll i, j, k;
ll idx;
C segTree[mx<<2];
C nullLeaf = {1,'L','L',1,1}, outsideLeaf = {0,'E','E',0,0};

C merging(C lower, C upper, ll lowerInterval, ll upperInterval) {
	C child;
	child.maxLen = max(upper.maxLen, lower.maxLen);
	if(lower.rightEnd!=upper.leftEnd) {
		child.maxLen = max(child.maxLen, lower.rightMaxLen + upper.leftMaxLen);
	}
	child.leftEnd = lower.leftEnd, child.rightEnd = upper.rightEnd;
	if(child.leftEnd=='E') child.leftEnd = upper.leftEnd;
	if(child.rightEnd=='E') child.rightEnd = lower.rightEnd;
	child.leftMaxLen = lower.leftMaxLen;
	if(child.leftMaxLen==lowerInterval && lower.rightEnd!=upper.leftEnd) {
		child.leftMaxLen += upper.leftMaxLen;
	}
	child.rightMaxLen = upper.rightMaxLen;
	if(child.rightMaxLen==upperInterval && upper.leftEnd!=lower.rightEnd) {
		child.rightMaxLen += lower.rightMaxLen;
	}
	return child;
}

C init(ll start, ll end, ll node) {
	if(start==end) return segTree[node] = nullLeaf;
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1);
	C upper = init(mid+1,end,node<<1|1);
	ll lowerInterval = mid-start+1, upperInterval = end-(mid+1)+1;
	return segTree[node] = merging(lower,upper, lowerInterval, upperInterval);
}

void update(ll start, ll end, ll node, ll idx) {
	if(idx<start || end<idx) return;
	if(start==end) {
        segTree[node].leftEnd = ((segTree[node].leftEnd=='L') ? 'R' : 'L');
        segTree[node].rightEnd = segTree[node].leftEnd;
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx);
	else update(mid+1,end,node<<1|1,idx);
	C lower = segTree[node<<1], upper = segTree[node<<1|1];
	ll lowerInterval = mid-start+1, upperInterval = end-(mid+1)+1;
	segTree[node] = merging(lower,upper,lowerInterval, upperInterval);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    init(0,N-1,1);
    for(i=0;i<Q;i++) {
    	cin >> idx;
    	idx --;
    	update(0,N-1,1,idx);
    	cout << segTree[1].maxLen << '\n';
    }
    return 0;
}
