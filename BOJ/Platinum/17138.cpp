#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17138: 습격자 초라기와 쿼리 (Easy)
//난이도: 플레1

struct C{
    ll bothEmpty, bothFull, rightEmpty, leftEmpty;
    bool isNull;
};

const ll mx = 250001;
ll N, Q, W;
ll i, j, k;
ll a, b;
ll A[mx];
C segTree[mx<<2];
C nullLeaf = {0,0,0,0,false};

C merging(C lower, C upper, ll start, ll end) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
    C ans = {
        lower.leftEmpty+upper.rightEmpty,
        lower.bothFull+upper.bothFull,
        lower.bothFull+upper.rightEmpty,
        lower.leftEmpty+upper.bothFull,
        false
    };
    ll mid = (start+end) >> 1;
    if(A[mid]+A[mid+1]<=W) {
        if(end-start>1) {
            ans.rightEmpty = min(ans.rightEmpty,lower.rightEmpty+upper.bothEmpty+1);
            ans.leftEmpty = min(ans.leftEmpty,upper.leftEmpty+lower.bothEmpty+1);
            ans.bothEmpty = min(ans.bothEmpty,lower.bothEmpty+upper.bothEmpty+1);
        }
        ans.bothFull = min(ans.bothFull,lower.rightEmpty+upper.leftEmpty+1);
    }
    return ans;
}

C init(ll start, ll end, ll node) {
    if(start==end) return segTree[node] = {0,1,0,0,false};
    ll mid = (start+end) >> 1;
    C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
    return segTree[node] = merging(lower, upper, start, end);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(rBound<start || end<lBound) return nullLeaf;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    C lower = search(start,mid,node<<1,lBound,rBound);
    C upper = search(mid+1,end,node<<1|1,lBound,rBound);
    return merging(lower, upper, start, end);
}

void update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) return;
    if(start==end) {
        segTree[node] = {0,1,0,0,false};
        return;
    }
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,idx,val);
    update(mid+1,end,node<<1|1,idx,val);
    segTree[node] = merging(segTree[node<<1], segTree[node<<1|1],start,end);
    return;
}

ll process() {
    ll ans = min({segTree[1].bothFull,segTree[1].leftEmpty+1, segTree[1].rightEmpty+1});
    if(A[0] + A[N-1] <= W) {
        ans = min(ans,segTree[1].bothEmpty+1);   
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> Q >> W;
    for(i=0;i<N;i++) {
        cin >> A[i];
    }
    init(0,N-1,1);
    cout << process() << '\n';
    for(i=0;i<Q;i++) {
        cin >> a >> b;
        a --; A[a] = b;
        update(0,N-1,1,a,b);
        cout << process() << '\n';
    }
    return 0;
}