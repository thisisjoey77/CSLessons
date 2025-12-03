#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17975: Strike Zone
//난이도: 다이아5

struct C{
	ll leftMax, rightMax, totMax, totSum;
	bool isNull;
};

struct ball{
	ll xLoc, y, val;
};

const ll mx = 2001;
ll nOne, nTwo;
ll i, j, k, lastJ=0, lastX, idx;
ll x, y, cOne, cTwo, sz, vSz;
ll ans = LLONG_MIN;
vector<ll> coords;
vector<ball> V;
C segTree[mx<<2];
C nullLeaf={0,0,0,0,true}, defLeaf={0,0,0,0,false};

bool sorter(ball b1, ball b2) {
	return b1.xLoc < b2.xLoc;
}

C merging(C lower, C upper) {
	if(lower.isNull) return upper;
	if(upper.isNull) return lower;
	C ans = {
		max(lower.leftMax, lower.totSum+upper.leftMax),
		max(upper.rightMax, upper.totSum+lower.rightMax),
		max({lower.totMax,upper.totMax,lower.rightMax+upper.leftMax}),
		lower.totSum + upper.totSum,
		false
	};
	return ans;
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	C lower = search(start,mid,node<<1,lBound,rBound);
	C upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || end<idx) return;
	if(start==end) {
		segTree[node] = {val,val,val,val,false};
		return;
	}
	ll mid = (start+end) >> 1;
	if(idx<=mid) update(start,mid,node<<1,idx,val);
	else update(mid+1,end,node<<1|1,idx,val);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1]);
	return;
}

void updateBalls(bool backTrack, ll to) {
	ll addVal=0, lastUpJ=0, lastUpX;
	while(lastUpJ<=to) {
		lastUpX = V[lastUpJ].xLoc;
		while(lastUpJ<=to && V[lastUpJ].xLoc==lastUpX) {
			idx = lower_bound(coords.begin(),coords.end(),V[lastUpJ].y)-coords.begin();
			if(!backTrack) addVal = ((V[lastUpJ].val&1) ? cOne : -cTwo);
			update(0,mx-1,1,idx,addVal);
			lastUpJ ++;
		}
		ans = max(ans,segTree[1].totMax);
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<(mx<<2);i++) segTree[i] = defLeaf;
    cin >> nOne;
    for(i=0;i<nOne;i++) {
    	cin >> x >> y;
    	coords.push_back(y);
    	V.push_back({x,y,1});
    }
    cin >> nTwo;
    for(i=0;i<nTwo;i++) {
    	cin >> x >> y;
    	coords.push_back(y);
    	V.push_back({x,y,2});
    }
    sort(V.begin(),V.end(),sorter);
    cin >> cOne >> cTwo;
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    sz = nOne+nTwo;
    while(lastJ<sz) {
    	lastX = V[lastJ].xLoc;
    	while(lastJ<sz && V[lastJ].xLoc==lastX) {
    		idx = lower_bound(coords.begin(),coords.end(),V[lastJ].y)-coords.begin();
    		update(0,mx-1,1,idx,((V[lastJ].val&1) ? cOne : -cTwo));
    		lastJ ++;
    	}
    	ans = max(ans,segTree[1].totMax);
    	updateBalls(true,lastJ-1);
    	updateBalls(false,lastJ-1);
    }
    cout << ans << '\n';
    return 0;
}
