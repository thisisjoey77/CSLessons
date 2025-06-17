//2025 Jan 3
//Implementation of the Segment Tree Algorithm (세그먼트 트리 알고리즘)
//Joy Kim

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

//ACMICPC 2042 Implementation

/*
 * PROBLEM
 * Let's say we initially get an array of integers given length N (1<=N<=1,000,000).
 * There are two things the user could do:
 *  1. Choose an interval to find the interval sum (구간합) of
 *  2. Replace an element of the given array with another value.
 * The number of such tasks in total are given with integer input M (1<=M<=1,000,000). 
 * For each task input, there are three integer inputs a, b, and c:
 *  - Input a identifies the type of task (1 or 2).
 *  - If a is 1, the user changes the bth element of the array with c.
 *  - If a is 2, the user finds the interval sum between index b to c.
 *  - Note that the order of counting the arrays is 1,2,3,... instead of 0,1,2,... 
 * As output, whenever the user demands the interval sum, the program must output the sum as an integer, followed by a new line.
*/

const ll mx = 1000000;
ll N, M;
ll A[mx] = {0,}, segTree[mx<<2] = {0,};
ll i, j, k;
ll a, b, c;
ll changeVal;


/*
 * The function initially sets up the segment tree.
*/
ll init(ll start, ll end, ll node) {
  //Condition: The segment tree node handles only one element of array A.
  if(start==end) {
    return segTree[node] = A[start];
  }

  //Else: The segment tree node isn't divided enough (handles more than one element)
  ll mid = (start+end) >> 1;
  return segTree[node] = init(start,mid,node*2) + init(mid+1,end,node*2+1);
}


/* 
 * The function finds the interval sum, given intervals lBound --> rBound. 
 * The segment tree node at segTree[node] has the interval sum from  A[start] --> A[end].
*/
ll sum(ll start, ll end, ll node, ll lBound, ll rBound) {
  //Condition: The segment tree node's interval handles nowhere that touches interval lBound --> rBound.
  if(end<lBound || rBound<start) {
    return 0;
  }

  //Condition: The segment tree node's interval is entirely fit inside the interval lBound --> rBound.
  if(lBound<=start && end<=rBound) {
    return segTree[node];
  }

  //Else: The segment tree node's interval fits partially into the interval lBound --> rBound.
  ll mid = (start+end) >> 1;
  return sum(start,mid,node*2,lBound,rBound) + sum(mid+1,end,node*2+1,lBound,rBound);
}

/*
 * The function updates relevant nodes of the segment tree when an element of array A is changed.
 * From original value A[b] to new input value c, the difference is integer val.
 * The segment tree node at segTree[node] has the interval sum from A[start] --> A[end].
 * Input b-1 is stored as number idx (Actual index of array A the user tries to change).
*/ 
void update(ll start, ll end, ll node, ll val, ll idx) {
  //Condition: The segment tree node's interval does not handle idxth element in array A.
  if(end<idx || idx<start) {
    return;
  }
  segTree[node] += val;

  //Condition: The segment tree node manages one element, A[b].
  if(start==end) {
    return;
  }

  //Update all children nodes of the segment tree.
  ll mid = (start+end) >> 1;
  update(start,mid,node*2,val,idx);
  update(mid+1,end,node*2+1,val,idx);
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  //INPUT 
  cin >> N >> M;
  for(i=0;i<N;i++) {
    cin >> A[i];
  }

  //Initialize the segment tree according to the initial array A setup.
  init(0,N-1,1);

  for(i=0;i<M;i++) {
    cin >> a >> b >> c;
    -- b;
    //Condition: User inputs for task 1
    if(a==1) {
      changeVal = c-A[b];
      A[b] = c;
      update(0,N-1,1,changeVal,b);
    }
    //Else: User inputs for task 2
    else {
      -- c;
      cout << sum(0,N-1,1,b,c) << '\n';
    }
  }
  return 0;
}
