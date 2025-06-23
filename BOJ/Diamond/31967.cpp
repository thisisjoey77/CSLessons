//BOJ 31967: 오름차순 서브테스크
//난이도: 다이아 5

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll mx = 260000;

ll N, Q;
ll i, j, k;
ll from, to;

stack<ll> nes;
ll A[mx], nums[mx];

ll subject, target;

ll deduct[mx] = {0,};
ll prefix[mx] = {0,};
ll sm = 0;

ll ans = 0;


void op(ll val, ll stackedCnt) {
	target = nums[val];

	while(target<nums[val-1]) {
		stackedCnt ++;
		target <<= 1;
	}
	
	if(A[val]>to || A[val] == -1) {
	    ans += stackedCnt * (to-val+1);
	    return;
	}
	else {
	    ans += stackedCnt * (A[val]-val);
	}
	
	op(A[val],stackedCnt);
	return;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	memset(A,-1,sizeof(A));
	cin >> N >> Q;

	for(i=0; i<N; i++) {
		cin >> nums[i];
		if(i>0 && nums[i]<nums[i-1]) {
		    while(!nes.empty()) {
		        A[nes.top()] = i;
			    nes.pop();
		    }
		}
		nes.push(i);
	}
	
	for(i=1; i<N; i++) {
		deduct[i] += deduct[i-1];
		target = nums[i-1];
		if(target<nums[i]) deduct[i] --;
		while(target<nums[i]) {
			deduct[i] ++;
			target <<= 1;
		}
	}

	for(i=0; i<N; i++) {
		sm += deduct[i];
		prefix[i] = sm;
	}
	
	for(i=0; i<Q; i++) {
		cin >> from >> to;
		from --; to --;
		ans = 0;
		
		if(A[from]!=-1 && A[from]<=to) {
		    op(A[from],0);
	        ans -= (prefix[to]-prefix[from-1]);
	        ans += deduct[A[from]] * (to-A[from]+1);
            ans += prefix[A[from]-1];
	    }
		cout << ans;
        if(i+1!=Q) cout << '\n';
	}
	return 0;
}
