#include <bits/stdc++.h>
#define ll long long int
#define INF 1e18
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 23840: 두 단계 최단경로 4
//난이도: 플레4

const ll mx = 21, bitMx = 1<<20, nMx = 100001; 
ll N, M, P, X, Z;
ll dist[mx][mx], startDist[mx], endDist[mx], DP[mx][bitMx];
vector<pii> G[nMx], bitIdx;
vector<ll> points;

ll numBits(ll idx) {
    ll ans = 0;
    while(idx) {
        ans += idx&1;
        idx>>=1;
    }
    return ans;
}

bool sorter(pii p1, pii p2) {
    return p1.second < p2.second;
}

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<bitMx;j++) {
            DP[i][j] = INF;
        }
    }
    for(i=0;i<mx;i++) {
        startDist[i] = endDist[i] = INF;
    }
    return;
}

void input() {
    ll i;
    ll u, v, w;
    cin >> N >> M;
    for(i=0;i<M;i++) {
        cin >> u >> v >> w;
        G[u].push_back(make_pair(v,w));
        G[v].push_back(make_pair(u,w));
    }
    cin >> X >> Z >> P;
    points.resize(P);
    for(i=0;i<P;i++) {
        cin >> points[i];
    }
    sort(points.begin(),points.end());
    for(i=1;i<(1<<P);i++) {
        bitIdx.push_back(make_pair(i,numBits(i)));
    }
    sort(bitIdx.begin(),bitIdx.end(),sorter);
    return;
}

void dijkstra(ll a, ll *dist) {
    ll i;
    ll allDist[nMx];
    ll start = ((a==-1) ? X : points[a]);
    priqueue PQ;
    for(i=0;i<nMx;i++) {
        allDist[i] = INF;
    }
    PQ.push(make_pair(0,start));
    allDist[start] = 0;
    ll curCost, curTo, totCost,sz;
    while(!PQ.empty()) {
        curCost = PQ.top().first;
        curTo = PQ.top().second;
        PQ.pop();
        if(allDist[curTo]<curCost) continue;
        sz = G[curTo].size();
        for(i=0;i<sz;i++) {
            totCost = curCost+G[curTo][i].second;
            if(totCost<allDist[G[curTo][i].first]) {
                allDist[G[curTo][i].first] = totCost;
                PQ.push(make_pair(totCost,G[curTo][i].first));
            }
        }
    }
    for(i=0;i<P;i++) {
        dist[i] = allDist[points[i]];
    }
    if(start!=X) endDist[a] = allDist[Z];
    return;
}

void solve() {
    ll i, j, k, curIdx, nIdx;
    ll sz;
    dijkstra(-1,startDist);
    for(i=0,j=1;i<P;i++,j<<=1) {
        DP[i][j] = startDist[i];
    }
    for(i=0;i<P;i++) {
        dijkstra(i,dist[i]);
    }
    sz = bitIdx.size();
    for(i=0;i<sz;i++) {
        curIdx = bitIdx[i].first;
        for(j=0;j<P;j++) {
            if(!(curIdx&(1<<j))) continue;
            for(k=0;k<P;k++) {
                if(curIdx&(1<<k)) continue;
                nIdx = curIdx|(1<<k);
                DP[k][nIdx] = min(DP[k][nIdx],DP[j][curIdx]+dist[j][k]);
            }
        }
    }
    return;
}

void output() {
    ll i;
    ll ans = INF, maxIdx = (1<<P)-1;
    for(i=0;i<P;i++) {
        ans = min(ans,DP[i][maxIdx]+endDist[i]);
    }
    cout << (ans==INF ? -1 : ans) << '\n';
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
