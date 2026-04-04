#include <bits/stdc++.h>
#define ll long long int
#define INF 1e13
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//BOJ 3043: 장난감 탱크
//난이도: 플레4

struct C{
    ll y, x, assignedX, idx;
    bool movedX;
};

const ll mx = 501;
ll N;
ll G[mx][mx];
ll numMoves;
string ans;
vector<C> V;

bool sortY(C c1, C c2) {
    return c1.y < c2.y;
}

bool sortX(C c1, C c2) {
    return c1.x < c2.x;
}

void init() {
    ll i, j;
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            G[i][j] = 0;
        }
    }
    numMoves = 0, ans = "";
    return;
}

void input() {
    ll i;
    cin >> N;
    V.resize(N);
    for(i=0;i<N;i++) {
        cin >> V[i].y >> V[i].x;
        V[i].idx = i+1;
        G[V[i].y][V[i].x] = 1;
    }
    return;
}

void solve() {
    ll i, j;
    ll moveIdx;
    sort(V.begin(),V.end(),sortX);
    for(i=0;i<N;i++) {
        V[i].assignedX = i+1;
        V[i].movedX = false;
    }
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            if(V[j].movedX) continue;
            if(V[j].assignedX!=V[j].x) {
                moveIdx = (V[j].assignedX-V[j].x)/abs(V[j].assignedX-V[j].x);
            }
            while(V[j].x!=V[j].assignedX && !G[V[j].y][V[j].x+moveIdx]) {
                G[V[j].y][V[j].x] = 0;
                G[V[j].y][V[j].x+moveIdx] = 1;
                V[j].x += moveIdx;
                ans += to_string(V[j].idx);
                ans += ((moveIdx==1) ? " R\n" : " L\n");
                numMoves ++;
            }
            if(V[j].x==V[j].assignedX) V[j].movedX = true;
        }
    }
    sort(V.begin(),V.end(),sortY);
    for(i=0;i<N;i++) {
        if(V[i].y!=i+1) {
            moveIdx = (i+1-V[i].y)/abs(i+1-V[i].y);
        }
        while(V[i].y!=i+1) {
            ans += to_string(V[i].idx);
            ans += ((moveIdx==1) ? " D\n" : " U\n");
            V[i].y += moveIdx;
            numMoves ++;
        }
    }
    return;
}

void output() {
    cout << numMoves << '\n' << ans;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    init();
    input();
    solve();
    output();
    return 0;
}
