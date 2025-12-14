#include <bits/stdc++.h>
#define ll long long int
#define INF 987654321
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1400: 화물차
//난이도: 골드1

struct bridge{
	char initial;
	ll idx, h, v;
};

const ll mx = 441;
ll N, M;
ll i, j, k;
ll nIdx, aIdx, bIdx;
ll rSz, vSz, sz;
ll ans;
ll dist[mx], roadIdx[10];
vector<bridge> V;
priority_queue<pii,vector<pii>,greater<pii>> PQ;
char A[mx];
string txt;

void reset() {
	rSz=0; ans=INF; sz=N*M;
	for(i=0;i<mx;i++) dist[i] = INF;
	V.clear();
	PQ = {};
}

void process(ll idx, ll x, ll U) {
	if(A[idx]=='.') return;
	ll totTime = 1;
	if(A[idx]>='0' && A[idx]<='9') {
        bridge cur = V[roadIdx[A[idx]-'0']];
		ll T = cur.h+cur.v, curTime = (x)%T;
		if(abs(U-idx)==N) {
			if(cur.initial=='|' && curTime>=cur.v) totTime += T-curTime;
			else if(cur.initial=='-' && curTime<=cur.h) totTime += cur.h-curTime;
		}
		else {
			if(cur.initial=='|' && curTime<=cur.v) totTime += cur.v-curTime;
			else if(cur.initial=='-' && curTime>=cur.h) totTime += T-curTime;
		}
	}
	if(x+totTime<dist[idx]) {
		dist[idx] = x+totTime;
		PQ.push(make_pair(x+totTime,idx));
	}
	return;
}

void dijkstra() {
	dist[aIdx] = 0;
	PQ.push(make_pair(0,aIdx));
	while(!PQ.empty()) {
		ll x = PQ.top().first, U = PQ.top().second;
		if(A[U]=='B') {
			ans = x;
			return;
		}
		PQ.pop();
		if(x>dist[U]) continue;
		if(U%N!=1) process(U-1,x,U);
		if(U%N) process(U+1,x,U);
		if(U+N<=sz) process(U+N,x,U);
		if(U-N>=1) process(U-N,x,U);
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while(1) {
    	cin >> M >> N;
    	if(!(M||N)) break;
    	reset();
    	for(i=0;i<M;i++) {
    		cin >> txt;
    		for(j=0;j<N;j++) {
    			nIdx = N*i+j+1;
    			A[nIdx] = txt[j];
    			if(A[nIdx]=='A') aIdx = nIdx;
    			else if(A[nIdx]=='B') bIdx = nIdx;
    			else if(A[nIdx]>='0' && A[nIdx]<='9') rSz ++;
    		}
    	}
    	V.resize(rSz);
    	for(i=0;i<rSz;i++) {
    		cin >> V[i].idx >> V[i].initial >> V[i].h >> V[i].v;
    		roadIdx[V[i].idx] = i;
    	}
    	dijkstra();
    	if(ans==INF) cout << "impossible\n";
    	else cout << ans << '\n';
    }
    return 0;
}