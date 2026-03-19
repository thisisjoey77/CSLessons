#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 34203: 통행료
//난이도: 플레2

struct C{
    ll ui, vi;
};

const ll mx = 501;
ll dist[mx][mx];
stack<ll> S;
ll N, M;
vector<C> V;

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    return;
}

void input() {
    ll i;
    cin >> N >> M;
    V.resize(M);
    for(i=0;i<M;i++) {
        cin >> V[i].ui >> V[i].vi;
        dist[V[i].ui][V[i].vi] = dist[V[i].vi][V[i].ui] = 1;
    }
    return;
}

void solve() {
    ll i, j, k;
    ll curAns=0, curU, curV;
    ll newDist, newDist2;
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            for(k=1;k<=N;k++) {
                dist[j][k] = min(dist[j][k],dist[j][i]+dist[i][k]);
            }
        }
    }
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            if(dist[i][j]!=INF) curAns += dist[i][j];
        }
    }
    S.push(curAns);
    for(i=M-1;i>0;i--) {
        curU = V[i].ui, curV = V[i].vi;
        if(!dist[curU][curV]) {
            S.push(curAns);
            continue;
        }
        for(j=1;j<=N;j++) {
            for(k=1;k<=N;k++) {
                newDist = dist[j][curU]+dist[curV][k];
                newDist2 = dist[j][curV]+dist[curU][k];
                dist[j][k] = min({dist[j][k],newDist,newDist2});
                curAns -= ((dist[k][j]-dist[j][k])<<1);
                dist[k][j] = dist[j][k];
            }
        }
        S.push(curAns);
    }
    return;
}

void output() {
    while(S.size()) {
        cout << S.top() << '\n';
        S.pop();
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
