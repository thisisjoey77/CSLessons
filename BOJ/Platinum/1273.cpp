#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1273: 샷
//난이도: 플레3

const ll mx = 3000001;
ll N, M;
ll idx, line;
ll i, j, k;
int idxSeg[mx<<2] = {0,};
int segTree[mx<<2] = {0,};
int lazy[mx<<2] = {0,};
int A[3][mx];
int floor1, floor2, floor3;

ll init(ll start, ll end, ll node) {
    if(start==end) return idxSeg[node] = 1;
    ll mid = (start+end) >> 1;
    return idxSeg[node] = init(start,mid,node<<1) + init(mid+1,end,node<<1|1);
}

void lazyUpdate(ll start, ll end, ll node) {
    if(lazy[node]) {
        segTree[node] += (end-start+1)*lazy[node];
        if(start!=end) {
            lazy[node<<1] += lazy[node];
            lazy[node<<1|1] += lazy[node];
        }
        lazy[node] = 0;
    }
    return;
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
    lazyUpdate(start,end,node);
    if(end<lBound || rBound<start) return;
    if(lBound<=start && end<=rBound) {
        segTree[node] += (end-start+1)*val;
        if(start!=end) {
            lazy[node<<1] += val;
            lazy[node<<1|1] += val;
        }
        return;
    }
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,lBound,rBound,val);
    update(mid+1,end,node<<1|1,lBound,rBound,val);
    segTree[node] = segTree[node<<1] + segTree[node<<1|1];
    return;
}

void updateIdx(ll start, ll end, ll node, ll idx) {
    if(idx<start || end<idx) return;
    idxSeg[node] --;
    if(start==end) return;
    ll mid = (start+end) >> 1;
    if(idx<=mid) updateIdx(start,mid,node<<1,idx);
    else updateIdx(mid+1,end,node<<1|1,idx);
    return;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound, bool findIdx) {
    if(findIdx) {
        if(rBound<start || end<lBound) return 0;
        if(lBound<=start && end<=rBound) return idxSeg[node];
        ll mid = (start+end) >> 1;
        return search(start,mid,node<<1,lBound,rBound,findIdx) + search(mid+1,end,node<<1|1,lBound,rBound,findIdx);
    }
    else {
        lazyUpdate(start,end,node);
        if(end<lBound || rBound<start) return 0;
        if(lBound<=start && end<=rBound) return segTree[node];
        ll mid = (start+end) >> 1;
        return search(start,mid,node<<1,lBound,rBound,findIdx) + search(mid+1,end,node<<1|1,lBound,rBound,findIdx);
    }
}

ll query(ll start, ll end, ll target) {
    if(start==end) return start;
    ll mid = (start+end) >> 1;
    ll compSum = search(0,mx-1,1,0,mid,true);
    if(target<=compSum) return query(start,mid,target);
    return query(mid+1,end,target);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    init(0,mx-1,1);
    for(i=0;i<3;i++) {
        for(j=0;j<N;j++) {
            cin >> A[i][j];
        }
    }
    for(i=0;i<N;i++) {
        floor1 = A[0][i], floor2 = A[1][i], floor3 = A[2][i];
        update(0,mx-1,1,0,floor1-1,1);
        update(0,mx-1,1,floor1,floor1+floor2-1,2);
        update(0,mx-1,1,floor1+floor2,floor1+floor2+floor3-1,5);
    }
    cin >> M;
    for(i=0;i<M;i++) {
        cin >> line;
        idx = query(0,mx-1,line);
        cout << search(0,mx-1,1,idx,idx,false) << '\n';
        updateIdx(0,mx-1,1,idx);
    }
    return 0;
}
