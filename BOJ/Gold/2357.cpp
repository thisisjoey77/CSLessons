#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//BOJ 2357: 최솟값과 최댓값
//난이도: 골드 1

const ll mx = 100000;
const ll segMin = LLONG_MIN, segMax = LLONG_MAX;
ll N, M;
ll i, j;
ll a, b;
ll A[mx] = {0,}, segTreeMin[mx<<2] = {0,}, segTreeMax[mx<<2] {0,};

//type 0 = minimum, type 1 = maximum
ll init(ll start, ll end, ll node, bool type) {
    //type 0 = minimum
    if(!type) {
        if(start==end) return segTreeMin[node] = A[start];
        ll mid = (start+end) >> 1;
        return segTreeMin[node] = min(
            init(start,mid,node<<1,type),
            init(mid+1,end,node<<1|1,type)
        );
    }
    if(start==end) return segTreeMax[node] = A[start];
    ll mid = (start+end) >> 1;
    return segTreeMax[node] = max(
        init(start,mid,node<<1,type),
        init(mid+1,end,node<<1|1,type)
    );
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound, bool type) {
    if(end<lBound || rBound<start) {
        if(!type) return LLONG_MAX;
        return LLONG_MIN;
    }
    if(lBound<=start && end<=rBound) {
        if(!type) return segTreeMin[node];
        return segTreeMax[node];
    }
    ll mid = (start+end) >> 1;
    if(!type) {
        return min(
            search(start,mid,node<<1,lBound,rBound,type),
            search(mid+1,end,node<<1|1,lBound,rBound,type)
        );
    }
    return max(
        search(start,mid,node<<1,lBound,rBound,type),
        search(mid+1,end,node<<1|1,lBound,rBound,type)
    );
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1,0); init(0,N-1,1,1);
    for(i=0;i<M;i++) {
        cin >> a >> b;
        --a; --b;
        cout << search(0,N-1,1,a,b,0) << ' ' << search(0,N-1,1,a,b,1) << '\n';
    }
    return 0;
}
