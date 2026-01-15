#include <bits/stdc++.h>
#define ll long long int
#define INF 1e18
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 2098: 외판원 순회
//난이도: 골드1

struct C{
    ll idx, numBits;
};

const ll mx = 17, bitMx = 1<<16;
ll N;
ll i, j, k;
ll sz;
ll W[mx][mx];
ll DP[bitMx][mx], isoBits[mx];
ll finAns = INF;
vector<C> V;
C cur;

bool sorter(const C &c1, const C &c2) {
    return c1.numBits < c2.numBits;
}

ll findBits(ll idx) {
    ll ans = 0;
    while(idx) {
        ans += idx&1;
        idx >>= 1;
    }
    return ans;
}

void init() {
    for(i=0;i<bitMx;i++) {
        for(j=0;j<mx;j++) {
            DP[i][j] = INF;
        }
    }
    isoBits[1] = 1;
    for(i=2;i<mx;i++) {
        isoBits[i] = isoBits[i-1] << 1;
    }
    sz = (1<<N)-1;
    V.resize(1);
    for(i=1;i<sz;i++) {
        V.push_back({i,findBits(i)});
    }
    sort(V.begin()+1,V.end(),sorter);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    init();
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            cin >> W[i][j];
        }
    }
    for(i=2;i<=N;i++) {
        if(W[1][i]) DP[isoBits[i]][i] = W[1][i];
    }
    ll nIdx;
    for(i=1;i<sz;i++) {
        cur = V[i];
        for(j=1;j<=N;j++) {
            if(DP[cur.idx][j]==INF) continue;
            for(k=1;k<=N;k++) {
                if(!W[j][k] || (isoBits[k] & cur.idx)) continue;
                nIdx = isoBits[k] | cur.idx;
                DP[nIdx][k] = min(DP[nIdx][k], DP[cur.idx][j]+W[j][k]);
            }
        }
    }
    cout << DP[sz][1] << '\n';
    return 0;
}