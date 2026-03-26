#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 14939: 불 끄기
//난이도: 플레4

const ll mx = 10, nMx = 1<<10;
ll N;
ll DP[mx][nMx][nMx];
ll turns[nMx], target[nMx], init[mx];
string S[mx];

ll numBits(ll idx) {
    ll ans = 0;
    while(idx) {
        ans += idx&1;
        idx >>= 1;
    }
    return ans;
}

void testSwitch(ll idx) {
    ll i=9,j;
    ll from, to, tIdx;
    string ans = "0000000000";
    tIdx = idx;
    while(i>=0) {
        if(tIdx&1) {
            from = max(0LL,i-1), to = min(9LL,i+1);
            for(j=from;j<=to;j++) {
                ans[j] = (ans[j]=='0') ? '1' : '0';
            }
        }
        tIdx >>= 1;
        i --;
    }
    ll switched = 0;
    for(j=0;j<10;j++) {
        switched <<= 1;
        if(ans[j]=='1') switched |= 1;
    }
    target[idx] = switched;
    return;
}

void start() {
    ll i, j, k;
    for(i=0;i<mx;i++) {
        for(j=0;j<nMx;j++) {
            for(k=0;k<nMx;k++) {
                DP[i][j][k] = INF;
            }
        }
    }
    for(i=0;i<nMx;i++) {
        turns[i] = numBits(i);
        testSwitch(i);
    }
    for(i=0;i<mx;i++) {
        init[i] = 0;
        string tempString = S[i];
        for(j=0;j<mx;j++) {
            init[i] <<= 1;
            if(S[i][j]=='O') init[i] |= 1;
        }
    }
    return;
}

void input() {
    ll i;
    for(i=0;i<10;i++) {
        cin >> S[i];
    }
    return;
}

void solve() {
    ll i, j, k;
    ll aIdx, bIdx;
    for(j=0;j<nMx;j++) {
        aIdx = target[j]^init[0], bIdx = init[1]^j;
        DP[1][aIdx][bIdx] = min(DP[1][aIdx][bIdx],turns[j]);
    }
    for(i=1;i<9;i++) {
        for(j=0;j<nMx;j++) {
            for(k=0;k<nMx;k++) {
                if(DP[i][j][k]==INF) continue;
                aIdx = k^target[j], bIdx = init[i+1]^j;
                DP[i+1][aIdx][bIdx] = min(DP[i+1][aIdx][bIdx],DP[i][j][k]+turns[j]);
            }
        }
    }
    for(j=0;j<nMx;j++) {
        DP[9][0][0] = min(DP[9][0][0],DP[9][j][target[j]]+turns[j]);
    }
    return;
}

void output() {
    cout << ((DP[9][0][0]==INF) ? -1 : DP[9][0][0]) << '\n';
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    input();
    start();
    solve();
    output();
    return 0;
}
