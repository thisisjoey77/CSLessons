#include <bits/stdc++.h>
#define ll long long int 
#define INF 1000000007
using namespace std;

//BOJ 17411: 가장 긴 증가하는 부분 수열 6
//난이도: 플레2

struct pii{
	ll length, possibilities;
};

struct C{
	ll val, atLoc;
};


vector<C> V;
const ll mx = 1000001;
pii segTree[mx<<2];
ll num;
ll N, i, j, k;
C cur;

pii search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return {0,0};
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	pii lower = search(start,mid,node<<1,lBound,rBound);
	pii upper = search(mid+1,end,node<<1|1,lBound,rBound);
	if(lower.length != upper.length) return ((lower.length > upper.length) ? lower : upper);
	return {lower.length, ((lower.possibilities + upper.possibilities)%INF)};
}

pii update(ll start, ll end, ll node, ll val, ll cnt, ll idx) {
	if(idx<start || end<idx) return {0,0};
	if(start==end) return segTree[node] = {val,cnt};
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,val,cnt,idx);
	update(mid+1,end,node<<1|1,val,cnt,idx);
	pii lower = segTree[node<<1], upper = segTree[node<<1|1];
	if(lower.length != upper.length) return segTree[node] = ((lower.length > upper.length) ? lower : upper);
	return segTree[node] = {lower.length,((lower.possibilities + upper.possibilities)%INF)};
}

bool sorter(C c1, C c2) {
	if(c1.val!=c2.val) return c1.val < c2.val;
	return c1.atLoc > c2.atLoc;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for(i=0;i<N;i++) {
		cin >> num;
		V.push_back({num,i});
	}
	sort(V.begin(),V.end(),sorter);
	for(i=0;i<N;i++) {
		cur = V[i];
		pii lowerSearch = search(0,N-1,1,0,cur.atLoc-1);
		ll adder = lowerSearch.length;
		ll pos;
		adder ++;
		if(!lowerSearch.length) pos =1; else pos = lowerSearch.possibilities;
		update(0,N-1,1,adder,pos%INF,cur.atLoc);
	}
	cout << segTree[1].length << ' ' << segTree[1].possibilities%INF << '\n';
	return 0;
}
