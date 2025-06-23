//BOJ 11025: 오세푸스 문제 3
//난이도: 플레 5

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll N, K, ans = 1;
ll i;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    
    cin >> N >> K;
	for (i = 2; i <= N; i++)
		ans = (ans + K - 1) % i + 1;
	cout << ans;
	return 0;
}
