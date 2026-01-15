#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000000000
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1562: 계단 수
//난이도: 골드1

const ll mx = 101, bitMx = (1<<10);
ll N;
ll i, j, k, a;
ll DP[mx][10][bitMx] = {0,}, isoBits[10];
ll ans = 0;

void init() {
	isoBits[0] = 1;
	for(i=1;i<10;i++) {
		isoBits[i] = isoBits[i-1] << 1;
		DP[1][i][isoBits[i]] = 1;
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    init();
    for(i=1;i<N;i++) {
    	for(j=0;j<10;j++) {
    		for(k=0;k<bitMx;k++) {
    			if(j+1<10) {
    				DP[i+1][j+1][isoBits[j+1]|k] += DP[i][j][k]%MOD;
    				DP[i+1][j+1][isoBits[j+1]|k] %= MOD;
    			}
    			if(j-1>=0) {
    				DP[i+1][j-1][isoBits[j-1]|k] += DP[i][j][k]%MOD;
    				DP[i+1][j-1][isoBits[j-1]|k] %= MOD;
    			}
    		}
    	}
    }
    for(i=0;i<10;i++) {
    	ans = (ans+DP[N][i][bitMx-1])%MOD;
    }
    cout << ans << '\n';
    return 0;
}