#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000000007
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

const ll mx = 1000001;
ll N, D;
ll ans=0;
ll segTree[mx<<2], lazy[mx<<2];
vector<pii> V;

void lazyUpdate(int start, int end, int node) {
    if(lazy[node]==1) return;
    lazy[node]%=MOD;
    segTree[node] = (segTree[node]*lazy[node])%MOD;
    if(start!=end) {
        lazy[node<<1] = (lazy[node<<1]*lazy[node])%MOD;
        lazy[node<<1|1] = (lazy[node<<1|1]*lazy[node])%MOD;
    }
    lazy[node] = 1;
    return;
}

ll search(int start, int end, int node, int lBound, int rBound) {
    lazyUpdate(start,end,node);
    if(rBound<start || end<lBound) return 0;
    if(lBound<=start && end<=rBound) return segTree[node];
    int mid = (start+end) >> 1;
    ll lower = search(start,mid,node<<1,lBound,rBound)%MOD;
    ll upper = search(mid+1,end,node<<1|1,lBound,rBound)%MOD;
    return (lower+upper)%MOD;
}

void update(int start, int end, int node, int lBound, int rBound) {
    lazyUpdate(start,end,node);
    if(rBound<start || end<lBound) return;
    if(lBound<=start && end<=rBound) {
        lazy[node] <<= 1;
        lazyUpdate(start,end,node);
        return;
    }
    int mid = (start+end) >> 1;
    update(start,mid,node<<1,lBound,rBound);
    update(mid+1,end,node<<1|1,lBound,rBound);
    segTree[node] = (segTree[node<<1]+segTree[node<<1|1])%MOD;
    return;
}

void updatePoint(int start, int end, int node, int idx, ll val) {
    lazyUpdate(start,end,node);
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] = (segTree[node]+val)%MOD;
        return;
    }
    int mid = (start+end) >> 1;
    if(idx<=mid) updatePoint(start,mid,node<<1,idx,val);
    else updatePoint(mid+1,end,node<<1|1,idx,val);
    segTree[node] = (segTree[node<<1] + segTree[node<<1|1])%MOD;
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(lazy,1,sizeof(lazy));
    memset(segTree,0,sizeof(segTree));

    cin >> N >> D;
    V.resize(N);
    for(int i=0;i<N;i++) {
        cin >> V[i].first >> V[i].second;
    }

    int coachIdx=0, idx=0;
    while(coachIdx<N && !V[coachIdx].second) coachIdx ++;
    idx = coachIdx;
    updatePoint(0,N-1,1,idx,1);

    while(++idx<N) {
        if(V[idx].second) {
            updatePoint(0,N-1,1,idx,(segTree[1]+1)%MOD);
        }
        else {
            while((!V[coachIdx].second || V[idx].first-V[coachIdx].first>D) && coachIdx<idx) {
                coachIdx ++;
            }
            if(V[coachIdx].second) {
                update(0,N-1,1,coachIdx,idx-1);
            }
        }
    }
    cout << segTree[1]%MOD << '\n';
    return 0;
}
