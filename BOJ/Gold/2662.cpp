#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2662: 기업투자
//난이도: 골드2

const ll mx = 301, mMx=21;

struct C{
	ll val;
	ll amt[mMx];
};

ll N, M;
ll i, j, k, l;
C DP[mx];
ll reward[mMx][mx];
ll cost;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=1;i<=N;i++) {
    	cin >> cost;
    	for(j=0;j<M;j++) {
    		cin >> reward[j][i];
    	}
    }
    for(i=1;i<=N;i++) {
    	DP[i].val = reward[0][i];
    	DP[i].amt[0] = i;
    }
    for(i=1;i<M;i++) {
    	for(j=1;j<=N;j++) {
    		for(k=N;k>=0;k--) {
    			ll addVal = j-DP[k].amt[i];
    			if(k+addVal>N) continue;
    			ll rewardChange = reward[i][j]-reward[i][DP[k].amt[i]];
    			if(DP[k].val+rewardChange<=DP[k+addVal].val) continue;
    			DP[k+addVal].val = DP[k].val+rewardChange;
    			for(l=0;l<M;l++) {
    				if(l==i) DP[k+addVal].amt[l] = j;
    				else DP[k+addVal].amt[l] = DP[k].amt[l];
    			}
    		}
    	}
    }
    cout << DP[N].val << '\n';
    for(i=0;i<M;i++) cout << DP[N].amt[i] << ' ';
    cout << '\n';
    return 0;
}