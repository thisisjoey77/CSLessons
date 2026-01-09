#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2169: 로봇 조종하기
//난이도: 골드2

const ll mx = 1002;
ll N, M;
ll i, j, k;
ll aboveDP;
ll A[mx][mx];
pii DP[mx][mx];
pii nullPair = make_pair(LLONG_MIN, LLONG_MIN);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            DP[i][j] = nullPair;
        }
    }
    cin >> N >> M;
    for(i=1;i<=N;i++) {
    	for(j=1;j<=M;j++) {
    		cin >> A[i][j];
    	}
    }
    DP[1][1] = make_pair(A[1][1],A[1][1]);
    for(j=2;j<=M;j++) DP[1][j].first = DP[1][j].second = DP[1][j-1].first+A[1][j];
    for(i=2;i<=N;i++) {
    	//traverse left
    	for(j=1;j<=M;j++) {
    		aboveDP = max(DP[i-1][j].first, DP[i-1][j].second);
    		DP[i][j].first = max(aboveDP,DP[i][j-1].first) + A[i][j];
    	}
    	//traverse right
    	for(j=M;j>=1;j--) {
    		aboveDP = max(DP[i-1][j].first, DP[i-1][j].second);
    		DP[i][j].second = max(aboveDP,DP[i][j+1].second) + A[i][j];
    	}
    }
    cout << max(DP[N][M].first, DP[N][M].second) << '\n';
    return 0;
}