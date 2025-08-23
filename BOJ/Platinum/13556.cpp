#include <bits/stdc++.h>
#define ll long long int 
#define DIV 5000000
using namespace std;

//BOJ 13556: 증가하는 부분 수열 2
//난이도: 플레2

const ll mx = 100001;
ll exist[mx] = {0,},query[mx] = {0,};
ll N,K,sz=0;
ll segTree[51][mx<<2] = {0,};
ll i, j, k;
ll curSum, endVal;

ll search(ll start, ll end, ll node, ll lBound, ll rBound, ll atIdx) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[atIdx][node] % DIV;
	ll mid = (start+end) >> 1;
	return (search(start,mid,node<<1,lBound,rBound,atIdx) + search(mid+1,end,node<<1|1,lBound,rBound,atIdx))%DIV;
}

void update(ll start, ll end, ll node, ll idx, ll val, ll atIdx) {
	if(idx<start || end<idx) return;
	if(start==end) {
        segTree[atIdx][node] = val%DIV;
        return;
    }
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val,atIdx);
	else update(mid+1,end,node<<1|1,idx,val,atIdx);
	segTree[atIdx][node] = (segTree[atIdx][node<<1] + segTree[atIdx][node<<1|1]) %DIV;
    return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> K;
	for(i=0;i<N;i++) {
		cin >> query[i];
		exist[query[i]] = 1;
	}
	for(i=0;i<mx;i++) {
		if(exist[i]) {
			exist[i] = sz;
			sz++;
		}
	}
	for(i=0;i<N;i++) {
		endVal = exist[query[i]] -1;
		update(0,sz-1,1,exist[query[i]],1,1);
		for(j=1;j<K;j++) {
			curSum = search(0,sz-1,1,0,endVal,j);
			update(0,sz-1,1,exist[query[i]],curSum,j+1);
		}
	}
	cout << segTree[K][1] % DIV << '\n';
	return 0;
}
