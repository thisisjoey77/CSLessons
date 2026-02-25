#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1162: 도로포장
//난이도: 플레5

const ll mx = 10001, rdMx = 50001, kmx = 21;
ll N, M, K;
ll i, j, k;
ll ans = INF;
ll dist[kmx][mx];
priority_queue<pii,vector<pii>,greater<pii>> PQ[kmx];
vector<pii> G[mx];

void init() {
    for(i=0;i<kmx;i++) {
        for(j=0;j<mx;j++) {
            dist[i][j] = INF;
        }
        dist[i][1] = 0;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    init();
    ll from, to, cost;
    for(i=0;i<M;i++) {
        cin >> from >> to >> cost;
        G[from].push_back(make_pair(to,cost));
        G[to].push_back(make_pair(from,cost));
    }
    PQ[0].push(make_pair(0,1));
    for(i=0;i<=K;i++) {
        while(!PQ[i].empty()) {
            ll curCost = PQ[i].top().first, U = PQ[i].top().second;
            PQ[i].pop();
            if(dist[i][U]<curCost) continue;
            ll sz = G[U].size();
            for(j=0;j<sz;j++) {
                ll V = G[U][j].first, cost = G[U][j].second;
                if(curCost+cost<dist[i][V]) {
                    dist[i][V] = curCost+cost;
                    PQ[i].push(make_pair(curCost+cost,V));
                }
                if(i<K && curCost<dist[i+1][V]) {
                    dist[i+1][V] = curCost;
                    PQ[i+1].push(make_pair(curCost,V));
                }
            }
        }
    }
    for(i=0;i<=K;i++) {
        ans = min(ans,dist[i][N]);
    }
    cout << ans << '\n';
    return 0;
}
