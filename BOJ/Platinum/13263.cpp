#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13263: 나무 자르기
//난이도: 플레2

struct C{
	ll a, b; double s;
};

const ll mx = 100001;
ll N;
ll i, j, k, X, pos;
ll A[mx], B[mx], DP[mx];
vector<C> V;
C cur;

double cross(C f, C g) {
	return (g.b-f.b)/(f.a-g.a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    for(i=0;i<N;i++) {
    	cin >> B[i];
    }
    for(i=1;i<N;i++) {
    	cur = {B[i-1], DP[i-1],0};
    	while(!V.empty()) {
    		cur.s = cross(cur,V.back());
    		if(cur.s>=V.back().s) break;
    		V.pop_back();
    	}
    	V.push_back(cur);
    	X = A[i], pos=0;
    	ll left=0, right = V.size()-1;
    	while(left<=right) {
    		ll mid = (left+right) >> 1;
    		if(V[mid].s<X) {
    			pos = mid;
    			left = mid+1;
    		}
    		else right = mid-1;
    	}
    	DP[i] = V[pos].a*X + V[pos].b;
    }
    cout << DP[N-1] << '\n';
    return 0;
}
