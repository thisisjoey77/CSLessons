#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 16496: 큰 수 만들기
//난이도: 플레5

const ll mx = 1001;
ll N;
vector<string> V;
string ans;

bool sorter(string s1, string s2) {
    ll minSz = min(s1.size(),s2.size());
    ll idx, i;
    char firstA = s1[0], firstB = s2[0];

    while(s1.size() && s2.size()) {
        minSz = min(s1.size(),s2.size());
        for(i=0;i<minSz;i++) {
            if(s1[i]!=s2[i]) {
                return s1[i] > s2[i];
            }
        }
        if(s1.size()>s2.size()) {
            if(s1.size()>minSz) s1 = s1.substr(minSz);
        }
        else if(s2.size()>s1.size()) {
            if(s2.size()) s2 = s2.substr(minSz);
        }
        else {
            s1 = s2 = "";
        }
    }
    if(s1.size()) return s1[0] > firstB;
    else if(s2.size()) return s2[0] > firstA;
    return false;
}

void input() {
    ll i;
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i];
    }
    sort(V.begin(),V.end(),sorter);
    return;
}

bool checkZero() {
    ll i;
    ll sz = ans.size();
    for(i=0;i<sz;i++) {
        if(ans[i]!='0') return false;
    }
    return true;
}

void output() {
    ll i;
    for(i=0;i<N;i++) {
        ans += V[i];
    }
    cout << (checkZero() ? "0" : ans) << '\n';
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    input();
    output();
    return 0;
}
