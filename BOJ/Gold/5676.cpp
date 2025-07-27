#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 100001;
ll N, K;
ll A[mx] = {0,};
ll segTree[mx<<2] = {0,};
ll i, j;
char a;
ll b, c;
ll ans;

ll init(ll start, ll end, ll node) {
	if(start==end) {
		return segTree[node] = (A[start]);
	}
	ll mid = (start+end) >> 1;
	return segTree[node] = init(start,mid,node<<1) * init(mid+1,end,node<<1|1);
}

ll prod(ll start, ll end, ll node, ll lBound, ll rBound) {
	if(end<lBound || start>rBound) {
		return 1;
	}
	if(lBound<=start && end<=rBound) {
		return segTree[node];
	}
	ll mid = (start+end) >> 1;
	return prod(start,mid,node<<1,lBound,rBound) * prod(mid+1,end,node<<1|1,lBound,rBound);
}


ll update(ll start, ll end, ll node, ll idx, ll val) {
	if(idx<start || idx>end) {
		return segTree[node];
	}

	if(start==end) return segTree[node]=val;

	ll mid = (start+end) >> 1;
	ll lower = update(start,mid,node<<1,idx, val);
	ll upper = update(mid+1,end,node<<1|1,idx, val);
	return segTree[node] = upper*lower;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> N >> K) {
        memset(segTree,0,sizeof(segTree));
        memset(A,0,sizeof(A));
		for(i=0; i<N; i++) {
			cin >> A[i];
            if(!A[i]) A[i] = 0;
            else if(A[i]>0) A[i] = 1;
            else A[i] = -1;
		}
		init(0,N-1,1);
        
		for(i=0; i<K; i++) {
			cin >> a >> b >> c;
			b--;
			if(a=='C') {
				if(!c) c=0;
                else if(c>0) c=1;
                else c=-1;
				if(c!=A[b]) {
					update(0,N-1,1,b,c);
					A[b] = c;
				}
			}
			else {
				c--;
				ans =prod(0,N-1,1,b,c);
				if(!ans) {
					cout << 0;
				}
				else if(ans>0) {
					cout << "+";
				}
				else {
					cout << "-";
				}
			}
		}
		cout << '\n';
	}
}
