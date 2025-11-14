#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 29770: 서로 다른 최대 구간 쿼리
//난이도: 플레2

struct D{
	ll from, to, atLoc, ans;
};

const ll mx = 500001;
ll N, Q;
ll i, j, k;
ll A[mx], vis[mx] = {0,};
ll startPoint=0, endPoint=0;
ll from, to;
ll segTree[mx<<2] = {0,};
ll lastJ = 0;
vector<D> query;

bool sorter(D d1, D d2) {
	return d1.to < d2.to;
}

bool sortBack(D d1, D d2) {
	return d1.atLoc < d2.atLoc;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	ll lower = search(start,mid,node<<1,lBound,rBound);
	ll upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return max(lower,upper);
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		segTree[node] = val;
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val);
	else update(mid+1,end,node<<1|1,idx,val);
	segTree[node] = max(segTree[node<<1], segTree[node<<1|1]);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    cin >> Q;
    query.resize(Q);
    for(i=0;i<Q;i++) {
    	cin >> query[i].from >> query[i].to;
    	query[i].from --; query[i].to --;
    	query[i].atLoc = i;
    }
    sort(query.begin(),query.end(),sorter);
    while(endPoint<N) {
    	vis[A[endPoint]] ++;
    	while(vis[A[endPoint]]>1) {
    		startPoint ++;
    		vis[A[startPoint-1]] --;
    		update(0,N-1,1,startPoint,(endPoint-1-startPoint+1));
    	}
    	update(0,N-1,1,startPoint,(endPoint-startPoint+1));
    	while(lastJ<Q && query[lastJ].to==endPoint) {
    		from = query[lastJ].from, to = query[lastJ].to;
    		if(from>startPoint) update(0,N-1,1,from,(endPoint-from+1));
    		query[lastJ].ans = search(0,N-1,1,from,to);
    		lastJ ++;
    	}
    	endPoint ++;
    }
    sort(query.begin(),query.end(),sortBack);
    for(i=0;i<Q;i++) {
    	cout << query[i].ans << '\n';
    }
    return 0;
}
