#include <bits/stdc++.h>
using namespace std;
//BOJ 17298: 오큰수
//난이도: 골드 4

const int mx = 1000000;
int N;
stack<int> neg;
int A[mx], nums[mx];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(A,-1,sizeof(A));
    cin >> N;
    for(int i=0;i<N;i++) {
        cin >> nums[i];
        while(!neg.empty() && nums[neg.top()]<nums[i]) {
            A[neg.top()] = nums[i];
            neg.pop();
        }
        neg.push(i);
    }
    for(int i=0;i<N;i++) {
        cout << A[i] << ' ';
    }
    cout << '\n';
    return 0;
}
