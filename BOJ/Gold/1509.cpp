#include <bits/stdc++.h>
#define ll long long int
#define INF 1e9
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 1509: 팰린드롬 분할
//난이도: 골드1

const ll mx = 2501;
ll N;
ll i, j, k;
bool isPalindrome[mx][mx] = {0,};
ll DP[mx];
string txt;

void init() {
	N = txt.size();
	for(i=0;i<mx;i++) {
		DP[i] = INF;
	}
	ll fromIdx, toIdx;
	for(i=0;i<N;i++) {
		fromIdx = toIdx = i;
		while(fromIdx>=0 && toIdx<N && txt[fromIdx]==txt[toIdx]) {
			isPalindrome[fromIdx][toIdx] = true;
			fromIdx --; toIdx ++;
		}
		if(i+1<N && txt[i]==txt[i+1]) {
			fromIdx = i, toIdx = i+1;
			while(fromIdx>=0 && toIdx<N && txt[fromIdx]==txt[toIdx]) {
				isPalindrome[fromIdx][toIdx] = true;
				fromIdx --; toIdx ++;
			}
		}
	}
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> txt;
    init();
    for(i=0;i<N;i++) {
    	if(isPalindrome[0][i]) {
    		DP[i] = 1;
    		continue;
    	}
    	for(j=0;j<i;j++) {
    		if(isPalindrome[j+1][i]) {
    			DP[i] = min(DP[i],DP[j]+1);
    		}
    	}
    }
    cout << DP[N-1] << '\n';
    return 0;
}