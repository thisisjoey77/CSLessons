//BOJ 1517: 버블소트
//난이도: 플레 5

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll N;
ll i, j;
const ll mx = 500000;
vector<pair<ll,ll>> V;
ll segTree[mx<<2] = {0,};
ll ans = 0;

ll update(ll start, ll end, ll node, ll idx) {
    if(start==end) return segTree[node] = 1;
    ll mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx);
    else update(mid+1,end,node<<1|1,idx);
    return segTree[node] = segTree[node<<1|1] + segTree[node<<1];
}

ll findLess(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(end<lBound || rBound<start) return 0;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    return findLess(start,mid,node<<1,lBound, rBound) + findLess(mid+1,end,node<<1|1,lBound, rBound);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i].first;
        V[i].second = i;
    }
    sort(V.begin(),V.end());
    j = V.size();
    for(i=0;i<j;i++) {
        ll curIdx = V[i].second;
        ans += findLess(0,N-1,1,curIdx+1,N-1);
        update(0,N-1,1,curIdx);
    }
    cout << ans << '\n';
    return 0;
}
