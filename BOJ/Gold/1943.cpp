#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1943: 동전 분배
//난이도: 골드2

const ll mx = 101, nMx = 50001;
ll N, M, T=3;
ll i, j, k;
ll V[mx], amt[mx];
ll totSum;
bool DP[nMx], tempDP[nMx];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while(T--) {
    	memset(DP,false,sizeof(DP));
    	memset(tempDP,false,sizeof(tempDP));
    	DP[0] = true;
    	totSum = 0;
    	cin >> N;
    	for(i=1;i<=N;i++) {
    		cin >> V[i] >> amt[i];
    		totSum += V[i]*amt[i];
    	}
    	if(totSum&1) {
    		cout << "0\n";
    		continue;
    	}
    	M = totSum>>1;
    	for(i=1;i<=N;i++) {
    		memset(tempDP,false,sizeof(tempDP));
    		for(j=0;j<=M;j++) {
    			if(!DP[j]) continue;
    			ll usedCoins = 1, curVal=j+V[i];
    			while(usedCoins<=amt[i] && curVal<=M) {
    				tempDP[curVal] = true;
    				usedCoins ++; curVal += V[i];
    			}
    		}
    		for(j=0;j<=M;j++) {
    			DP[j] |= tempDP[j];
    		}
    	}
    	cout << ((DP[M]) ? 1:0) << '\n';
    }
    return 0;
}