#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 17443: 여우 퀴즈
//난이도: 다이아4

struct C{
    ll maxVal, from, to;
    char leftEnd[4], rightEnd[4];
    bool isNull;
};

const ll mx = 250001;
ll N, A, B, Q;
ll i, j, k;
ll a, b, n;
string S, T;
char order;
C segTree[mx<<2];
C nullLeaf = {0,0,0,{'E','E','E','E'},{'E','E','E','E'},true};
C defLeaf = {0,0,0,{'E','E','E','E'},{'E','E','E','E'},false};

C merging(C lower, C upper, ll start, ll end) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
    C ans = defLeaf;

    ans.from = lower.from; ans.to = upper.to;
    ans.maxVal = lower.maxVal + upper.maxVal;
    ll mid = (start+end) >> 1;

    //case 1: FOFO XX
    if(T[mid]=='O' && T[mid+1]=='X' && (lower.to-lower.from+1>=2)) {
        ll profit = 0;
        if(lower.rightEnd[0]=='F') {
            profit -= B;
            if(T[mid-3]==S[mid-3]) profit += A;
        }
        if(upper.leftEnd[0]=='F') {
            profit -= B;
            if(T[mid+1]==S[mid+1]) profit += A;
        }
        profit += B;
        if(T[mid-1]==S[mid-1]) profit -= A;
        if(profit>0) {
            lower.rightEnd[0] = ((lower.rightEnd[0]=='E') ? 'E' : T[mid-3]);
            lower.rightEnd[2] = 'F';
            if(lower.to-lower.from+1<=4) {
                lower.leftEnd[mid-3-lower.from] = lower.rightEnd[0];
                lower.leftEnd[mid-1-lower.from] = lower.rightEnd[2];
            }
            upper.leftEnd[0] = T[mid+1];
            if(upper.to-upper.from+1<=4) {
                upper.rightEnd[mid+1-(upper.to-3)] = upper.leftEnd[0];
            }
        }
        ans.maxVal += profit;
    }
    //case 2: XFOF OX
    else if(T[mid+1]=='O' && T[mid+2]=='X' && (upper.to-upper.from+1>=2)) {
        ll profit = 0;
        if(lower.rightEnd[1]=='F') {
            profit -= B;
            if(T[mid-2]==S[mid-2]) profit += A;
        }
        if(upper.leftEnd[1]=='F') {
            profit -= B;
            if(T[mid+2]==S[mid+2]) profit += A;
        }
        profit += B;
        if(T[mid]==S[mid]) profit -= A;
        if(profit>0) {
            lower.rightEnd[1] = ((lower.rightEnd[1]=='E') ? 'E' : T[mid-2]);
            lower.rightEnd[3] = 'F';
            if(lower.to-lower.from+1<=4) {
                lower.leftEnd[mid-2-lower.from] = lower.rightEnd[1];
                lower.leftEnd[mid-lower.from] = lower.rightEnd[3];
            }
            upper.leftEnd[1] = ((upper.leftEnd[1]=='E') ? 'E' : T[mid+2]);
            if(upper.to-upper.from+1<=4) {
                upper.rightEnd[mid+2-(upper.to-3)] = upper.leftEnd[1];
            }
        }
        ans.maxVal += profit;
    }
    //merge and fill ends
    for(ll a=0;a<4;a++) {
        ans.leftEnd[a] = lower.leftEnd[a];
        ans.rightEnd[a] = upper.rightEnd[a];
    }
    ll idx = 0;
    for(ll a=0;a<4;a++) {
        if(ans.leftEnd[a] == 'E') {
            ans.leftEnd[a] = upper.leftEnd[idx];
            idx ++;
        }
    }
    idx = 3;
    for(ll a=3;a>=0;a--) {
        if(ans.rightEnd[a] == 'E') {
            ans.rightEnd[a] = lower.rightEnd[idx];
            idx --;
        }
    }
    return ans;
}

void makeIndi(ll node, ll idx) {
    segTree[node] = defLeaf;
    if(T[idx]==S[idx]) {
        segTree[node].maxVal = A;
    }
    segTree[node].leftEnd[0] = segTree[node].rightEnd[3] = T[idx];
    segTree[node].from = segTree[node].to = idx;
    return;
}

C init(ll start, ll end, ll node) {
    if(start==end) {
        makeIndi(node,start);
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    init(start,mid,node<<1);
    init(mid+1,end,node<<1|1);
    return segTree[node] = merging(segTree[node<<1], segTree[node<<1|1], start, end);
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(rBound<start || end<lBound) return nullLeaf;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    C lower = search(start,mid,node<<1,lBound,rBound);
    C upper = search(mid+1,end,node<<1|1,lBound,rBound);
    return merging(lower, upper, start, end);
}

void update(ll start, ll end, ll node, ll idx) {
    if(idx<start || end<idx) return;
    if(start==end) {
        T[idx] = ((T[idx]=='O') ? 'X':'O');
        makeIndi(node,idx);
        return;
    }
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,idx);
    update(mid+1,end,node<<1|1,idx);
    segTree[node] = merging(segTree[node<<1], segTree[node<<1|1], start, end);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> A >> B >> S >> T >> Q;
    init(0,N-1,1);
    while(Q--) {
        cin >> order;
        if(order=='Q') {
            cin >> a >> b;
            a --; b --;
            C res = search(0,N-1,1,a,b);
            cout << res.maxVal << endl;
        }
        else {
            cin >> n;
            n --;
            update(0,N-1,1,n);
        }
    }
    return 0;
}