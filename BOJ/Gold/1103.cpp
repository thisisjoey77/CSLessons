#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1103: 게임
//난이도: 골드2

const ll mx = 51;
const ll dy[4] = {0,1,0,-1}, dx[4]={1,0,-1,0};
ll N, M;
ll i, j, k;
ll A[mx][mx], DP[mx][mx];
ll ans=0;
bool vis[mx][mx]={0,};
bool infinite = false;
queue<pii> Q;
string txt;

bool outside(ll y, ll x) {
	return (y<0 || y>=N || x<0 || x>=M);
}

void dfs(ll y, ll x, ll turns) {
	if(outside(y,x) || A[y][x]=='H') {
		ans = max(ans,turns);
		return;
	}
	if(vis[y][x]) {
		infinite = true;
		return;
	}
	if(DP[y][x]>=turns) return;
	vis[y][x]=true; DP[y][x] = turns;
	ll coin = A[y][x]-'0';
	for(ll j=0;j<4;j++) {
		ll ny=y+coin*dy[j], nx=x+coin*dx[j];
		dfs(ny,nx,turns+1);
	}
	vis[y][x] = false;
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
    	cin >> txt;
    	for(j=0;j<M;j++) {
    		A[i][j] = txt[j];
    	}
    }
    for(i=0;i<mx;i++) for(j=0;j<mx;j++) DP[i][j]=-1;
    dfs(0,0,0);
    cout << ((infinite) ? -1 : ans) << '\n';
    return 0;
}