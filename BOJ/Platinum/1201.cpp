#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 1201: NMK
//난이도: 플레3

const ll mx = 501;
ll N, M, K;
bool possible = false;
vector<ll> V[mx];

void input() {
    cin >> N >> M >> K;
    return;
}

void solve() {
    ll i, j, curIdx;
    if(N>(M*K) || N<(M+K-1)) return;
    possible = true;
    for(i=1,j=K-1;j>=0;i++,j--) {
        V[j].push_back(i);
    }
    curIdx = K-1;
    while(curIdx>=0 && i<=N) {
        if(V[curIdx].size()==M) {
            curIdx --;
            continue;
        }
        V[curIdx].push_back(i);
        i ++;
    }
    return;
}

void output() {
    ll i, j;
    ll sz;
    if(!possible) {
        cout << "-1\n";
        return;
    }
    for(i=0;i<K;i++) {
        sz = V[i].size();
        for(j=0;j<sz;j++) {
            cout << V[i][j] << ' ';
        }
    }
    cout << '\n';
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    input();
    solve();
    output();
    return 0;
}
