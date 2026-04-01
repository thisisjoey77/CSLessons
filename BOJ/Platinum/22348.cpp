#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define MOD 1000000007
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 22348: 헬기 착륙장
//난이도: 플레4

const ll mx = 450, nMx = 50001;
ll N;
ll DP[mx][nMx], layerSum[mx];
vector<pii> V;

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<nMx;j++) {
            DP[i][j] = 0;
        }
    }
    layerSum[0] = 0;
    for(i=1;i<mx;i++) {
        layerSum[i] = layerSum[i-1] + i;
    }
    return;
}

void input() {
    ll i;
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i].first >> V[i].second;
    }
    return;
}

void solve() {
    ll i, j;
    DP[1][1] = DP[1][0] = 1;
    for(i=1;i<(mx-1);i++) {
        //case 1: next layer is blue
        for(j=0;j<nMx;j++) {
            DP[i+1][j] = DP[i][j]%MOD;
        }
        //case 2: next layer is red
        for(j=0;j<(nMx-(i+1));j++) {
            DP[i+1][j+i+1] = (DP[i+1][j+i+1] + DP[i][j])%MOD;
        }
        //prefix sumify
        for(j=1;j<nMx;j++) {
            DP[i][j] = (DP[i][j] + DP[i][j-1])%MOD;
        }
    }
    return;
}

void output() {
    ll i, j, nIdx;
    ll ans;
    for(i=0;i<N;i++) {
        j=1, ans = 0;
        while(layerSum[j]<=(V[i].first+V[i].second)) {
            nIdx = layerSum[j] - V[i].second - 1;
            ll val = DP[j][V[i].first];
            if(nIdx >= 0) {
                val = (val-DP[j][nIdx]+MOD)%MOD;
            }
            ans = (ans+val)%MOD;
            j++;
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
