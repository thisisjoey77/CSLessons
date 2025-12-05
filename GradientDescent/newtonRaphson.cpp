#include <bits/stdc++.h>
#define ll long long int
#define lDoub long double
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//from BOJ 14786: Ax+Bsinx=c 2
//난이도: 골드3

ll N;
ll A, B, C;
lDoub aDoub, bDoub, cDoub, nextVal=0, x=0;
const lDoub eps = 1e-13;
ll i, j, k;

lDoub f(lDoub x) {
    return aDoub*x+bDoub*sinl(x);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    cin >> A >> B >> C;
    aDoub = A, bDoub = B, cDoub = C;
    while(fabs(f(x)-cDoub)>eps) {
        nextVal = x-(aDoub*x + bDoub*sinl(x)-cDoub)/(aDoub+bDoub*cosl(x));
        x = nextVal;
    }
    cout << x << '\n';
    return 0;
}
