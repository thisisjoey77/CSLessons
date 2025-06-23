//BOJ 11003: 최솟값 찾기
//난이도: 플레 5

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 5000000;
ll i, j;
ll N, L;
ll segTree[mx<<1] = {0,};
ll lft;

void init() {
    for(i=N-1;i>0;--i) {
        segTree[i] = min(segTree[i<<1],segTree[i<<1|1]);
    }
    return;
}

ll minim(ll l, ll r) {
    ll res = LLONG_MAX;
    for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
        if(l&1) {
            res = min(res,segTree[l++]);
        }
        if(r&1) {
            res = min(res,segTree[--r]);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> L;
    for(i=0;i<N;i++) {
        cin >> segTree[i+N];
    }
    init();
    for(i=0;i<N;i++) {
        lft = i+1-L;
        if(lft<0) lft = 0;
        cout << minim(lft,i+1) << ' ';
    } cout << '\n';
    return 0;
}
