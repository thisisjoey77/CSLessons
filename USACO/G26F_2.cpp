#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

const int mx = 500001;
ll T, N;
int segTree[mx<<2];
ll ans, amt[mx];
vector<pii> V;
vector<ll> coords;

bool sorter(pii p1, pii p2) {
    if(p1.first!=p2.first) return p1.first > p2.first;
    return p1.second > p2.second;
}

int init(int start, int end, int node) {
    if(start==end) return segTree[node] = 1;
    int mid = (start+end) >> 1;
    return segTree[node] = init(start,mid,node<<1) + init(mid+1,end,node<<1|1);
}

int search(int start, int end, int node, int lBound, int rBound) {
    if(rBound<start || end<lBound) return 0;
    if(lBound<=start && end<=rBound) return segTree[node];
    int mid = (start+end) >> 1;
    int lower = search(start,mid,node<<1,lBound,rBound);
    int upper = search(mid+1,end,node<<1|1,lBound,rBound);
    return lower + upper;
}

void update(int start, int end, int node, int idx) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] --;
        return;
    }
    int mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx);
    else update(mid+1,end,node<<1|1,idx);
    segTree[node] = segTree[node<<1] + segTree[node<<1|1];
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) {
        ans = 0;
        V = vector<pii>(); coords = vector<ll>();
        cin >> N;
        V.resize(N);
        for(int i=0;i<N;i++) {
            cin >> V[i].first;
            V[i].second = i;
            coords.push_back(V[i].first);
        }
        sort(coords.begin(),coords.end());
        vector<ll> vals = coords;
        coords.erase(unique(coords.begin(),coords.end()),coords.end());
        const int sz = coords.size();
        for(int i=0;i<sz;i++) amt[i] = 0;
        int idx = 0;
        for(int i=0;i<N;i++) {
            while(coords[idx]!=vals[i]) idx ++;
            amt[idx] ++;
        }
        init(0,N-1,1);
        sort(V.begin(),V.end(),sorter);
        idx = sz-1;
        for(int i=0;i<N;i++) {
            int leftSweep = search(0,N-1,1,0,V[i].second-1)-(--amt[idx]);
            int rightSweep = search(0,N-1,1,V[i].second+1,N-1);
            ans += min(leftSweep,rightSweep);
            update(0,N-1,1,V[i].second);
            if(!amt[idx]) idx --;
        }
        cout << ans << '\n';
    }
    return 0;
}
