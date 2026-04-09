#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 2449: 전구
//난이도: 플레4

const ll mx = 201;
ll N, K;
ll A[mx];
ll DP[mx][mx];

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            DP[i][j] = INF;
        }
        DP[i][i] = 0;
    }
    return;
}

void input() {
    ll i;
    cin >> N >> K;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
}

void solve() {
    ll i, j, k;
    for(k=1;k<N;k++) {
        for(i=0;i+k<N;i++) {
            ll s=i, e=i+k;
            for(j=s;j<e;j++) {
                DP[s][e] = min(DP[s][e],DP[s][j]+DP[j+1][e]+(A[s]!=A[j+1] ? 1:0));
            }
        }
    }
    return;
}

void output() {
    cout << DP[0][N-1] << '\n';
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
