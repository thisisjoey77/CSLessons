#include <bits/stdc++.h>
#define ll long long int
#define INF 1e9
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2281: 데스노트
//난이도: 골드2

const ll mx = 1001;
ll N, M;
ll i, j, k;
ll DP[mx];
ll A[mx];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    DP[0] = 0;
    for(i=1;i<mx;i++) DP[i] = INF;
    cin >> N >> M;
    for(i=1;i<=N;i++) {
    	cin >> A[i];
    }
    ll curSum;
    for(i=1;i<=N;i++) {
    	j=i, curSum=A[j];
    	while(curSum<=M && j<=N) {
    		if(j!=N) DP[j] = min(DP[j],(M-curSum)*(M-curSum)+DP[i-1]);
    		else DP[j] = min(DP[j],DP[i-1]);
    		j++;
    		curSum += A[j]+1;
    	}
    }
    cout << DP[N] << '\n';
    return 0;
}