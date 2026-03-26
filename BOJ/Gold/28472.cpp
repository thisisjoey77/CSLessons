#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 28472: Minimax Tree
//난이도: 골드3

const ll mx = 100001;
ll N, R, L, Q;
vector<ll> G[mx];
ll level[mx], DP[mx];
queue<ll> query, leaf;
bool isLeaf[mx];

void init() {
    ll i;
    for(i=0;i<mx;i++) {
        level[i] = -1;
        isLeaf[i] = false;
    }
    return;
}

void floorDfs(ll idx, ll curLevel) {
    ll i, nIdx;
    level[idx] = curLevel;
    ll sz = G[idx].size();
    for(i=0;i<sz;i++) {
        nIdx = G[idx][i];
        if(level[nIdx]==-1) {
            floorDfs(nIdx,curLevel+1);
        }
    }
    return;
}

void dfs(ll idx, ll val) {
    ll i, nIdx;
    ll sz = G[idx].size();
    if(isLeaf[idx]) DP[idx] = val;
    else if(sz && level[idx]&1) {
        DP[idx] = INF;
        for(i=0;i<sz;i++) {
            if(level[G[idx][i]]>level[idx]) {
                DP[idx] = min(DP[idx],DP[G[idx][i]]);
            }
        }
    }
    else if(sz) {
        DP[idx] = -1;
        for(i=0;i<sz;i++) {
            if(level[G[idx][i]]>level[idx]) {
                DP[idx] = max(DP[idx],DP[G[idx][i]]);
            }
        }
    }
    for(i=0;i<sz;i++) {
        nIdx = G[idx][i];
        if(level[nIdx]<level[idx]) {
            dfs(nIdx,DP[idx]);
        }
    }
    return;
}

void input() {
    ll i, j, k;
    ll ui, vi, ki, ti, qi;
    cin >> N >> R;
    for(i=0;i<(N-1);i++) {
        cin >> ui >> vi;
        G[ui].push_back(vi);
        G[vi].push_back(ui);
    }
    cin >> L;
    for(i=0;i<L;i++) {
        cin >> ki >> ti;
        DP[ki] = ti;
        leaf.push(ki);
        isLeaf[ki] = true;
    }
    cin >> Q;
    while(Q--) {
        cin >> qi;
        query.push(qi);
    }
    return;
}

void solve() {
    floorDfs(R,0);
    while(!leaf.empty()) {
        dfs(leaf.front(), DP[leaf.front()]);
        leaf.pop();
    }
    return;
}

void output() {
    while(!query.empty()) {
        cout << DP[query.front()] << '\n';
        query.pop();
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    input();
    solve();
    output();
    return 0;
}
