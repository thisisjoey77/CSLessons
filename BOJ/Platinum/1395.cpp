//BOJ 1395: 스위치
//난이도: 플레 3

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 150000;
ll N, M;
ll i;
ll segTree[mx<<2]  ={0,};
ll lazy[mx<<2] = {0,};
ll type, idx1, idx2;

void updateLazy(ll start, ll end, ll node) {
    if(lazy[node]) {
        segTree[node] = abs(segTree[node]-(end-start+1));
        if(start!=end) {
            lazy[node<<1] = abs(lazy[node<<1]-1);
            lazy[node<<1|1] = abs(lazy[node<<1|1]-1);
        }
        lazy[node] = 0;
    }
    return;
}

void updateRange(ll start, ll end, ll node, ll lBound, ll rBound) {
    updateLazy(start,end,node);
    if(end<lBound || rBound < start) return;
    if(lBound<=start && end<=rBound) {
        segTree[node] = abs(segTree[node] - (end-start+1));
        if(start!=end) {
            lazy[node<<1] = abs(lazy[node<<1]-1);
            lazy[node<<1|1] = abs(lazy[node<<1|1]-1);
        }
        return;
    }
    ll mid = (start+end) >> 1;
    updateRange(start,mid,node<<1,lBound,rBound);
    updateRange(mid+1,end,node<<1|1,lBound,rBound);
    segTree[node] = segTree[node<<1] + segTree[node<<1|1];
    return;
}

ll search(ll start, ll end, ll node, ll lBound, ll rBound) {
    updateLazy(start,end,node);
    if(end<lBound || rBound<start) return 0;
    if(lBound<=start && end<=rBound) {
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    return search(start,mid,node<<1,lBound,rBound) + search(mid+1,end,node<<1|1,lBound, rBound);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for(i=0;i<M;i++) {
        cin >> type >> idx1 >> idx2;
        --idx1; --idx2;
        if(!type) {
            //스위치 idx1 --> idx2까지 반전
            updateRange(0,N-1,1,idx1,idx2);
        }
        else {
            //스위치 구간합
            cout << search(0,N-1,1,idx1,idx2) << '\n';
        }
    }
    return 0;
}
