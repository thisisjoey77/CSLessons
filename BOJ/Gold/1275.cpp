#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//BOJ 1275: 커피숍 2
//난이도: 골드 1

const ll mx = 100001;
ll N, Q;
ll i, j;
ll x, y, a, b;
ll from, to;
ll A[mx] = {0,};
ll segTree[mx<<2] = {0,};


ll init(ll start, ll end, ll node) {
  if(start==end) {
    return segTree[node] = A[start];
  }
  ll mid = (start+end) >> 1;
  return segTree[node] = init(start,mid,node*2) + init(mid+1,end,node*2+1);
}

ll sum(ll start, ll end, ll node, ll lBound, ll rBound) {
  if(end<lBound || rBound<start) {
    return 0;
  }
  if(lBound<=start && end<=rBound) {
    return segTree[node];
  }
  ll mid = (start+end) >> 1;
  return sum(start,mid,node*2,lBound,rBound) + sum(mid+1,end,node*2+1,lBound,rBound);
}

void update(ll start, ll end, ll node, ll val, ll idx) {
  if(end<idx || idx<start) {
    return;
  }
  segTree[node] += val;
  if(start==end) {
    return;
  }
  ll mid = (start+end) >> 1;
  update(start,mid,node*2,val,idx);
  update(mid+1,end,node*2+1,val,idx);
  return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    for(i=0;i<Q;i++) {
        cin >> x >> y >> a >> b;
        from = min(x,y); to = max(x,y);
        from--; to--;
        cout << sum(0,N-1,1,from,to) << '\n';
        
        a --;
        update(0,N-1,1,b-A[a],a);
        A[a] = b;
    }
}
