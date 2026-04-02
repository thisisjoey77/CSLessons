#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 10803: 정사각형 만들기
//난이도: 플레2

const ll mx = 10001, nMx = 101;
ll N, M;
ll DP[mx][nMx] = {0,};

void init() {
    ll i, j;
    for(i=1;i<mx;i++) {
        for(j=1;j<nMx;j++) {
            DP[i][j] = INF;
        }
    }
    return;
}

void input() {
    cin >> N >> M;
    return;
}

void solve() {
    ll i, j, k;
    ll aIdx, bIdx, cIdx, dIdx;
    for(i=1;i<nMx;i++) {
        for(j=i;j<mx;j++) {
            for(k=1;k<i;k++) {
                aIdx = max(j-k,i), bIdx = min(j-k,i);
                DP[j][i] = min({DP[j][i],DP[j][k]+DP[j][i-k],DP[i][k]+DP[aIdx][bIdx]});
            }
            aIdx = max(j-i,i); bIdx = min(j-i,i);
            DP[j][i] = min(DP[j][i],1+DP[aIdx][bIdx]);
            if(j>=3*i) continue;
            for(k=i+1;k<=(j>>1);k++) {
                aIdx = max(j-k,i), bIdx = min(j-k,i);
                cIdx = max(i,k), dIdx = min(i,k);
                DP[j][i] = min(DP[j][i],DP[cIdx][dIdx]+DP[aIdx][bIdx]);
            }
        }
    }
    return;
}

void output() {
    cout << DP[max(N,M)][min(N,M)] << '\n';
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
