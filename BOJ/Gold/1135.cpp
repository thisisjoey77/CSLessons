#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1135: 뉴스 전하기
//난이도: 골드2

const ll mx = 51;
ll N;
ll i, j, k;
ll A[mx];
vector<ll> G[mx];

bool sorter(ll a, ll b) {
	return a>b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> A[0];
    for(i=1;i<N;i++) {
    	cin >> A[i];
    }
    for(i=N-1;i>=0;i--) {
    	sort(G[i].begin(),G[i].end(),sorter);
    	ll sz = G[i].size(), curCost=0;
    	for(j=0;j<sz;j++) {
    		curCost = max(curCost,G[i][j]+j);
    	}
    	if(i==0) {
    		cout << curCost << '\n';
    		break;
    	}
    	G[A[i]].push_back(curCost+1);
    }
    return 0;
}