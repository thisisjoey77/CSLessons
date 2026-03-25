#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 24617: Redistributing Gifts
//난이도: 플레4

const ll mx = 501;
ll N;
ll dist[mx][mx], pref[mx][mx];
ll ans[mx];

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
    ll i, j;
    cin >> N;
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            cin >> pref[i][j];
        }
    }
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            dist[i][pref[i][j]] = 0;
            if(pref[i][j]==i) break;
        }
    }
    return;
}

void solve() {
    ll i, j, k;
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            for(k=1;k<=N;k++) {
                dist[j][k] = min(dist[j][k], dist[j][i]+dist[i][k]);
            }
        }
    }
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            if(dist[i][pref[i][j]]+dist[pref[i][j]][i]<INF) {
                ans[i] = pref[i][j];
                break;
            }
        }
    }
    return;
}

void output() {
    ll i;
    for(i=1;i<=N;i++) {
        cout << ans[i] << '\n';
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
