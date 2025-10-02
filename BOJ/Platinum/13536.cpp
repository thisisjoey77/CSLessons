#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13536: 괄호 부분 문자열 쿼리
//난이도: 플레2

struct C{
	ll maxLen;
	ll open, closed;
};

const ll mx = 1000001;
string txt;
ll N;
ll i, j, k;
ll sz;
ll from, to;
C segTree[mx<<2];

C merge(C c1, C c2) {
    C ans;
    ll adder = min(c1.open, c2.closed);
    ans.maxLen = c1.maxLen + c2.maxLen + adder*2;
    ans.open = c1.open + c2.open - adder;
    ans.closed = c1.closed + c2.closed - adder;
    return ans;
}

C init(ll start, ll end, ll node) {
	C child = {0,0,0};
	if(start==end) {
		child.maxLen = 0;
		if(txt[start]=='(') child.open=1;
		else child.closed=1;
		return segTree[node] = child;
	}
	ll mid = (start+end) >> 1;
	C lower = init(start,mid,node<<1);
	C upper = init(mid+1,end,node<<1|1);
	return segTree[node] = merge(lower,upper);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return {0,0,0};
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper= search(mid+1,end,node<<1|1,lBound,rBound);
	return merge(lower,upper);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) {
        segTree[i] = {0,0,0};
    }
    cin >> txt >> N;
    sz = txt.size();
    init(0,sz-1,1);
    for(i=0;i<N;i++) {
    	cin >> from >> to;
    	from --; to --;
    	cout << search(0,sz-1,1,from,to).maxLen << '\n';
    }
    return 0;
}
