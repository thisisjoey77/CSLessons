#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 20648: Rectangular Pasture
//난이도: 플레4

struct point{
    ll x,y;
};

const ll mx = 2501;
ll N;
ll ans = 1;
ll segTree[mx<<2];
vector<point> V;
vector<ll> yCoords, coordIdx;

bool sorter(point p1, point p2) {
    return p1.x < p2.x;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(rBound<start || end<lBound) return 0;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    ll lower = search(start,mid,node<<1,lBound,rBound);
    ll upper = search(mid+1,end,node<<1|1,lBound,rBound);
    return lower+upper;
}

void update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] += val;
        return;
    }
    ll mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx,val);
    else update(mid+1,end,node<<1|1,idx,val);
    segTree[node] = segTree[node<<1] + segTree[node<<1|1];
    return;
}


void init() {
    ll i;
    for(i=0;i<(mx<<2);i++) {
        segTree[i] = 0;
    }
    return;
}

void input() {
    ll i;
    cin >> N;
    V.resize(N); yCoords.resize(N); coordIdx.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i].x >> V[i].y;
        yCoords[i] = V[i].y;
    }
    sort(V.begin(),V.end(),sorter);
    sort(yCoords.begin(),yCoords.end());
    for(i=0;i<N;i++) {
        coordIdx[i] = lower_bound(yCoords.begin(),yCoords.end(),V[i].y)-yCoords.begin();
    }
    return;
}

void solve() {
    ll i, j, k;
    ll lowerIdx, upperIdx;
    for(i=0;i<N;i++) {
        for(j=0;j<i;j++) {
            lowerIdx = min(coordIdx[i],coordIdx[j]), upperIdx = max(coordIdx[i],coordIdx[j]);
            ans += (search(0,N-1,1,0,lowerIdx-1)+1) * (search(0,N-1,1,upperIdx+1,N-1)+1);
            update(0,N-1,1,coordIdx[j],-1);
        }
        for(j=0;j<=i;j++) {
            update(0,N-1,1,coordIdx[j],1);
        }
        ans ++;
    }
    return;
}

void output() {
    cout << ans << '\n';
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    input();
    solve();
    output();
    return 0;
}
