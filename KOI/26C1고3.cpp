#include <bits/stdc++.h>
#define ll long long int
#define INF 1e15
#define pii pair<ll, ll>
#define priqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;

//한국정보올림피아드 2026년 1차대회 고3: 점프

struct C{
    bool isNull;
    ll pointCnt, minHeight, sweepCnt;
};

const ll mx = 900001;
ll N, D;
ll ans[mx], pointsOn[mx];
C segTree[2][mx<<2];
vector<ll> coords, V;
C nullLeaf = {true,0,INT_MAX,0};

C merging(const C &lower, const C &upper, int type) {
    if(lower.isNull) return upper;
    if(upper.isNull) return lower;
    C ans = {
        false, lower.pointCnt+upper.pointCnt, min(lower.minHeight,upper.minHeight), -1
    };
    if(type==0) {
        //leftSweep
        //case 1: 오른쪽 높이가 더 낮으면 무조건 sweep 가능
        if(upper.minHeight<lower.minHeight) {
            ans.sweepCnt = upper.sweepCnt;
        }
        //case 2: 오른쪽 높이가 더 높으면 왼쪽거로 유지하되 count 더하기
        else {
            ans.sweepCnt = lower.sweepCnt + upper.pointCnt;
        }
    }
    else {
        //반대로
        if(lower.minHeight<upper.minHeight) {
            ans.sweepCnt = lower.sweepCnt;
        }
        else {
            ans.sweepCnt = upper.sweepCnt + lower.pointCnt;
        }
    }
    return ans;
}

C search(int start, int end, int node, int lBound, int rBound, int type) {
    if(rBound<start || end<lBound) return nullLeaf;
    if(lBound<=start && end<=rBound) return segTree[type][node];
    int mid = (start+end) >> 1;
    C lower = search(start,mid,node<<1,lBound,rBound,type);
    C upper = search(mid+1,end,node<<1|1,lBound,rBound,type);
    return merging(lower,upper,type);
}

void update(int start, int end, int node, int idx, int height, pii sweeps) {
    if(idx<start || end<idx) return;
    if(start==end) {
        for(int i=0;i<2;i++) {
            segTree[i][node].minHeight = height;
            segTree[i][node].isNull = false;
            segTree[i][node].pointCnt ++;
        }
        segTree[0][node].sweepCnt = sweeps.first;
        segTree[1][node].sweepCnt = sweeps.second;
        return;
    }
    int mid = (start+end) >> 1;
    if(idx<=mid) update(start,mid,node<<1,idx,height,sweeps);
    else update(mid+1,end,node<<1|1,idx,height,sweeps);
    for(int i=0;i<2;i++) {
        segTree[i][node] = merging(segTree[i][node<<1],segTree[i][node<<1|1],i);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(pointsOn,0,sizeof(pointsOn));
    for(int i=0;i<(mx<<2);i++) segTree[0][i] = segTree[1][i] = nullLeaf;
    cin >> N >> D;
    V.resize(N);
    for(int i=0;i<N;i++) {
        cin >> V[i];
        coords.push_back(V[i]);
        coords.push_back(V[i]+D);
        coords.push_back(V[i]-D);
    }
    sort(coords.begin(),coords.end());
    coords.erase(unique(coords.begin(),coords.end()),coords.end());
    const int sz = coords.size();
    for(int i=N-1;i>=0;i--) {
        int idx = lower_bound(coords.begin(),coords.end(),V[i])-coords.begin();
        int leftIdx = lower_bound(coords.begin(),coords.end(),V[i]-D)-coords.begin();
        int rightIdx = lower_bound(coords.begin(),coords.end(),V[i]+D)-coords.begin();
        C leftSweep = search(0,sz-1,1,leftIdx,idx,0);
        C rightSweep = search(0,sz-1,1,idx,rightIdx,1);
        ans[i] = leftSweep.sweepCnt+rightSweep.sweepCnt-pointsOn[idx]+1;
        update(0,sz-1,1,idx,i,make_pair(leftSweep.sweepCnt+1,rightSweep.sweepCnt+1));
        pointsOn[idx] ++;
    }
    for(int i=0;i<N;i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}
