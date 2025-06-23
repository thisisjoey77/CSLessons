//BOJ 14245: XOR
//난이도: 플레 4

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 500001;
ll segTree[mx<<2] = {0,};
ll lazy[mx<<2] = {0,};
ll A[mx] = {0,};
ll N, M;
ll i;
ll type;
ll from, to, target;

ll init(ll start, ll end, ll node) {
  if(start==end) return segTree[node] = A[start];
  ll mid = (start+end) >> 1;
  init(start,mid,node<<1);
  init(mid+1,end,node<<1|1);
  return 0;
}

void updateLazy(ll start, ll end, ll node) {
    if(lazy[node]) {
        segTree[node] ^= lazy[node];
        if(start!=end) {
            lazy[node<<1] ^= lazy[node];
            lazy[node<<1|1] ^= lazy[node];
        }
        lazy[node] = 0;
    }
    return;
}

void updateRange(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
    updateLazy(start,end,node);
    if(rBound<start || end<lBound) return;
    if(lBound<=start && end<=rBound) {
        segTree[node] ^= val;
        if(start!=end) {
            lazy[node<<1] ^= val;
            lazy[node<<1|1] ^= val;
        }
        return;
    }
    ll mid = (start+end) >> 1;
    updateRange(start,mid,node<<1,lBound,rBound,val);
    updateRange(mid+1,end,node<<1|1,lBound,rBound,val);
    //
    return;
}

ll search(ll start, ll end, ll node, ll idx) {
    updateLazy(start,end,node);
    if(idx<start || end<idx) return 0;
    if(idx<=start && end<=idx) return segTree[node];
    ll mid = (start+end) >> 1;
    return search(start,mid,node<<1,idx) ^ search(mid+1,end,node<<1|1,idx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    cin >> M;
    for(i=0;i<M;i++) {
        cin >> type;
        if(type==1) {
            cin >> from >> to >> target;
            updateRange(0,N-1,1,from,to,target);
        }
        else {
            cin >> target;
            cout << search(0,N-1,1,target) << '\n';
        }
    }
    return 0;
}
