#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 32411: 계단 수열과 쿼리
//난이도: 다이아5

struct D{
	//위치, 값
	pii leftEnd, rightEnd;
};

struct C{
	D leftFixMax[11], rightFixMax[11], totMax[11];
	bool isNull;
};

const ll mx = 100001;
ll N, Q;
ll order, oI, oJ, oX, oK;
ll i, j, k;
C segTree[mx<<2];
C nullLeaf;
D ans;
ll lazy[mx<<2] = {0,}, A[mx];

C merging(C lower, C upper, ll start, ll end) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	ll mid = (start+end) >> 1;
	C ans; ans.isNull = false;
	for(ll j=1;j<=10;j++) {
		ans.leftFixMax[j] = lower.leftFixMax[j];
		ans.rightFixMax[j] = upper.rightFixMax[j];
		ll lowerDiff = lower.totMax[j].rightEnd.first-lower.totMax[j].leftEnd.first;
		ll upperDiff = upper.totMax[j].rightEnd.first-upper.totMax[j].leftEnd.first;
		ans.totMax[j] = ((lowerDiff>upperDiff) ? lower.totMax[j] : upper.totMax[j]);
		//맥스
		ll diff = abs(lower.rightFixMax[j].rightEnd.second-upper.leftFixMax[j].leftEnd.second);
		if(diff==j) {
			ll newLen = upper.leftFixMax[j].rightEnd.first-lower.rightFixMax[j].leftEnd.first+1;
			ll oldLen = ans.totMax[j].rightEnd.first - ans.totMax[j].leftEnd.first+1;
			if(newLen > oldLen) {
				ans.totMax[j] = {lower.rightFixMax[j].leftEnd, upper.leftFixMax[j].rightEnd};
			}
		}
		//왼쪽 끝 갱신
		diff = abs(upper.leftFixMax[j].leftEnd.second-lower.leftFixMax[j].rightEnd.second);
		if(lower.leftFixMax[j].rightEnd.first==mid && diff==j) {
			ans.leftFixMax[j].rightEnd = upper.leftFixMax[j].rightEnd;
		}
		//오른쪽 끝 갱신
		diff = abs(upper.rightFixMax[j].leftEnd.second-lower.rightFixMax[j].rightEnd.second);
		if(upper.rightFixMax[j].leftEnd.first==mid+1 && diff==j) {
			ans.rightFixMax[j].leftEnd = lower.rightFixMax[j].leftEnd;
		}
	}
	return ans;
}

void lazyUpdate(ll start, ll end, ll node) {
	if(lazy[node]) {
		for(ll j=1;j<=10;j++) {
			segTree[node].leftFixMax[j].leftEnd.second += lazy[node];
			segTree[node].leftFixMax[j].rightEnd.second += lazy[node];
			segTree[node].rightFixMax[j].leftEnd.second += lazy[node];
			segTree[node].rightFixMax[j].rightEnd.second += lazy[node];
			segTree[node].totMax[j].leftEnd.second += lazy[node];
			segTree[node].totMax[j].rightEnd.second += lazy[node];
		}
		if(start!=end) {
			lazy[node<<1] += lazy[node];
			lazy[node<<1|1] += lazy[node];
		}
		lazy[node] = 0;
	}
	return;
}

C init(ll start, ll end, ll node) {
	if(start==end) {
		segTree[node].isNull = false;
		for(ll j=1;j<=10;j++) {
			segTree[node].leftFixMax[j].leftEnd = {start,A[start]};
			segTree[node].leftFixMax[j].rightEnd = {start,A[start]};
			segTree[node].rightFixMax[j].leftEnd = {start,A[start]};
			segTree[node].rightFixMax[j].rightEnd = {start,A[start]};
			segTree[node].totMax[j].leftEnd = {start,A[start]};
			segTree[node].totMax[j].rightEnd = {start,A[start]};
		}
		return segTree[node];
	}
	ll mid = (start+end) >> 1;
	return segTree[node] = merging(init(start,mid,node<<1), init(mid+1,end,node<<1|1),start,end);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper,start,end);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
		lazy[node] += val;
		lazyUpdate(start,end,node);
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1],start,end);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    nullLeaf.isNull = true;
    cin >> N >> Q;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<Q;i++) {
    	cin >> order >> oI >> oJ;
        oI --; oJ --;
    	if(order==1) {
    		cin >> oX;
    		update(0,N-1,1,oI,oJ,oX);
    	}
    	else {
    		cin >> oK;
    		ans = search(0,N-1,1,oI,oJ).totMax[oK];
    		cout << ans.rightEnd.first - ans.leftEnd.first+1 << '\n';
    	}
    }
    return 0;
}
