#include <bits/stdc++.h>
using namespace std;

int N, M;

//cost, from, to vector
struct C {
    int cost;
    int from;
    int to;
};
vector<C> G;
int Cap[10000];
int ans = 0;

bool sorter(C p1, C p2) {
    
    return p1.cost < p2.cost;
}

void unify(int tar1, int tar2, int to) {
    for(int i=0;i<N;i++) {
        if(Cap[i]==tar1 || Cap[i]==tar2) Cap[i] = to;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> M;
    int x, y, z;
    for(int i=0;i<M;i++) {
        cin >> x >> y >> z;
        G.push_back({z,x-1,y-1});
    }
    
    sort(G.begin(),G.end(),sorter);
    for(int i=0;i<N;i++) Cap[i] = i+1;
    
    for(unsigned int i=0;i<G.size();i++) {
        C nval = G[i];
        if(Cap[nval.to]!=Cap[nval.from]) {
            int t = min(Cap[nval.to],Cap[nval.from]);
            unify(Cap[nval.to], Cap[nval.from], t);
            ans += nval.cost;
        }
    }
    cout << ans << '\n';
    return 0;
}
