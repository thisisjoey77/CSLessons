#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 24941: 줄넘기
//난이도: 플레2

struct C{
	ll val, atLoc;
};

struct D{
	ll lEnd, rEnd;
	ll isQuery;
};

const ll mx = 500001;
ll N, Q;
ll from, to;
ll i, j, k;
ll sz, numSz;
ll idx, maxVal, yCoord;
vector<C> V;
vector<ll> nums, heights;
vector<D> coords;
vector<pii> ans;
ll segTree[mx<<2] = {0,}, prevOccurence[mx];

bool sortCoords(D d1, D d2) {
	if(d1.lEnd!=d2.lEnd) return d1.lEnd > d2.lEnd;
	if(d1.rEnd!=d2.rEnd) return d1.rEnd < d2.rEnd;
	return d1.isQuery < d2.isQuery;
}

bool sortBack(pii p1, pii p2) {
	return p1.first < p2.first;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return 0;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	return max(
		search(start,mid,node<<1,lBound,rBound),
		search(mid+1,end,node<<1|1,lBound,rBound)
		);
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
    for(i=0;i<mx;i++) prevOccurence[i] = -1;
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
    	cin >> V[i].val;
    	V[i].atLoc = i;
    	heights.push_back(V[i].val);
    }
    cin >> Q;
    for(i=0;i<Q;i++) {
    	cin >> from >> to;
    	from --; to --;
    	nums.push_back(to);
    	coords.push_back({from,to,i+1});
    }
    sort(heights.begin(),heights.end());
    heights.erase(unique(heights.begin(),heights.end()),heights.end());
    for(i=0;i<N;i++) {
    	idx = lower_bound(heights.begin(),heights.end(),V[i].val)-heights.begin();
    	if(prevOccurence[idx]!=-1) {
    		coords.push_back({prevOccurence[idx],V[i].atLoc,0});
    		nums.push_back(V[i].atLoc);
    	}
    	prevOccurence[idx] = i;
    }
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    sort(coords.begin(),coords.end(),sortCoords);
    sz = coords.size(); numSz = nums.size();
    for(i=0;i<sz;i++) {
    	yCoord = lower_bound(nums.begin(),nums.end(),coords[i].rEnd)-nums.begin();
    	if(coords[i].isQuery) {
    		maxVal = search(0,numSz-1,1,0,yCoord);
    		ans.push_back(make_pair(coords[i].isQuery,maxVal));
    	}
    	else {
    		update(0,numSz-1,1,yCoord,coords[i].rEnd-coords[i].lEnd+1);
    	}
    }
    sort(ans.begin(),ans.end(),sortBack);
    for(i=0;i<Q;i++) {
    	cout << ans[i].second << '\n';
    }
    return 0;
}
