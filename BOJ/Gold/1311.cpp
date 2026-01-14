#include <bits/stdc++.h>
#define ll long long int
#define INF 1e9
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1311: 할 일 정하기 1
//난이도: 골드1

struct C{
	ll idx, numBits;
};

const ll mx = (1<<21)|1, nMx = 21;
ll N;
ll i, j, k;
ll sz;
ll DP[mx], isoBits[nMx], costs[nMx][nMx];
vector<C> V;
C cur;

bool sorter(C c1, C c2) {
	return c1.numBits < c2.numBits;
}

ll findBits(ll idx) {
	ll ans = 0;
	while(idx) {
		ans += idx&1;
		idx >>= 1;
	}
	return ans;
}

void init() {
	for(i=0;i<mx;i++) {
		DP[i] = INF;
	}
	sz = (1<<N)-1;
	for(i=1;i<sz;i++) {
		V.push_back({i,findBits(i)});
	}
	isoBits[1] = 1;
	for(i=2;i<nMx;i++) {
		isoBits[i] = isoBits[i-1] << 1;
	}
	sort(V.begin(),V.end(),sorter);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    init();
    for(i=1;i<=N;i++) {
    	for(j=1;j<=N;j++) {
    		cin >> costs[i][j];
    	}
    }
    ll idx = 1;
    for(i=1;i<=N;i++) {
    	DP[idx] = costs[1][i];
    	idx<<= 1;
    }
    ll nIdx;
    for(i=0;i<(sz-1);i++) {
    	cur = V[i];
    	for(j=1;j<=N;j++) {
    		if(isoBits[j]&cur.idx) continue;
    		nIdx = isoBits[j] | cur.idx;
    		DP[nIdx] = min(DP[nIdx],DP[cur.idx]+costs[cur.numBits+1][j]);
    	}
    }
    cout << DP[sz] << '\n';
    return 0;
}