#include <bits/stdc++.h>
using namespace std;

//BOJ 2637: 장난감 조립
//난이도: 골드 2

long long n, m, x, y, k, i, j, qf;
long long arr[101][101], base[101] = {0,};
queue<long long> q;
long long inDeg[101] = {0,};
long long master[101][101] = {0,};

int main(){
    cin>>n;
    cin>>m;
    for(i=1; i<=m; i++){ //입력 받기 
        cin>>x>>y>>k;
        arr[x][y] = k;
        //x needs k of y
        inDeg[x] ++;
    }
    for(i=1; i<=n; i++){ //중간 부품 정하기 
        if(!inDeg[i])  {
            base[i] = 1;
            q.push(i);
        }
    }
    while(!q.empty()) {
        long long X = q.front(); q.pop();
        for(i=1;i<=n;i++) {
            if(arr[i][X]) {
                inDeg[i] --;
                if(base[X]) {
                    master[i][X] += arr[i][X];
                }
                else {
                    for(j=1;j<=n;j++) {
                        if(base[j]) {
                            master[i][j] += master[X][j] * arr[i][X];
                        }
                    }
                }
                
                if(!inDeg[i]) q.push(i);
            }
        }
    }
    
    for(i=1;i<=n;i++) {
        if(base[i])
        cout << i << ' ' << master[n][i] << '\n';
    }
    return 0;
}
