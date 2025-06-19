//BOJ 1168: 요세푸스 문제 2
//난이도: 플레 3

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 100001;
ll N, K;
ll i, j;
ll ans;
ll segTree[mx<<2] = {0,};
ll A[mx] = {0,};

ll init(ll start,ll end, ll node) {
    if(start==end) return segTree[node] = A[start];
    ll mid = (start+end) >> 1;
    return segTree[node] = init(start,mid,node<<1) + init(mid+1,end,node<<1|1);
}
//ans = search(0,N-1,1,0,T);
ll search(ll start, ll end, ll node, ll before, ll target){
    if(before>=target) return 0;
    if(start==end) {
        return((segTree[node]+before>=target) ? start : 0);
    }
    if(!segTree[node]) return 0;
    
    ll mid = (start+end) >> 1;
    if(segTree[node<<1]+before>=target) {
        return search(start,mid,node<<1,before,target);
    }
    else {
        return search(mid+1,end,node<<1|1,before+segTree[node<<1],target);
    }
}

ll sumSearch(ll start, ll end, ll node, ll lBound, ll rBound) {
    if(end<lBound || rBound<start) return 0;
    if(lBound<=start && end<=rBound) return segTree[node];
    ll mid = (start+end) >> 1;
    return sumSearch(start,mid,node<<1,lBound,rBound) + 
        sumSearch(mid+1,end,node<<1|1,lBound,rBound);
}

void update(ll start, ll end, ll node, ll idx) {
    if(idx<start || end<idx) {
        return;
    }
    segTree[node] --;
    if(start==end) return;
    ll mid = (start+end) >> 1;
    update(start,mid,node<<1,idx);
    update(mid+1,end,node<<1|1,idx);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for(i=1;i<=N;i++) A[i] = 1;
    init(1,N,1);
    ll T = K;
    cout << "<";
    for(i=0;i<N;i++) {
        if(i) {
            T = K-sumSearch(1,N,1,ans+1,N); 
            if(T<=0) T = sumSearch(1,N,1,1,ans) + (K);
        }
        else T = K;
    
        if(segTree[1]<T) {
            T %= segTree[1];
            if(!T) T = segTree[1];
        }

        ans = search(1,N,1,0,T);
        cout << ans;
        if(i+1<N) cout << ", ";
        update(1,N,1,ans);
    }
    cout << ">" << '\n';
    return 0;
}
