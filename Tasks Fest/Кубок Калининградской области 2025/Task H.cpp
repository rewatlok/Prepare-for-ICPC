// #define _CRT_SECURE_NO_WARNINGS 

#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <climits> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <tuple> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <iomanip> 
#include <iterator>       
#include <functional> 
#include <ctime> 
#include <chrono> 
#include <cctype> 
#include <fstream> 
#include <numeric>               
#include <complex> 
#include <cassert> 

using namespace std;
       
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int               long long 
#define sz(x)             ((int)(x).size()) 
#define mp                make_pair 
#define all(x)            (x).begin(), (x).end() 
#define pb                push_back 
#define pf                push_front 
#define ff                first 
#define ss                second 
#define unique(x)         (x).erase(unique(all(x)), (x).end()) 
#define min3(a, b, c)     min(a, min(b, c)) 
#define max3(a, b, c)     max(a, max(b, c)) 
#define FOR(i, a, b)      for (int i = (a); i <= (b); i++) 
#define ROF(i, a, b)      for (int i = (a); i >= (b); i--) 
        
using vi = vector<int>;
using vd = vector<double>;
using vpii = vector<pair<int, int>>;
using vpdd = vector<pair<double, double>>;
using pii = pair<int, int>;
using pdd = pair<double, double>;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_O_statistics_node_update> Oed_set;

template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

#define BIT(n) (1LL << (n))
#define HAS_BIT(x, n) (((x) >> (n)) & 1)
#define SET_BIT(x, n) ((x) | BIT(n))

template <typename Container>
void PRINT(const Container& container) {
    for (const auto& e : container) {
        cout << e << ' ';
    } cout << '\n';
}

void print_double(double ans, int num) {
    cout << fixed << setprecision(num) << ans << '\n';
}

const int inf = 1e9 + 100;
const int INF = 1e18 + 10000;
const double eps = 1e-9;
const long double EPS = 1e-18;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

using ll = long long;
using ld = long double;

const int MAXN = 1048576;

struct Node {
    int x;
    int i;

    Node(int v = 0, int i = -1) : x(v), i(i) {}

    static Node merge(const Node& a, const Node& b) {
        if (a.x > b.x) return a;
        if (b.x > a.x) return b;
        return a.i < b.i ? a : b;
    }
};

Node tree[2 * MAXN];
int lazy[2 * MAXN];
int nt;

void build(vector<int>& a, int node, int left, int right) {
    if (left == right) {
        tree[node] = Node(a[left], left);
        return;
    }

    int mid = (left + right) / 2;
    build(a, 2 * node, left, mid);
    build(a, 2 * node + 1, mid + 1, right);
    tree[node] = Node::merge(tree[2 * node], tree[2 * node + 1]);
}

void push(int node, int left, int right) {
    if (lazy[node] != 0) {
        tree[node].x += lazy[node];

        if (left != right) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

void update_range(int node, int left, int right, int l, int r, int value) {
    push(node, left, right);

    if (l > right || r < left) {
        return;
    }

    if (l <= left && right <= r) {
        lazy[node] += value;
        push(node, left, right);
        return;
    }

    int mid = (left + right) / 2;
    update_range(2 * node, left, mid, l, r, value);
    update_range(2 * node + 1, mid + 1, right, l, r, value);
    tree[node] = Node::merge(tree[2 * node], tree[2 * node + 1]);
}

Node query_range(int node, int left, int right, int l, int r) {
    push(node, left, right);

    if (l > right || r < left) {
        return Node();
    }

    if (l <= left && right <= r) {
        return tree[node];
    }

    int mid = (left + right) / 2;
    return Node::merge(query_range(2 * node, left, mid, l, r), query_range(2 * node + 1, mid + 1, right, l, r));
}

void BUILD(vector<int>& a) {
    nt = a.size();
    int s = 1;
    while (s < nt) {
        s *= 2;
    }
    for (int i = 0; i < s - nt; i++) {
        a.push_back(0);
    }
    nt = s;
    for (int i = 0; i < 2 * s; i++) {
        lazy[i] = 0;
    }
    build(a, 1, 0, nt - 1);
}

void update(int l, int r, int x) {
    update_range(1, 0, nt - 1, l, r, x);
}

pair<int, int> query() {
    Node z = query_range(1, 0, nt - 1, 0, nt - 1);
    return { z.x, z.i };
}

int n, k;
vector<int> g[MAXN];
int m[MAXN];
int cnt1, cnt2;
vector<int> gg[MAXN];
pair<int, int> lr[MAXN];
int dist[MAXN];
int parent[MAXN];
bool color[MAXN];

void dfs1(int u, int p) {
    for (int v : g[u]) {
        if (v != p) {
            dfs1(v, u);
        }
    }
    if (u == 0) {
        if (g[u].size() == 0) m[u] = cnt1++;
        else m[u] = cnt2--;
    }
    else {
        if (g[u].size() == 1) m[u] = cnt1++;
        else m[u] = cnt2--;
    }
}

void dfs2(int u, int p) {
    if (u == m[0]) {
        dist[u] = 1;
    }
    for (int v : gg[u]) {
        if (v != p) {
            dist[v] = dist[u] + 1;
            parent[v] = u;
            dfs2(v, u);
            lr[u].first = min(lr[u].first, lr[v].first);
            lr[u].second = max(lr[u].second, lr[v].second);
        }
    }
    if (lr[u].first == MAXN && lr[u].second == -MAXN) {
        lr[u].first = u;
        lr[u].second = u;
    }
}

void Solve() {
    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int pi; cin >> pi;
        g[i].push_back(pi);
        g[pi].push_back(i);
    }

    cnt1 = 0;
    cnt2 = n - 1;

    dfs1(0, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < g[i].size(); j++) {
            g[i][j] = m[g[i][j]];
        }
    }

    for (int i = 0; i < n; i++) {
        gg[m[i]] = move(g[i]);
    }

    for (int i = 0; i < n; i++) {
        lr[i] = { MAXN, -MAXN };
        dist[i] = 0;
        parent[i] = -1;
        color[i] = false;
    }

    dfs2(m[0], -1);

    vector<int> dv;
    for (int i = 0; i < cnt1; i++) {
        dv.push_back(dist[i]);
    }
    BUILD(dv);

    int need = n - k;
    int ans = 0;

    while (need > 0) {
        pair<int, int> xi = query();
        int x = xi.first;
        int i = xi.second;

        need -= x;

        int u = i;
        while (color[u] == false) {
            color[u] = true;
            int l = lr[u].first;
            int r = lr[u].second;
            update(l, r, -1);
            if (u == m[0]) {
                break;
            }
            else {
                u = parent[u];
            }
        }

        ans += 1;
    }

    cout << ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    /*
                      ________________
                     / Just solved it \
                     |   in my mind   |
                     \________________/
                    /
                   /
　　　　　／＞　 フ         ___________
　　　　　| 　_　 _|       |          |
　 　　　／`ミ _x 彡       |   WA 2   |
　　 　 /　　　 　 |       |__________|
　　　 /　 ヽ　　 ﾉ        /          /
　／￣|　　 |　|　|       /_________ /
　| (￣ヽ＿_ヽ_)_)
　＼二つ

    */

    /*
    freopen("task.in", "r", stdin);
    freopen("task.out", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
