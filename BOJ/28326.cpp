//BOJ 28326: 요세푸스 문제 2
//난이도: 플레2

#include <bits/stdc++.h>
#define ll long long int
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<ll,ll> pii;

const ll mx = 250000;
ll N, M;
ll i, j;
ll meats[mx][3];
ll from, to;
ll ans[mx] = {0,};
vector<pii> A;
pii segTree[mx<<4];

pii makeSeg(ll start, ll end, ll node) {
    if(start==end) return segTree[node] = make_pair(A[start].second,1);
    ll mid = (start+end) >> 1;
    pii lower = makeSeg(start,mid,node<<1);
    pii upper = makeSeg(mid+1,end,node<<1|1);
    if(lower.first==upper.first) return segTree[node] = make_pair(lower.first,2);
    if(lower.first<upper.first) return segTree[node] = lower;
    return segTree[node] = upper;
}

pii getSeg(ll start, ll end, ll node, ll mStart, ll mEnd) {
    if(mEnd<=A[start].first || A[end].first<mStart) return make_pair(INF,0);
    if(mStart<=A[start].first && A[end].first<mEnd) return segTree[node];
    ll mid = (start+end) >> 1;
    pii lower = getSeg(start,mid,node<<1,mStart,mEnd);
    pii upper = getSeg(mid+1,end,node<<1|1,mStart,mEnd);
    if(lower.first==upper.first) return make_pair(lower.first,2);
    if(lower.first<upper.first) return lower;
    return upper;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<N;i++) {
        for(j=0;j<3;j++) {
            cin >> meats[i][j];
        }
    }
    for(i=0;i<M;i++) {
        cin >> from >> to;
        A.push_back(make_pair(from,i));
        A.push_back(make_pair(to,i));
    }
    sort(A.begin(),A.end());
    makeSeg(0,(M<<1)-1,1);
    for(i=0;i<N;i++) {
        pii cur = getSeg(0,(M<<1)-1,1,meats[i][0],meats[i][1]);
        if(cur.second==2 && cur.first!=INF) {
            ans[cur.first] += meats[i][2];
        }
    }
    for(i=0;i<M;i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
