#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1028: 다이아몬드 광산
//난이도: 플레5

const ll mx = 751;
ll N, R, C;
ll i, j, k;
ll ans = 0;
pii DP[mx][mx];
//first = 위로 올라가는거, second = 아래로 내려가는거
char A[mx][mx];
string txt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            DP[i][j] = make_pair(0,0);
        }
    }
    cin >> R >> C;
    for(i=0;i<R;i++) {
        cin >> txt;
        for(j=0;j<C;j++) {
            A[i][j] = txt[j];
        }
    }
    for(j=0;j<C;j++) {
        for(i=0;i<R;i++) {
            if(A[i][j]!='1') continue;
            if(!ans) ans = 1;
            DP[i][j] = make_pair(1,1);
            if(j>0) {
                if(i>0) DP[i][j].second += DP[i-1][j-1].second;
                if(i+1<R) DP[i][j].first += DP[i+1][j-1].first;
            }
            ll idx = 1;
            while(j-idx>=0 && i-idx>=0 && i+idx<R) {
                if(A[i+idx][j-idx]!='1' || A[i-idx][j-idx]!='1') break;
                if(min(DP[i+idx][j-idx].second,DP[i-idx][j-idx].first)>=idx+1) {
                    ans = max(ans,idx+1);
                }
                idx ++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}