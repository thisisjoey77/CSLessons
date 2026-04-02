#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 1014: No Cheating (Small)
//난이도: 플레4

const ll mx = 1<<10, nMx = 11;
ll N, M, T;
vector<string> V;
vector<ll> gridBits, nextPos[mx];
ll DP[nMx][mx], bitCount[mx];

ll numBits(ll idx) {
    ll ans = 0;
    while(idx) {
        ans += idx&1;
        idx >>= 1;
    }
    return ans;
}

void reset() {
    ll i, j;
    for(i=0;i<nMx;i++) {
        for(j=0;j<mx;j++) {
            DP[i][j] = 0;
        }
    }
    for(i=0;i<mx;i++) {
        nextPos[i].clear();
    }
    gridBits.clear();
    V.clear();
    return;
}

void init() {
    ll i;
    for(i=0;i<mx;i++) {
        bitCount[i] = numBits(i);
    }
    return;
}

void solve() {
    ll i, j, k;
    ll sz, nIdx;
    gridBits.resize(M);
    for(i=0;i<M;i++) {
        gridBits[i] = 0;
        for(j=0;j<N;j++) {
            gridBits[i] <<= 1;
            if((char)V[j][i]=='x') gridBits[i] ++;
        }
    }
    for(i=0;i<(1<<N);i++) {
        for(j=0;j<(1<<N);j++) {
            if(!(i&j) && !((i<<1)&j) && !(i&(j<<1))) {
                nextPos[i].push_back(j);
            }
        }
    }
    for(i=0;i<(1<<N);i++) {
        if(gridBits[0]&i) continue;
        DP[0][i] = bitCount[i];
    }
    for(i=0;i<M-1;i++) {
        for(j=0;j<(1<<N);j++) {
            if(gridBits[i]&j) continue;
            sz = nextPos[j].size();
            for(k=0;k<sz;k++) {
                nIdx = nextPos[j][k];
                if(gridBits[i+1]&nIdx) continue;
                DP[i+1][nIdx] = max(DP[i+1][nIdx],DP[i][j]+bitCount[nIdx]);
            }
        }
    }
    return;
}

void output() {
    ll i;
    ll ans = 0;
    for(i=0;i<(1<<N);i++) {
        ans = max(ans,DP[M-1][i]);
    }
    cout << ans << '\n';
}

void input() {
    ll i;
    cin >> T;
    while(T--) {
        reset();
        cin >> N >> M;
        V.resize(N);
        for(i=0;i<N;i++) {
            cin >> V[i];
        }
        solve();
        output();
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    input();
    return 0;
}
