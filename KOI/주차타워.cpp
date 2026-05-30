#include <bits/stdc++.h>
#define ll long long int
#define INF 1e15
#define pii pair<ll, ll>
using namespace std;

//한국정보올림피아드 주차타워

const ll mx = 100001;
ll N, sz;
ll DP[2][mx], A[mx];
ll ans = LLONG_MAX;
pii segTree[2][mx<<2];
pii nullPair = {-1,-1};
vector<ll> V[mx], coords;

pii merging(const pii p1, const pii p2, int type) {
    if(p1.first==-1) return p2;
    else if(p2.first==-1) return p1;

    if(A[p1.first]>A[p2.first]) return p1;
    else if(A[p1.first]<A[p2.first]) return p2;
    
    if(type==0) {
        return (p1.second-p1.first<p2.second-p2.first) ? p1 : p2;
    } 
    return (p1.second+p1.first<p2.second+p2.first) ? p1 : p2;
}
pii search(ll start, ll end, ll node, ll lBound, ll rBound, ll type) {
    if(rBound<start || end<lBound) return nullPair;
    if(lBound<=start && end<=rBound) return segTree[type][node];
    ll mid = (start+end) >> 1;
    pii lower = search(start,mid,node<<1,lBound,rBound,type);
    pii upper = search(mid+1,end,node<<1|1,lBound,rBound,type);
    return merging(lower,upper,type);
}

void update(ll start, ll end, ll node, ll idx, pii val, ll type) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[type][node] = val;
        return;
    }
    ll mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx,val,type);
    else update(mid+1,end,node<<1|1,idx,val,type);
    segTree[type][node] = merging(segTree[type][node<<1], segTree[type][node<<1|1],type);
    return;
}

void nextEntry(int idx) {
    vector<ll> &cur = V[idx], &next = V[idx+1];
    int curSz = cur.size(), nextSz = next.size();
    for(int i=0;i<curSz;i++) {
        update(0,N-1,1,cur[i],make_pair(cur[i],DP[1][cur[i]]),0);
        update(0,N-1,1,cur[i],make_pair(cur[i],DP[1][cur[i]]),1);
    }
    for(int i=0;i<nextSz;i++) {
        pii loForward = search(0,N-1,1,0,next[i]-1,0);
        pii loBack = search(0,N-1,1,0,next[i]-1,1);
        if(A[loForward.first]==coords[idx]) {
            DP[0][next[i]] = min({
                DP[0][next[i]], 
                loForward.second+(next[i]-loForward.first),
                loBack.second + (loBack.first+N-next[i])%N
                });
        }
        pii hiForward = search(0,N-1,1,next[i]+1,N-1,0);
        pii hiBack = search(0,N-1,1,next[i]+1,N-1,1);
        if(A[hiForward.first]==coords[idx]) {
            DP[0][next[i]] = min({
                DP[0][next[i]],
                hiForward.second+(next[i]+N-hiForward.first)%N,
                hiBack.second+(hiBack.first-next[i])
            });
        }
    }
    return;
}

void oneWay(int idx) {
    vector<ll> &cur = V[idx];
    int curSz = cur.size();
    int gap;
    for(int i=0;i<curSz-1;i++) {
        gap = N-cur[i+1]+cur[i];
        DP[1][cur[i+1]] = min(DP[1][cur[i+1]], DP[0][cur[i]]+gap);
        DP[1][cur[i]] = min(DP[1][cur[i]], DP[0][cur[i+1]]+gap);
    }
    int lastIdx=curSz-1;
    DP[1][cur[lastIdx]] = min(DP[1][cur[lastIdx]], DP[0][cur[0]]+cur[lastIdx]-cur[0]);
    DP[1][cur[0]] = min(DP[1][cur[0]], DP[0][cur[lastIdx]]+cur[lastIdx]-cur[0]);
    return;
}

void twoWay(int idx) {
    vector<ll> &cur = V[idx];
    int curSz = cur.size();
    int bestIdx = 0;
    int dest, pivot;
    for(int i=0;i<curSz;i++) {
        dest = (i+1)%curSz, pivot = (i+2)%curSz;
        if(DP[0][cur[i]]+(cur[i]-cur[bestIdx])<DP[0][cur[bestIdx]]) {
            bestIdx = i;
        }
        ll travel = (cur[bestIdx]+N-cur[pivot])%N+(cur[dest]+N-cur[pivot])%N;
        DP[1][cur[dest]] = min(DP[1][cur[dest]], DP[0][cur[bestIdx]]+travel);
    }
    for(int i=0;i<curSz;i++) {
        dest = (i+1)%curSz, pivot = (i+2)%curSz;
        ll travel = (cur[bestIdx]+N-cur[pivot])%N+(cur[dest]+N-cur[pivot])%N;
        DP[1][cur[dest]] = min(DP[1][cur[dest]], DP[0][cur[bestIdx]]+travel);
    }
    bestIdx = curSz-1;
    for(int i=curSz-1;i>=0;i--) {
        dest = (i-1+curSz)%curSz, pivot = (i-2+curSz)%curSz;
        if(DP[0][cur[i]]+(cur[bestIdx]-cur[i])<DP[0][cur[bestIdx]]) {
            bestIdx = i;
        }
        ll travel = (cur[pivot]+N-cur[bestIdx])%N + (cur[pivot]+N-cur[dest])%N;
        DP[1][cur[dest]] = min(DP[1][cur[dest]],DP[0][cur[bestIdx]]+travel);
    }
    for(int i=curSz-1;i>=0;i--) {
        dest = (i-1+curSz)%curSz, pivot = (i-2+curSz)%curSz;
        ll travel = (cur[pivot]+N-cur[bestIdx])%N + (cur[pivot]+N-cur[dest])%N;
        DP[1][cur[dest]] = min(DP[1][cur[dest]],DP[0][cur[bestIdx]]+travel);
    }
    return;
}

void init() {
    for(int i=0;i<mx;i++) {
        DP[0][i] = DP[1][i] = INF;
    }
    for(int i=0;i<(mx<<2);i++) {
        segTree[0][i] = segTree[1][i] = nullPair;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    cin >> N;
    for(int i=0;i<N;i++) {
        cin >> A[i];
        coords.push_back(A[i]);
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    for(int i=0;i<N;i++) {
        int idx = lower_bound(coords.begin(),coords.end(),A[i])-coords.begin();
        V[idx].push_back(i);
    }
    sz = coords.size();
    for(int i=0;i<V[0].size();i++) {
        DP[0][V[0][i]] = min(V[0][i],N-V[0][i]);
    }
    for(int i=0;i<sz;i++) {
        oneWay(i); twoWay(i);
        if(i+1<sz) nextEntry(i);
    }
    for(int i=0;i<V[sz-1].size();i++) {
        ans = min(ans,DP[1][V[sz-1][i]]);
    }
    cout << ans << '\n';
    return 0;
}
