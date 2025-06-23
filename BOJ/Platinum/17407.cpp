//BOJ 17407: 괄호 문자열과 쿼리
//난이도: 플레 3

//최솟값 세그트리?
//각 노드는 1-x 구간합
#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 200000;
string T;
unsigned ll sz;
ll N;
ll i, target, val;
ll A[mx] = {0,}, segTree[mx<<2] = {0,}, lazy[mx<<2] = {0,};
ll cnt = 0, sm = 0;


ll init(ll start, ll end, ll node) {
    if(start==end) return segTree[node] = A[start];
    ll mid = (start+end) >> 1;
    return segTree[node] = min(init(start,mid,node<<1), init(mid+1,end,node<<1|1));
}

void updateLazy(ll start, ll end, ll node) {
    if(lazy[node]) {
        segTree[node] += lazy[node];
        if(start!=end) {
            lazy[node<<1] += lazy[node];
            lazy[node<<1|1] += lazy[node];
        }
        lazy[node] = 0;
    }
    return;
}

void updateRange(ll start, ll end, ll node, ll lBound, ll rBound, ll val) {
    updateLazy(start,end,node);
    if(end<lBound || rBound<start) return;
    if(lBound<=start && end<=rBound) {
        segTree[node] += val;
        if(start!=end) {
            lazy[node<<1] += val;
            lazy[node<<1|1] += val;
        }
        return;
    }
    ll mid = (start+end) >> 1;
    updateRange(start,mid,node<<1,lBound,rBound,val);
    updateRange(mid+1,end,node<<1|1,lBound,rBound,val);
    segTree[node] = min(segTree[node<<1], segTree[node<<1|1]);
    return;
}

ll search(ll start, ll end, ll node, ll idx) {
    updateLazy(start,end,node);
    if(idx<start || end<idx) return LLONG_MAX;
    if(idx<=start && end<=idx) {
        return segTree[node];
    }
    ll mid = (start+end) >> 1;
    return min(search(start,mid,node<<1,idx), search(mid+1,end,node<<1|1,idx));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T >> N;
    sz = T.size();
    for(i=0;i<sz;i++) {
        sm += (T[i]=='(') ? 1 : -1;
        A[i] = sm;
    }
    init(0,sz-1,1);
    for(i=0;i<N;i++) {
        cin >> target;
        --target;
        val = (T[target]=='(') ? -2 : 2;
        updateRange(0,sz-1,1,target,sz-1,val);
        if(segTree[1]==0 && search(0,sz-1,1,sz-1)==0) cnt ++;
        T[target] = (T[target]=='(') ? ')' : '(';
    }
    cout << cnt << '\n';
    return 0;
}

