#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//BOJ 11505: 구간 곱 구하기
//난이도: 골드 1

const ll mx = 1000000, dv = 1000000007;
ll A[mx] = {0,}, segTree[mx*6] = {0,};
ll N, M, K;
ll i;
ll a, b, c;

ll init(ll start, ll end, ll node) {
    if(start==end) 
        return segTree[node] = A[start];
    ll mid = (start+end) /2;
    return segTree[node] = ((init(start,mid,node*2)) * (init(mid+1,end,node*2+1)))%dv;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(end<lBound || rBound<start) 
        return 1;
    if(lBound<=start && end<=rBound) 
        return segTree[node];
    
    ll mid = (start+end) /2;
    return ((search(start,mid,node*2,lBound,rBound)) * (search(mid+1,end,node*2+1,lBound,rBound)))%dv;
}

ll update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) 
        return segTree[node];
    if(start==end) 
        return segTree[node] = val;
    ll mid = (start+end) / 2;
    return segTree[node] = ((update(start,mid,node*2,idx,val)) * (update(mid+1,end,node*2+1,idx,val)))%dv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<(M+K);i++) {
        cin >> a >> b >> c;
        --b;
        if(a==1) {
            update(0,N-1,1,b,c);
        }
        else {
            -- c;
            cout << search(0,N-1,1,b,c) << '\n';
        }
    }
    return 0;
}
