#include <bits/stdc++.h>
#define ll long long int
#define INF 987654321
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2423: 전구를 켜라
//난이도: 골드1

const ll mx = 501;
ll N, M;
ll i, j, k;
string txt;
char A[mx][mx];
ll dist[mx][mx];
deque<pii> dq;

void process(ll fromX, ll fromY, ll toX, ll toY) {
	ll aX = min(fromX,toX), aY = min(fromY,toY);
	ll cost=1, dy=toY-fromY, dx=toX-fromX;
	if(dx==dy && A[aY][aX]=='\\') cost = 0;
	if(dx!=dy && A[aY][aX]=='/')  cost = 0;
	if(dist[toY][toX]>dist[fromY][fromX]+cost) {
		if(cost) dq.push_back(make_pair(toX,toY));
		else dq.push_front(make_pair(toX,toY));
		dist[toY][toX] = dist[fromY][fromX]+cost;
	}
	return;
}

void zeroOneBfs() {
	dist[0][0] = 0;
	dq.push_back(make_pair(0,0));
	while(!dq.empty()) {
		ll curX = dq.front().first, curY = dq.front().second;
		dq.pop_front();
		if(curY==N && curX==M) return;
		if(curX && curY) process(curX,curY,curX-1,curY-1);
		if(curX && curY+1<=N) process(curX,curY,curX-1,curY+1);
		if(curX+1<=M && curY) process(curX,curY,curX+1,curY-1);
		if(curX+1<=M && curY+1<=N) process(curX,curY,curX+1,curY+1);
	}
	return;
}

void reset() {
	for(i=0;i<mx;i++) {
		for(j=0;j<mx;j++) {
			dist[i][j] = INF;
		}
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    reset();
    for(i=0;i<N;i++) {
    	cin >> txt;
    	for(j=0;j<M;j++) {
    		A[i][j] = txt[j];
    	}
    }
    zeroOneBfs();
    if(dist[N][M]==INF) cout << "NO SOLUTION\n";
    else cout << dist[N][M] << '\n';
    return 0;
}