#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1615: 교차개수세기
//난이도: 플레5

struct C{
	ll from, to;
};

const ll mx = 2002;
ll N, M;
ll i, j, k;
ll from, to;
vector<C> V;
C cur;
ll segTree[mx<<2] = {0,};
ll ans = 0;

bool sorter(C c1, C c2) {
	if(c1.from!=c2.from) return c1.from<c2.from;
	return c1.to < c2.to;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	return search(start,mid,node<<1,lBound,rBound) + search(mid+1,end,node<<1|1,lBound,rBound);
}

void update(ll start, ll end, ll node, ll idx) {
	if(idx<start || end<idx) return;
	segTree[node] ++;
	if(start==end) return;
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx);
	else update(mid+1,end,node<<1|1,idx);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<M;i++) {
    	cin >> from >> to;
    	from--; to--;
    	V.push_back({from,to});
    }
    sort(V.begin(),V.end(),sorter);
    for(i=0;i<M;i++) {
    	cur = V[i];
    	ans += search(0,N-1,1,cur.to+1,N-1);
    	update(0,N-1,1,cur.to);
    }
    cout << ans << '\n';
    return 0;
}
