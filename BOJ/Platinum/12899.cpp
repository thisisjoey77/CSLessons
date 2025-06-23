//BOJ 12899: 데이터구조
//난이도: 플레 4

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 2000001;
ll N;
ll i, j;
ll a, T;
ll ans;
ll segTree[mx<<2] = {0,};

void update(ll start, ll end, ll node, ll idx, ll val) {
    if(idx<start || end<idx) return;
    segTree[node] += val;
    if(start==end) return;
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,idx,val);
    update(mid+1,end,node<<1|1,idx,val);
    return;
}

ll search(ll start, ll end, ll node, ll before) {
    if(before>=T) return 0;
    //정답
    if(start==end) {
        if(T-1-before<=segTree[node]-1) return start;
        return 0;
    }
    if(!segTree[node]) return 0;
    ll mid = (start+end) >> 1;
    ll firstHalf = 0, secondHalf = 0;
    //left node contains it
    if(before+segTree[node<<1]>=T)
        return search(start,mid,node<<1,before);
    else
        return search(mid+1,end,node<<1|1,before+segTree[node<<1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
        cin >> a >> T;
        //case 1: add
        if(a==1) {
            update(1,mx,1,T,1);
        }
        //case 2: remove
        else {
            ans = search(1,mx,1,0);
            cout << ans << '\n';
            update(1,mx,1,ans,-1);
        }
    }
    return 0;
}
