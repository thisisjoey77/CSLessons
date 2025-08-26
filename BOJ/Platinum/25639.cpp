#include <bits/stdc++.h>
#define ll long long int
#define MX (9999999999<<1)
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 25639: 수열과 최대 상승 쿼리
//난이도: 플레2

struct C{
    ll minVal, maxVal, maxDiff;
};

const ll mx = 100001;
ll N, Q;
ll i, j, k, x, l, r;
ll A[mx];
ll order;
C segTree[mx<<2];

C init(ll start, ll end, ll node) {
    if(start==end) {
        if(start<N) return segTree[node] = {A[start],A[end],0};
        return segTree[node] = {MX,-MX,0};
    }
    ll mid = (start+end) >> 1;
    C lower = init(start,mid,node<<1);
    C upper = init(mid+1,end,node<<1|1);
    return segTree[node] = {min(lower.minVal,upper.minVal),
                            max(upper.maxVal, lower.maxVal),
                            max({lower.maxDiff,upper.maxDiff,upper.maxVal-lower.minVal})};
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(rBound<start || end<lBound) return {MX,-MX,0};
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    C lower = search(start,mid,node<<1,lBound,rBound);
    C upper = search(mid+1,end,node<<1|1,lBound,rBound);
    return {min(lower.minVal,upper.minVal),
            max(upper.maxVal, lower.maxVal),
            max({lower.maxDiff,upper.maxDiff,upper.maxVal-lower.minVal})};
}

void update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] = {val,val,0};
        return;
    }
    ll mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx,val);
    else update(mid+1,end,node<<1|1,idx,val);
    C lower = segTree[node<<1];
    C upper = segTree[node<<1|1];
    segTree[node] = {min(lower.minVal,upper.minVal),
                     max(upper.maxVal, lower.maxVal),
                     max({lower.maxDiff,upper.maxDiff,upper.maxVal-lower.minVal})};
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    cin >> Q;
    for(i=0;i<Q;i++) {
        cin >> order;
        if(order==1) {
            cin >> k >> x;
            k --;
            update(0,N-1,1,k,x);
        }
        else {
            cin >> l >> r;
            l --; r --;
            C result =search(0,N-1,1,l,r);
            cout << result.maxDiff << '\n';
        }
    }
    return 0;
}
