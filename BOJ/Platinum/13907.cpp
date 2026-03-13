#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13907: 세금
//난이도: 플레4

const ll mx = 1001, nMx = 30001;
ll N, M, K, S, D;
ll i, j, k;
ll tax[nMx] = {0,};
ll dist[mx][mx];
//도로를 i만큼 쓸때 j까지 가는데 최단거리
priority_queue<pii,vector<pii>,greater<pii>> PQ[mx];
vector<pii> G[mx];

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            dist[i][j] = INF;
        }
    }
    return;
}

void input() {
    ll i, j, k;
    ll a, b, w;
    cin >> N >> M >> K >> S >> D;
    for(i=0;i<M;i++) {
        cin >> a >> b >> w;
        G[a].push_back(make_pair(b,w));
        G[b].push_back(make_pair(a,w));
    }
    for(i=1;i<=K;i++) {
        cin >> tax[i];
    }
    return;
}

void solve() {
    ll i, j;
    PQ[0].push(make_pair(S,0));

    for(i=0;i<=N;i++) {
        while(!PQ[i].empty()) {
            ll U = PQ[i].top().first, curCost = PQ[i].top().second;
            PQ[i].pop();
            if(dist[i][U]<curCost) continue;
            ll sz = G[U].size();
            for(j=0;j<sz;j++) {
                ll V = G[U][j].first, vCost = G[U][j].second;
                if(curCost+vCost<dist[i+1][V]) {
                    dist[i+1][V] = curCost+vCost;
                    PQ[i+1].push(make_pair(V,curCost+vCost));
                }
            }
        }
    }
    return;
}

void output() {
    ll i, j;
    ll ans, totTax=0;
    for(i=0;i<=K;i++) {
        ans = INF;
        totTax += tax[i];
        for(j=0;j<=N;j++) {
            ans = min(ans,dist[j][D]+totTax*j);
        }
        cout << ans << '\n';
    }
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
