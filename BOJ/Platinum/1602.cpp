#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1602: 도망자 원숭이
//난이도: 플레3

struct C{
    ll idx, delay;
};

const ll mx = 501;
ll N, M, Q;
vector<C> V;
ll dist[mx][mx], dp[mx][mx], delay[mx];

bool sorter(C c1, C c2) {
    return c1.delay < c2.delay;
}

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            dist[i][j] = dp[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    return;
}

void input() {
    ll i, a, b, d;
    cin >> N >> M >> Q;
    V.resize(N+1);
    for(i=1;i<=N;i++) {
        cin >> delay[i];
        V[i] = {i,delay[i]};
    }
    for(i=0;i<M;i++) {
        cin >> a >> b >> d;
        dist[a][b] = dist[b][a] = min(dist[a][b],d);
    }
    sort(V.begin()+1,V.end(),sorter);
    return;
}

void solve() {
    ll i, j, k;
    for(i=1;i<=N;i++) {
        ll via = V[i].idx;
        for(j=1;j<=N;j++) {
            for(k=1;k<=N;k++) {
                dist[j][k] = min(dist[j][k],dist[j][via]+dist[via][k]);
                ll maxDelay = max({delay[via],delay[j],delay[k]});
                dp[j][k] = min(dp[j][k],dist[j][via]+dist[via][k]+maxDelay);
            }
        }
    }
    return;
}

void output() {
    ll S, T;
    while(Q--) {
        cin >> S >> T;
        cout << ((dp[S][T]>=INF) ? -1 : dp[S][T]) << '\n';
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
