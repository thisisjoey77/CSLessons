#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2718: 타일 채우기
//난이도: 골드1

const ll mx = 25, nMx = 1<<4;
ll N, T;
ll i, j, k;
ll DP[mx][nMx] = {0,};

void init() {
    DP[1][nMx-1] = 1;
    DP[2][nMx-1] = 1;
    DP[2][9] = 1;
    DP[2][12] = 1;
    DP[2][3] = 1;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    for(i=1;i<mx-1;i++) {
        DP[i][nMx-1] += DP[i][0] + DP[i][12] + DP[i][3] + DP[i][9];
        DP[i+1][9] += DP[i][6] + DP[i][0];
        DP[i+1][6] += DP[i][9];
        DP[i+1][3] += DP[i][12] + DP[i][0];
        DP[i+1][12] += DP[i][3] + DP[i][0];
        DP[i+1][0] += DP[i][nMx-1];
        DP[i+1][nMx-1] += DP[i][0];
    }
    cin >> T;
    while(T--) {
        cin >> N;
        cout << DP[N][nMx-1] << '\n';
    }
    return 0;
}