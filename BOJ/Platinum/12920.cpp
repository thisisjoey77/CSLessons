#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 12920: 평범한 배낭 2
//난이도: 플레4

struct C{
    ll v, c, k;
};

const ll mx = 10001;
ll N, M;
ll DP[mx];
vector<C> V;

void init() {
    ll i, j, k;
    for(i=0;i<mx;i++) {
        DP[i] = 0;
    }
    return;
}

void input() {
    ll i;
    cin >> N >> M;
    V.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i].v >> V[i].c >> V[i].k;
    }
    return;
}

void solve() {
    ll i, j, k;
    for(i=0;i<N;i++) {
        ll idx=1, temp;
        while(V[i].k>0) {
            temp = min(idx,V[i].k);
            for(j=M;j>=temp*V[i].v;j--) {
                DP[j] = max(DP[j],DP[j-temp*V[i].v]+temp*V[i].c);
            }
            idx<<=1;
            V[i].k -= temp;
        }
    }
    return;
}

void output() {
    ll i;
    ll ans = 0;
    for(i=0;i<=M;i++) {
        ans = max(ans,DP[i]);
    }
    cout << ans << '\n';
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
