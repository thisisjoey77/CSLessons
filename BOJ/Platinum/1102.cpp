#include <bits/stdc++.h>
#define ll long long int
#define INF 1e9
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1102: 발전소
//난이도: 플레5

struct C{
    ll idx, bitNum;
};

const ll mx = 1<<16, nMx=17;
ll N, P;
ll A[nMx][nMx], DP[mx];
ll i, j, k;
ll sz;
ll ans = INF;
vector<C> V;
string txt;

ll numBits(ll idx) {
    ll ans = 0;
    while(idx>0) {
        ans += idx&1;
        idx >>= 1;
    }
    return ans;
}

bool sorter(C c1, C c2) {
    return c1.bitNum < c2.bitNum;
}

void init() {
    for(i=0;i<mx;i++) DP[i] = INF;
    DP[0] = 0;
    for(i=0;i<(1<<N);i++) {
        V.push_back({i,numBits(i)});
    }
    sort(V.begin(),V.end(),sorter);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            cin >> A[i][j];
        }
    }
    init();
    sz = V.size();
    cin >> txt >> P;
    for(i=0;i<N;i++) {
        if(txt[i]=='Y') {
            DP[1<<i] = 0;
        }
    }
    for(i=0;i<sz;i++) {
        ll curIdx = V[i].idx;
        if(V[i].bitNum>=P) {
            ans = min(ans,DP[curIdx]);
        }
        ll idx, nIdx;
        for(j=0,idx=1;j<N;j++,idx<<=1) {
            nIdx = idx|curIdx;
            if(nIdx==curIdx) continue;
            if(txt[j]=='Y') {
                DP[nIdx] = min(DP[nIdx], DP[curIdx]);
                continue;
            }
            ll makerIdx = 1, cost=INF;
            for(k=0,makerIdx=1;k<N;k++,makerIdx<<=1) {
                if(curIdx&makerIdx) {
                    cost = min(cost,A[k][j]);
                }
            }
            DP[nIdx] = min(DP[nIdx], DP[curIdx]+cost);
        }
    }
    cout << ((ans==INF) ? -1 : ans) << '\n';
    return 0;
}