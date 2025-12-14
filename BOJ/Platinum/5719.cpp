#include <bits/stdc++.h>
#define ll long long int
#define INF 987654321
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 5719: 거의 최단 경로
//난이도: 플레5

const ll mx = 501;
ll N, M, S, D;
ll i, j, k;
ll vSz;
ll u, v, p;
ll dist[mx];
bool vis[mx][mx], tracked[mx];
vector<pii> G[mx];
vector<ll> inDeg[mx];
priority_queue<pii,vector<pii>,greater<pii>> PQ;
queue<ll> Q;

void reset(ll query) {
	for(i=0;i<mx;i++) {
		if(query) {
			G[i].clear();
			for(j=0;j<mx;j++) vis[i][j] = false;
		}
		tracked[i] = false;
		inDeg[i].clear();
		dist[i] = INF;
	}
	Q = {}; PQ = {};
	return;
}

void shortest(ll query) {
	dist[S] = 0;
	PQ.push(make_pair(0,S));
	while(!PQ.empty()) {
		ll x = PQ.top().first, U = PQ.top().second;
		PQ.pop();
		if(x>dist[U]) continue;
		vSz = G[U].size();
		for(j=0;j<vSz;j++) {
			ll V = G[U][j].first, W = G[U][j].second;
			if(x+W<dist[V] && !vis[U][V]) {
				if(query) {
					inDeg[V].clear();
					inDeg[V].push_back(U);
				}
				dist[V] = x+W;
				PQ.push(make_pair(x+W,V));
			}
			else if(x+W==dist[V] && query) inDeg[V].push_back(U);
		}
	}
	return;
}

void bfs() {
	Q.push(D); 
	tracked[D] = true;
	while(!Q.empty()) {
		ll cur = Q.front(); Q.pop();
		vSz = inDeg[cur].size();
		for(j=0;j<vSz;j++) {
			ll V = inDeg[cur][j];
			if(!tracked[V]) {
				Q.push(V);
				tracked[V] = true;
			}
			vis[V][cur] = true;
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while(1) {
    	cin >> N >> M;
    	if(!(N||M)) break;
    	cin >> S >> D;
    	reset(1);
    	for(i=0;i<M;i++) {
    		cin >> u >> v >> p;
    		G[u].push_back(make_pair(v,p));
    	}
    	shortest(1);
    	bfs();
    	reset(0); 
    	shortest(0);
    	cout << ((dist[D]==INF) ? -1:dist[D]) << '\n';
    }
    return 0;
}