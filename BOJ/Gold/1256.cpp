#include <bits/stdc++.h>
#define ll long long int
#define INF 1000000000
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1256: 사전
//난이도: 골드2

const ll mx = 101;
ll N, M, K;
ll i, j, k;
ll sz;
ll DP[mx][mx] = {0,};
string ans = "";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    DP[0][0] = 1;
    for(i=0;i<=N;i++) {
    	for(j=0;j<=M;j++) {
    		if(i>0) DP[i][j] += DP[i-1][j];
    		if(j>0) DP[i][j] += DP[i][j-1];
    		if(DP[i][j]>INF) DP[i][j] = INF;
    	}
    }
    if(K<=DP[N][M]) {
    	ll aCnt=0, zCnt=0;
    	for(i=1;i<=(N+M);i++) {
    		if(aCnt==N || (aCnt<N && K>DP[N-aCnt-1][M-zCnt])) {
    			ans += 'z';
    			K -= DP[N-aCnt-1][M-zCnt];
    			zCnt ++;
    		}
    		else {
    			ans += 'a';
    			aCnt ++;
    		}
    	}
    }
    cout << ((ans.size()) ? ans : "-1") << '\n';
    return 0;
}