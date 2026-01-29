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
    for(ll y=0;y<4;y++) {
        for(ll x=0;x<4;x++) {
            ans.minVal[y][x] = lower.minVal[y][3] + upper.minVal[3][x];
            if(upCan) ans.minVal[y][x] = min(ans.minVal[y][x], lower.minVal[y][1]+upper.minVal[1][x]+1);
            if(lowCan) ans.minVal[y][x] = min(ans.minVal[y][x], lower.minVal[y][2]+upper.minVal[2][x]+1);
            if(lowCan && upCan) ans.minVal[y][x] = min(ans.minVal[y][x], lower.minVal[y][0]+upper.minVal[0][x]+2);
        }
    }
    return ans;
}

void setIndi(ll idx, ll node) {
    segTree[node] = defLeaf;
    bool canAdd = (A[idx]+A[N+idx]<=W);
    for(ll y=0;y<4;y++) {
        for(ll x=0;x<4;x++) {
            if((y==0 && x==0) || (y==3 && x==3)) continue;
            segTree[node].minVal[y][x] = ((y&x)) ? 1 : 0;
        }
    }
    segTree[node].minVal[3][3] = ((canAdd) ? 1:2);
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
    for(ll y=0;y<4;y++) {
        for(ll x=0;x<4;x++) {
            ans = min(ans,segTree[1].minVal[y][x]+findBits(3^y)+findBits(3^x));
            ll cnt = 0;
            if((y&x)!=3) {
                if(!(y&1) && !(x&1)) {
                    if(A[N+1]+A[N<<1]<=W) cnt ++;
                    else cnt += 2;
                }
                else if(!(y&1) || !(x&1)) cnt ++;

                if(!(y&2) && !(x&2)) {
                    if(A[1]+A[N]<=W) cnt ++;
                    else cnt += 2;
                }
                else if(!(y&2) || !(x&2)) cnt ++;

            }
            ans = min(ans, segTree[1].minVal[y][x]+cnt);
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