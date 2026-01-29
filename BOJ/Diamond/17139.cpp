#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17139: 습격자 초라기와 쿼리 (Normal)
//난이도: 다이아4

struct C{
    ll minVal[4][4]; //왼쪽 1-n, n+1-2n, 오른쪽
    bool isNull;
};

const ll mx = 500001, nMx = 250001;
ll N, Q, W;
ll i, j, k;
ll A[mx];
ll a, b;
C segTree[nMx<<2];
C nullLeaf={{0,},true}, defLeaf={{0,},false};

C merging(const C &lower, const C &upper, ll start, ll end) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
    C ans = defLeaf;
    ll mid = (start+end) >> 1;
    bool upCan = (A[mid]+A[mid+1]<=W), lowCan = (A[N+mid]+A[N+mid+1]<=W);
    for(ll l=0;l<4;l++) {
        for(ll r=0;r<4;r++) {
            ans.minVal[l][r] = lower.minVal[l][3] + upper.minVal[3][r];
            if(upCan) ans.minVal[l][r] = min(ans.minVal[l][r], lower.minVal[l][1]+upper.minVal[1][r]+1);
            if(lowCan) ans.minVal[l][r] = min(ans.minVal[l][r], lower.minVal[l][2]+upper.minVal[2][r]+1);
            if(lowCan && upCan) ans.minVal[l][r] = min(ans.minVal[l][r], lower.minVal[l][0]+upper.minVal[0][r]+2);
        }
    }
    return ans;
}

void setIndi(ll idx, ll node) {
    segTree[node] = defLeaf;
    bool canAdd = (A[idx]+A[N+idx]<=W);
    for(ll l=0;l<4;l++) {
        for(ll r=0;r<4;r++) {
            if(!(l|r) || ((l&r)==3)) continue;
            segTree[node].minVal[l][r] = (l&r) ? 1 : 0;
        }
    }
    segTree[node].minVal[3][3] = (canAdd) ? 1:2;
    return;
}

C init(ll start, ll end, ll node) {
    if(start==end) {
        setIndi(start,node);
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    C lower = init(start,mid,node<<1), upper = init(mid+1,end,node<<1|1);
    return segTree[node] = merging(lower, upper, start, end);
}

void update(ll start, ll end, ll node, ll idx) {
    if(idx<start || end<idx) return;
    if(start==end) {
        setIndi(idx,node);
        return;
    }
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,idx); update(mid+1,end,node<<1|1,idx);
    segTree[node] = merging(segTree[node<<1], segTree[node<<1|1], start, end);
    return;
}

ll findBits(ll idx) {
    ll ans=0;
    while(idx) {
        ans += idx&1;
        idx >>= 1;
    }
    return ans;
}

ll process() {
    ll ans = segTree[1].minVal[3][3];
    for(ll l=0;l<4;l++) {
        for(ll r=0;r<4;r++) {
            ans = min(ans,segTree[1].minVal[l][r]+findBits(3^l)+findBits(3^r));
            ll cnt = 0;
            if((l&r)!=3) {
                if(!(l&1) && !(r&1)) {
                    cnt += (A[N+1]+A[N<<1]<=W) ? 1:2;
                }
                else if(!(l&1) || !(r&1)) cnt ++;
                if(!(l&2) && !(r&2)) {
                    cnt += (A[1]+A[N]<=W) ? 1:2;
                }
                else if(!(l&2) || !(r&2)) cnt ++;
            }
            ans = min(ans, segTree[1].minVal[l][r]+cnt);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> Q >> W;
    for(i=1;i<=(N<<1);i++) {
        cin >> A[i];
    }
    init(1,N,1);
    cout << process() << '\n';
    for(i=0;i<Q;i++) {
        cin >> a >> b;
        A[a] = b;
        if(a>N) a -= N;
        update(1,N,1,a);
        cout << process() << '\n';
    }
    return 0;
}