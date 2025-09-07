#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const ll primitive_root = 3;

//BOJ 22273: 큰 수 곱셈 3
//난이도: 다이아5

ll fpow(ll x, ll n, ll mod){
    ll result = 1;
    while (n){
        if (n & 1) result = result * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return result;
}

void ntt(vector<ll> &A, bool inv = false){
    int n = A.size();
    for (int i = 1, j = 0, bit; i < n; i++){
        bit = n >> 1;
        while (j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if (i < j) swap(A[i], A[j]);
    }

    ll z, w, tmp;
    for (int s = 2; s <= n; s <<= 1){
        z = fpow(primitive_root, (mod - 1) / s, mod);
        if (inv) z = fpow(z, mod - 2, mod);
        for (int i = 0; i < n; i += s){
            w = 1;
            for (int j = i; j < i + (s >> 1); j++){
                tmp = A[j + (s >> 1)] * w;
                A[j + (s >> 1)] = (A[j] - tmp) % mod;
                A[j] = (A[j] + tmp) % mod;
                w = (w * z) % mod;
            }
        }
    }

    for (auto &x: A) if (x < 0) x += mod;

    if (inv){
        ll inv_n = fpow(n, mod - 2, mod);
        for (auto &x: A) x = x * inv_n % mod;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string SA, SB;
    cin >> SA >> SB;

    int a = SA.size(), b = SB.size(), N = 1 << (int)ceil(log2(a + b - 1));

    vector<ll> A(N, 0);
    for (int i = 0; i < a; i++) A[i] = SA[i] - '0';
    vector<ll> B(N, 0);
    for (int i = 0; i < b; i++) B[i] = SB[i] - '0';

    ntt(A); ntt(B);
    for (int i = 0; i < N; i++) A[i] *= B[i];
    ntt(A, true);

    ll result[a + b] = {0, };
    for (int i = 0; i < a + b - 1; i++) result[i + 1] = A[i];

    for (int i = a + b - 1; i > 0; i--){
        result[i - 1] += result[i] / 10;
        result[i] %= 10;
    }

    if (result[0]) cout << result[0]; 
    for (int i = 1; i < a + b; i++) cout << result[i];
}
