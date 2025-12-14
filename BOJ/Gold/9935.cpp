#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 9935: 문자열 폭발
//난이도: 골드4

ll N;
ll i, j, k;
ll sz, bSz;
string T, B;
stack<char> S, temp;
string ans="";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T >> B;
    sz = T.size(); bSz = B.size();
    for(i=0;i<sz;i++) {
    	S.push(T[i]);
    	while(!S.empty()) {
    		bool fail = false;
    		for(j=bSz-1;j>=0;j--) {
    			if(S.empty() || S.top()!=B[j]) {
    				fail = true;
    				break;
    			}
    			temp.push(S.top());
    			S.pop();
    		}
    		if(fail) {
    			while(!temp.empty()) {
    				S.push(temp.top());
    				temp.pop();
    			}
    			break;
    		}
    		else temp = {};
    	}
    }
    while(!S.empty()) {
    	ans += S.top();
    	S.pop();
    }
    reverse(ans.begin(),ans.end());
    if(!ans.size()) ans = "FRULA";
    cout << ans << '\n';
    return 0;
}