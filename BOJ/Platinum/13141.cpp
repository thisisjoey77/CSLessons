#include <bits/stdc++.h>
#define ll long long int
#define INF 1e10
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 13141: Ignition
//난이도: 플레5

const ll mx = 201;
ll N, M;
ll i, j, k;
ll s, e, l;
double lDoub;
double dist[mx][mx] = {0,}, maxDist[mx][mx] = {0,};
double ans = INF;

void init() {
    for(i=0;i<mx;i++) {
        for(j=0;j<mx;j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    init();
    for(i=0;i<M;i++) {
        cin >> s >> e >> l;
        lDoub = (double)l;
        dist[s][e] = dist[e][s] = min(dist[s][e],lDoub);
        maxDist[s][e] = maxDist[e][s] = max(maxDist[s][e],lDoub);
    }
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++) {
            for(k=1;k<=N;k++) {
                if(j!=k) {
                    dist[j][k] = min(dist[j][k], dist[j][i]+dist[i][k]);
                }
            }
        }
    }
    double tempAns;
    for(i=1;i<=N;i++) {
        tempAns = 0;
        for(j=1;j<=N;j++) {
            double nodeAns = dist[i][j];
            for(k=1;k<=N;k++) {
                if(j==k) {
                    nodeAns = max(nodeAns,dist[i][j]+(maxDist[j][j]/2));
                }
                else if(dist[i][j]<dist[i][k]+maxDist[k][j]) {
                    double additional = 0;
                    //case 1
                    if(dist[i][j]+maxDist[j][k]<=dist[i][k]) additional = maxDist[j][k];
                    //case 2
                    else if(dist[i][k]<=dist[i][j]) additional = (maxDist[k][j]-(dist[i][j]-dist[i][k]))/2;
                    //case 3
                    else additional = (dist[i][k]-dist[i][j])+(maxDist[j][k]-(dist[i][k]-dist[i][j]))/2;

                    nodeAns = max(nodeAns, dist[i][j]+additional);
                }
            }
            tempAns = max(tempAns,nodeAns);
        }
        ans = min(ans,tempAns);
    }
    cout << fixed << setprecision(1) << ans << '\n';
    return 0;
}
