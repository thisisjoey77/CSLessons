#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 5430: AC
//난이도: 골드5

ll N, T;
ll i, j, k;
ll pSz, vSz, xSz, fromIdx, toIdx;
bool isRev, fail, isNone;
string P, X, tmp;
vector<ll> V;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) {
    	cin >> P >> N >> X;
    	pSz = P.size(); V.clear();
    	xSz = X.size(); 
    	tmp = ""; 
    	fail=false;
    	for(i=1;i<xSz-1;i++) {
    		if(X[i]==',') {
                V.push_back(stoi(tmp));
    			tmp = "";
    		}
    		else tmp += X[i];
    	}
    	if(tmp.size()) V.push_back(stoi(tmp));
    	fromIdx = 0, toIdx = V.size()-1;
    	if(!V.size()) {
    		fromIdx = -1, toIdx=-1;
    	}
    	for(i=0;i<pSz;i++) {
    		if(P[i]=='R') {
    			swap(fromIdx,toIdx);
    			continue;
    		}
    		if(fromIdx==-1) {
    			fail = true;
    			break;
    		}
    		if(fromIdx==toIdx) {
    			fromIdx=-1, toIdx=-1;
    		}
    		else if(fromIdx<toIdx) fromIdx ++;
    		else fromIdx --;
    	}
    	if(fail) cout << "error\n";
    	else if(fromIdx==-1) cout << "[]\n";
    	else {
    		cout << "[";
    		if(fromIdx<toIdx) for(i=fromIdx;i<toIdx;i++) cout << V[i] << ',';
    		else for(i=fromIdx;i>toIdx;i--) cout << V[i] << ',';
    		cout << V[toIdx] << "]\n";
    	}
    }
    return 0;
}