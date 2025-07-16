#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//BOJ 10868: 최솟값
//난이도: 골드 1

const ll mx = 100000;
ll N, M;
ll i, j, k;
ll a, b;
ll A[mx] = {0,}, segTree[mx << 2] = {0,};

ll init(ll start, ll end, ll node) {
    if(start==end) {
        return segTree[node] = A[start];
    }
    ll mid = (start+end) >> 1;
    return segTree[node] = min(init(start,mid,node*2),init(mid+1,end,node*2+1));
}

ll minim(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(end < lBound || rBound < start) {
        return INT_MAX;
    }
    if(lBound <= start && end <= rBound) {
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    return min( {
        minim(start,mid,node*2,lBound,rBound),
        minim(mid+1,end,node*2+1,lBound,rBound)
        });
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<M;i++) {
        cin >> a >> b;
        --a; --b;
        cout << minim(0,N-1,1,a,b) << '\n';
    }
    return 0;
}
