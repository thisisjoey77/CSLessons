#include <bits/stdc++.h>
#define ll long long int
#define MOD 1000007
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1513: 경로 찾기
//난이도: 골드2

const ll mx = 51;
ll N, M, C;
ll i, j, k, a, b;
ll DP[mx][mx][mx][mx] = {0,};
ll A[mx][mx] = {0,};
ll y, x;

void integrate(ll y, ll x) {
	ll cur = A[y][x];
	bool insideY = y>1, insideX = x>1;
	if(!cur) {
		for(a=0;a<=C;a++) {
			for(ll b=0;b<=C;b++) {
				if(insideY) DP[y][x][a][b] += DP[y-1][x][a][b]%MOD;
				if(insideX) DP[y][x][a][b] += DP[y][x-1][a][b]%MOD;
				DP[y][x][a][b] %= MOD;
			}
		}
	}
	else {
		for(a=0;a<cur;a++) {
			for(ll b=0;b<cur;b++) {
				if(insideY) DP[y][x][cur][a+1] += DP[y-1][x][b][a]%MOD;
				if(insideX) DP[y][x][cur][a+1] += DP[y][x-1][b][a]%MOD;
				DP[y][x][cur][a+1]%=MOD;
			}
		}
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> C;
    for(i=1;i<=C;i++) {
    	cin >> y >> x;
    	A[y][x] = i;
    }
    if(!A[1][1]) DP[1][1][0][0] = 1;
    else DP[1][1][A[1][1]][1] = 1;
    for(i=1;i<=N;i++) {
    	for(j=1;j<=M;j++) {
    		integrate(i,j);
    	}
    }
    for(i=0;i<=C;i++) {
    	ll curAns = 0;
    	for(j=0;j<=C;j++) {
    		curAns = (curAns+DP[N][M][j][i])%MOD;
    	}
    	cout << curAns << ' ';
    }
    cout << '\n';
    return 0;
}