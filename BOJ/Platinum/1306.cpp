#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//BOJ 1306: 달려라 홍준
//난이도: 플레 5

ll N, M;
const ll mx = 1000001;
ll A[mx] = {0,};
ll segTree[mx<<2] = {0,};
ll i, j;
ll lower, upper;

ll init(ll start, ll end, ll node) {
    if(start==end) return segTree[node] = A[start];
    ll mid = (start+end) >> 1;
    return segTree[node] = max(init(start,mid,node<<1),init(mid+1,end,node<<1|1));
}

ll query(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(end<lBound || rBound<start) {
        return 0;
    }
    if(lBound<=start && end<=rBound) {
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    return max(
        query(start,mid,node<<1,lBound,rBound),
        query(mid+1,end,node<<1|1,lBound,rBound)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    for(i=M-1;i<(N-M+1);i++) {
        lower = ((i-M+1)>=0) ? i-M+1 : 0;
        upper = ((i+M-1)<N) ? i+M-1 : N-1;
        cout << query(0,N-1,1,lower,upper) << ' ';
    }
    cout << '\n';
    return 0;
}
