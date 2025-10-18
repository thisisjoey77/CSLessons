#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 19651: 수열과 쿼리 39
//난이도: 다이아5

struct sequence {
	pii start, end;
	ll d, length;
};

struct C{
	ll aOne, d;
	bool isSeq;
};

struct D{
	sequence maxSeq, leftSeq, rightSeq;
	ll leftEnd, rightEnd;
};

const ll mx = 100001;
ll N, M;
ll i, j, k;
ll query, from, to, x, y;
ll A[mx];
C lazy[mx<<2];
D segTree[mx<<2];
sequence nullSeq = {{0,0},{0,0},0,0};
D nullLeaf = {nullSeq, nullSeq, nullSeq, 0,0};

bool isNull(D target) {
	return target.maxSeq.length==0;
}

sequence findMx(sequence s1, sequence s2) {
	if(s1.length>s2.length) return s1;
	return s2;
}

D merging(D lower, D upper, ll start, ll end) {
	if(isNull(lower)) return upper;
	if(isNull(upper)) return lower;
	D ans = {
		findMx(lower.maxSeq, upper.maxSeq),
		lower.leftSeq, upper.rightSeq,
		lower.leftEnd, upper.rightEnd
	};
	ll mid = (start+end) >> 1;
	ll diff = upper.leftEnd - lower.rightEnd;

	sequence newSeq;
	pii fromIdx = lower.rightSeq.end;
	pii toIdx = upper.leftSeq.start;
	ll ld = lower.rightSeq.d, rd = upper.leftSeq.d;
	if(lower.rightSeq.length==1) ld = diff;
	if(upper.leftSeq.length==1) rd = diff;
	if(rd==diff) toIdx = upper.leftSeq.end;
	if(ld==diff) fromIdx = lower.rightSeq.start;
	newSeq = {fromIdx,toIdx,diff,(toIdx.second-fromIdx.second)+1};
	ans.maxSeq = findMx(ans.maxSeq,newSeq);

	if(lower.leftSeq.length==(mid-start+1)) {
		sequence ext = lower.leftSeq;
		ll ed = ext.d;
		if(ext.length==1) ed = diff;
		if(ed==diff) {
			if(upper.leftSeq.length==1 || upper.leftSeq.d==diff) {
				ext.end = upper.leftSeq.end;
				ext.length += upper.leftSeq.length;
				ext.d = diff;
			} else {
				ext.end = upper.leftSeq.start;
				ext.length += 1;
				if(ext.length==2) ext.d = diff;
			}
			ans.leftSeq = ext;
			ans.maxSeq = findMx(ans.maxSeq,ans.leftSeq);
		}
	}

	if(upper.rightSeq.length==(end-(mid+1)+1)) {
		sequence ext = upper.rightSeq;
		ll ed = ext.d;
		if(ext.length==1) ed = diff;
		if(ed==diff) {
			if(lower.rightSeq.length==1 || lower.rightSeq.d==diff) {
				ext.start = lower.rightSeq.start;
				ext.length += lower.rightSeq.length;
				ext.d = diff;
			} else {
				ext.start = lower.rightSeq.end;
				ext.length += 1;
				if(ext.length==2) ext.d = diff;
			}
			ans.rightSeq = ext;
			ans.maxSeq = findMx(ans.maxSeq,ans.rightSeq);
		}
	}

	return ans;
}

D init(ll start, ll end, ll node) {
	if(start==end) {
		sequence curSeq = {{A[start],start},{A[start],start},0,1};
		return segTree[node] = {curSeq, curSeq, curSeq, A[start],A[start]};
	}
	ll mid = (start+end) >> 1;
	return segTree[node] = merging(init(start,mid,node<<1), init(mid+1,end,node<<1|1),start, end);
}

void lazyUpdate(ll start, ll end, ll node) {
	if(lazy[node].isSeq) {
	    ll mid = (start+end) >> 1;
	    ll startIdx, endIdx;

	    startIdx = segTree[node].maxSeq.start.second; 
	    endIdx = segTree[node].maxSeq.end.second;
		segTree[node].maxSeq = {
			{segTree[node].maxSeq.start.first+lazy[node].aOne+lazy[node].d*(startIdx-start),segTree[node].maxSeq.start.second},
			{segTree[node].maxSeq.end.first+lazy[node].aOne+lazy[node].d*(endIdx-start),segTree[node].maxSeq.end.second},
			segTree[node].maxSeq.length>=2 ? segTree[node].maxSeq.d+lazy[node].d : segTree[node].maxSeq.d,
			segTree[node].maxSeq.length
		};

		startIdx = segTree[node].leftSeq.start.second; 
		endIdx = segTree[node].leftSeq.end.second;
		segTree[node].leftSeq = {
			{segTree[node].leftSeq.start.first+lazy[node].aOne+lazy[node].d*(startIdx-start),segTree[node].leftSeq.start.second},
			{segTree[node].leftSeq.end.first+lazy[node].aOne+lazy[node].d*(endIdx-start),segTree[node].leftSeq.end.second},
			segTree[node].leftSeq.length>=2 ? segTree[node].leftSeq.d+lazy[node].d : segTree[node].leftSeq.d,
			segTree[node].leftSeq.length
		};

		startIdx = segTree[node].rightSeq.start.second; 
		endIdx = segTree[node].rightSeq.end.second;
		segTree[node].rightSeq = {
			{segTree[node].rightSeq.start.first+lazy[node].aOne+lazy[node].d*(startIdx-start),segTree[node].rightSeq.start.second},
			{segTree[node].rightSeq.end.first+lazy[node].aOne+lazy[node].d*(endIdx-start),segTree[node].rightSeq.end.second},
			segTree[node].rightSeq.length>=2 ? segTree[node].rightSeq.d+lazy[node].d : segTree[node].rightSeq.d,
			segTree[node].rightSeq.length
		};

		segTree[node].leftEnd += lazy[node].aOne;
		segTree[node].rightEnd += lazy[node].aOne+lazy[node].d*(end-start);

		if(start!=end) {
			lazy[node<<1] = {
				lazy[node<<1].aOne+lazy[node].aOne,
				lazy[node<<1].d + lazy[node].d,
				true
			};
			lazy[node<<1|1] = {
				lazy[node<<1|1].aOne+lazy[node].aOne+lazy[node].d*(mid+1-start),
				lazy[node<<1|1].d + lazy[node].d,
				true
			};
		}
		lazy[node] = {0,0,false};
	}
}


D search(ll start, ll end, ll node, ll lBound, ll rBound) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return nullLeaf;
	if(lBound<=start && end<=rBound) return segTree[node];
	ll mid = (start+end) >> 1;
	D lower = search(start,mid,node<<1,lBound,rBound);
	D upper = search(mid+1,end,node<<1|1,lBound,rBound);
	return merging(lower, upper, start,end);
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, C val) {
	lazyUpdate(start,end,node);
	if(rBound<start || end<lBound) return;
	if(lBound<=start && end<=rBound) {
	    if(start==end) {
	        ll newVal = val.aOne + val.d*(start-lBound);
            pii coord = {segTree[node].leftEnd+newVal,start};
		    segTree[node].maxSeq = {coord,coord,0,1};
		    segTree[node].leftSeq = segTree[node].maxSeq;
		    segTree[node].rightSeq = segTree[node].maxSeq;
		    segTree[node].leftEnd += newVal;
		    segTree[node].rightEnd = segTree[node].leftEnd;
		    return;
	    }
		lazy[node] = {
			lazy[node].aOne + val.aOne + val.d*(start-lBound),
			lazy[node].d + val.d,
			true
		};
		lazyUpdate(start,end,node);
		return;
	}
	ll mid = (start+end) >> 1;
	update(start,mid,node<<1,lBound,rBound,val);
	update(mid+1,end,node<<1|1,lBound,rBound,val);
	segTree[node] = merging(segTree[node<<1], segTree[node<<1|1],start,end);
	return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for(i=0;i<N;i++) {
    	cin >> A[i];
    }
    init(0,N-1,1);
    cin >> M;
    for(i=0;i<M;i++) {
    	cin >> query >> from >> to;
    	from --; to --;
    	if(query==2) {
    		cout << search(0,N-1,1,from,to).maxSeq.length << '\n';
    		continue;
    	}
    	cin >> x >> y;
    	update(0,N-1,1,from,to,{x,y});
    }
    return 0;
}
