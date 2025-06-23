//BOJ 25378: 조약돌
//난이도: 플레 5

#include <bits/stdc++.h>
#define ll long long int
using namespace std ;

const ll mx = 2501;
ll arr[mx], dp[mx] = {0,};
ll N, answer ;
ll i, j;
ll remain;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N ;
    for(i = 0 ; i < N ; i++)
        cin >> arr[i] ;
    
    for(i = 0 ; i < N ; i++)
    {
        remain = arr[i] ;
        dp[i] = max(dp[i], dp[i-1]) ;
        for(j = i + 1; j < N ; j++)
        {
            remain = arr[j] - remain ;
            if(remain < 0) break ;
            else if(remain == 0) dp[j] = dp[i-1] + 1 ;
        }
    }
    cout << N - dp[N-1] << '\n';
    return 0;
}
