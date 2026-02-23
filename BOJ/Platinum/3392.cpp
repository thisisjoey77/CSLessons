#include <bits/stdc++.h>
#define ll long long int
#define INF 999999999
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 3392: 화성지도
//난이도: 플레2

struct C{
	ll yFrom, yTo, x, adding;
};

struct D{
	ll cover;
	ll len;
};

const ll mx = 60005;
ll N;
ll i, j, k;
ll xFrom, yFrom, xTo, yTo;
ll area = 0;
vector<C> V;
vector<ll> yCoords;
D segTree[mx<<2];

bool sorter(C a, C b) {
	return a.x < b.x;
}

void pull(ll node, ll l, ll r, vector<ll>& yCoords) {
	if(segTree[node].cover > 0) {
		segTree[node].len = yCoords[r] - yCoords[l];
	}
	else if(l+1==r) {
		segTree[node].len = 0;
	}
	else {
		segTree[node].len = segTree[node<<1].len + segTree[node<<1|1].len;
	}
}

void update(ll node, ll l, ll r, ll ql, ll qr, ll val, vector<ll>& yCoords) {
	if(qr <= l || r <= ql) return;
	if(ql <= l && r <= qr) {
		segTree[node].cover += val;
		pull(node, l, r, yCoords);
		return;
	}
	ll mid = (l + r) >> 1;
	update(node<<1, l, mid, ql, qr, val, yCoords);
	update(node<<1|1, mid, r, ql, qr, val, yCoords);
	pull(node, l, r, yCoords);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for(i=0;i<N;i++) {
		cin >> xFrom >> yFrom >> xTo >> yTo;
		if(xFrom > xTo) swap(xFrom, xTo);
		if(yFrom > yTo) swap(yFrom, yTo);
		V.push_back({yFrom, yTo, xFrom, 1});
		V.push_back({yFrom, yTo, xTo, -1});
		yCoords.push_back(yFrom);
		yCoords.push_back(yTo);
	}

	sort(V.begin(), V.end(), sorter);
	sort(yCoords.begin(), yCoords.end());
	yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());
	ll ySize = yCoords.size();
	ll prevX = V[0].x;
	
	for(i=0;i<(N<<1);i++) {
		C cur = V[i];
		ll curX = cur.x;
		if(i) {
			ll width = curX - prevX;
			area += segTree[1].len * width;
		}
		ll y1 = lower_bound(yCoords.begin(), yCoords.end(), cur.yFrom) - yCoords.begin();
		ll y2 = lower_bound(yCoords.begin(), yCoords.end(), cur.yTo) - yCoords.begin();
		update(1, 0, ySize-1, y1, y2, cur.adding, yCoords);
		prevX = curX;
	}
	cout << area << '\n';
	return 0;
}
