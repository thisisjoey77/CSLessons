#include <bits/stdc++.h>
#define ll long long int
#define pii pair<ll, ll>
#define priqueue priority_queue<pii>
using namespace std;

//BOJ 16910: mex와 쿼리
//난이도: 다이아5

struct C{
    ll type;
    ll l, r;
};

const ll MAXV = 1000000000000000005LL;
const int TMX = 1202020;
ll s[TMX];
ll lazy[TMX];
ll N, i;
ll sz;
vector<C> orders;
C cur;
vector<ll> yCoords;

inline void push(ll node, ll start, ll end){
    if(!lazy[node]) return;
    if (llabs(lazy[node]) == 1){
        s[node] = (lazy[node] > 0) ? (end - start + 1) : 0;
    }else{
        s[node] = (end - start + 1) - s[node];
    }
    if(start != end){
        if (llabs(lazy[node]) == 1){
            lazy[node<<1] = lazy[node];
            lazy[node<<1|1] = lazy[node];
        }else{
            auto map_toggle = [](ll x)->ll{
                return (llabs(x) == 1) ? -x : (2 - x);
            };
            lazy[node<<1]   = map_toggle(lazy[node<<1]);
            lazy[node<<1|1] = map_toggle(lazy[node<<1|1]);
        }
    }
    lazy[node] = 0;
}

void update(ll start, ll end, ll node, ll lBound, ll rBound, ll val){
    push(node, start, end);
    if (rBound < start || end < lBound) return;
    if (lBound <= start && end <= rBound){
        if (llabs(val) == 1) lazy[node] = val;
        else lazy[node] = (llabs(lazy[node]) == 1) ? -lazy[node] : (2 - lazy[node]);
        push(node, start, end);
        return;
    }
    ll mid = (start + end) >> 1;
    update(start, mid, node<<1, lBound, rBound, val);
    update(mid+1, end, node<<1|1, lBound, rBound, val);
    s[node] = s[node<<1] + s[node<<1|1];
}

ll query(ll start, ll end, ll node){
    if (start == end) return start;
    push(node, start, end);
    ll mid = (start + end) >> 1;
    push(node<<1, start, mid);
    if ((mid - start + 1) != s[node<<1]) return query(start, mid, node<<1);
    return query(mid+1, end, node<<1|1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    orders.resize(N);
    for(i=0;i<N;i++){
        cin >> orders[i].type >> orders[i].l >> orders[i].r;
        yCoords.push_back(orders[i].l);
        yCoords.push_back(orders[i].l - 1);
        yCoords.push_back(orders[i].l + 1);
        yCoords.push_back(orders[i].r);
        yCoords.push_back(orders[i].r - 1);
        yCoords.push_back(orders[i].r + 1);
    }
    yCoords.push_back(1);
    yCoords.push_back(MAXV);
    sort(yCoords.begin(), yCoords.end());
    yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());
    if (!yCoords.empty() && yCoords.front() <= 0) yCoords.erase(yCoords.begin());
    sz = (ll)yCoords.size();
    for(i=0;i<N;i++){
        cur = orders[i];
        ll b = lower_bound(yCoords.begin(), yCoords.end(), cur.l) - yCoords.begin();
        ll c = lower_bound(yCoords.begin(), yCoords.end(), cur.r) - yCoords.begin();
        if (cur.type == 1) update(0, sz, 1, b, c, +1);
        else if (cur.type == 2) update(0, sz, 1, b, c, -1);
        else update(0, sz, 1, b, c, 2);
        ll retIdx = query(0, sz, 1);
        cout << yCoords[retIdx] << '\n';
    }
    return 0;
}