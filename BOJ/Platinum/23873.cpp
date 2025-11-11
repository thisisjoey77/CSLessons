#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 23873: HILO
//USACO 2021 December Gold #2
//난이도: 플레2

struct C {
    ll hiCnt, loCnt, hilos;
    bool isNull;
    char leftEnd, rightEnd;
};

struct D {
    ll num, idx;
    bool adding;
};

const ll mx = 200001;
ll N;
ll i, j, k;
ll lastJ;
C segTree[mx << 2];
C nullLeaf = {0, 0, 0, true, 'E', 'E'};
vector<D> orders;
ll A[mx], locs[mx];

C merging(C lower, C upper) {
    if (lower.isNull) return upper;
    if (upper.isNull) return lower;
    C ans = {
        lower.hiCnt + upper.hiCnt,
        lower.loCnt + upper.loCnt,
        lower.hilos + upper.hilos,
        false,
        lower.leftEnd, upper.rightEnd
    };
    if (lower.rightEnd == 'H' && upper.leftEnd == 'L') ans.hilos++;
    return ans;
}

C search(ll start, ll end, ll node, ll lBound, ll rBound) {
    if (rBound < start || end < lBound) return nullLeaf;
    if (lBound <= start && end <= rBound) return segTree[node];
    ll mid = (start + end) >> 1;
    C lower = search(start, mid, node << 1, lBound, rBound);
    C upper = search(mid + 1, end, node << 1 | 1, lBound, rBound);
    return merging(lower, upper);
}

void update(ll start, ll end, ll node, ll idx, pair<bool, bool> val) {
    if (idx < start || end < idx) return;
    if (start == end) {
        if (!val.second) {
            segTree[node].isNull = true;
            segTree[node].hiCnt = 0;
            segTree[node].loCnt = 0;
        } else if (val.first) {
            segTree[node].leftEnd = 'H';
            segTree[node].rightEnd = 'H';
            segTree[node].hiCnt = 1;
            segTree[node].loCnt = 0;
            segTree[node].isNull = false;
        } else {
            segTree[node].leftEnd = 'L';
            segTree[node].rightEnd = 'L';
            segTree[node].hiCnt = 0;
            segTree[node].loCnt = 1;
            segTree[node].isNull = false;
        }
        return;
    }
    ll mid = (start + end) >> 1;
    if (idx <= mid) update(start, mid, node << 1, idx, val);
    else update(mid + 1, end, node << 1 | 1, idx, val);
    segTree[node] = merging(segTree[node << 1], segTree[node << 1 | 1]);
}

ll query(ll start, ll end, ll target, ll base, bool isHi, ll node = 1) {
    if (start == end) return start;
    ll mid = (start+end) >> 1;
    C cur = search(start,mid,node<<1,base,mid);
    ll leftCnt = ((isHi) ? cur.hiCnt : cur.loCnt);
    if (target <= leftCnt) return query(start,mid,target,base,isHi,node<<1);
    return query(mid+1,end,target-leftCnt,base,isHi,node<<1|1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (i = 0;i<(mx<<2);i++) {
        segTree[i] = nullLeaf;
    }
    cin >> N;
    for (i=0;i<N;i++) {
        cin >> A[i];
        locs[A[i]] = i;
    }
    for (i=N;i>0;i--) {
        ll target = search(0,N-1,1,locs[i]+1,N-1).hiCnt;
        while (target--) {
            ll idx = query(0,N-1,1,locs[i]+1,true);
            update(0,N-1,1,idx,{true, false});
            orders.push_back({i,idx,true});
        }
        update(0,N-1,1,locs[i],{true, true});
        orders.push_back({i,locs[i],false});
    }
    lastJ = orders.size() - 1;
    for(i=0;i<=N;i++) {
        ll target = search(0,N-1,1,locs[i]+1,N-1).loCnt;
        while(target--) {
            ll idx = query(0,N-1,1,locs[i]+1,false);
            update(0,N-1,1,idx,{false, false});
        }
        while(lastJ>=0 && orders[lastJ].num==i) {
            update(0,N-1,1,orders[lastJ].idx,{true, orders[lastJ].adding});
            lastJ--;
        }
        if(i) update(0, N - 1, 1, locs[i], {false, true});
        cout << segTree[1].hilos << '\n';
    }
    return 0;
}
