#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2336: 굉장한 학생
//난이도: 플레2

struct C{
    ll first, second, third;
};

const ll mx = 500001;
ll N;
ll i, j, k;
ll num;
ll segTree[mx<<2] = {0,};
ll minVal;
ll ans=0;
vector<C> V;
C cur;

bool sorter(C c1, C c2) {
    return c1.third < c2.third;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(rBound<start || end<lBound) return LLONG_MAX;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    return min(
        search(start,mid,node<<1,lBound,rBound),
        search(mid+1,end,node<<1|1,lBound,rBound)
    );
}

void update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] = val;
        return;
    }
    ll mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx,val);
    else update(mid+1,end,node<<1|1,idx,val);
    segTree[node] = min(segTree[node<<1],segTree[node<<1|1]);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    V.resize(N);
    for(i=0;i<3;i++) {
        for(j=0;j<N;j++) {
            cin >> num;
            if(i==0) V[num-1].first=j;
            else if(i==1) V[num-1].second=j;
            else V[num-1].third=j;
        }
    }
    sort(V.begin(),V.end(),sorter);
    for(i=0;i<(mx<<2);i++) segTree[i] = LLONG_MAX;
    for(i=0;i<N;i++) {
        cur = V[i];
        minVal = search(0,N-1,1,0,cur.second-1);
        if(minVal>cur.first) {
            ans ++;
        }
        update(0,N-1,1,cur.second,cur.first);
    }
    cout << ans << '\n';
    return 0;
}
