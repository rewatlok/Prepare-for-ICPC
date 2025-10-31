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
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Oset;

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

class SparseTablemin {
private:
    vector<vector<int>> st;
    vector<int> logTable;
    int neutral = 2e9;

    void buildLogTable(int n) {
        logTable.resize(n + 1);
        logTable[0] = logTable[1] = 0;
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }
    }

public:
    SparseTablemin(const vector<int>& a_) {
        vector<int> a = a_;
        while ((a.size() & (a.size() - 1)) != 0) {
            a.push_back(neutral);
        } int n = a.size();

        buildLogTable(n);

        int K = logTable[n] + 1;
        st.resize(K, vector<int>(n, neutral));

        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }

        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int k = logTable[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

class SparseTablemax {
private:
    vector<vector<int>> st;
    vector<int> logTable;
    int neutral = -2e9;

    void buildLogTable(int n) {
        logTable.resize(n + 1);
        logTable[0] = logTable[1] = 0;
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }
    }

public:
    SparseTablemax(const vector<int>& a_) {
        vector<int> a = a_;
        while ((a.size() & (a.size() - 1)) != 0) {
            a.push_back(neutral);
        } int n = a.size();

        buildLogTable(n);

        int K = logTable[n] + 1;
        st.resize(K, vector<int>(n, neutral));

        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }

        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int k = logTable[r - l + 1];
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

vector<vector<pair<int, int>>> g;
map<pair<int, int>, int> W;
vector<int> a;
vector<int> dist;

const int LOGN = 23;

vector<vector<int>> parent;
vector<int> depth;

void DFS(int v, int p, int d) {
    depth[v] = d;
    parent[v][0] = p;
    for (int i = 1; i < LOGN; ++i) {
        parent[v][i] = parent[parent[v][i - 1]][i - 1];
    }
    for (auto [u, w] : g[v]) {
        if (u != p) {
            DFS(u, v, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOGN - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

vector<vector<pair<int, int>>> tree;

void dfs(int u, int p) {
    a.push_back(u);
    for (auto [v, w] : g[u]) {
        if (v != p) {
            dist[v] = dist[u] + w;
            tree[u].push_back({ v, 0 });
            dfs(v, u);
        }
    }
    a.push_back(u);
}

vector<multiset<int>> mns;
vector<multiset<int, greater<int>>> mxs;

vector<int> mn_up;
vector<int> mx_up;

vector<int> in;
vector<int> out;

int get_mn_down(int u, SparseTablemin& ST) {
    return ST.query(in[u], out[u]);
}

int get_mx_down(int u, SparseTablemax& ST) {
    return ST.query(in[u], out[u]);
}

int Get(vector<pair<int, int>>& Z, int t) {
    int l = -1;
    int r = Z.size();
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (in[Z[m].ff] <= t) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return l;
}

int get_mn_up(int u, int v, SparseTablemin& ST) {
    int t = Get(tree[u], in[v]);

    if (t != -1) {
        auto [k, _] = tree[u][t];
        if (in[k] <= in[v] && out[k] >= out[v]) {
            if (mns[u].size() <= 1) {
                return mn_up[u];
            }
            auto set_it = mns[u].begin();
            if (get_mn_down(u, ST) - dist[u] == get_mn_down(k, ST) - dist[k] + W[{u, k}]) {
                ++set_it;
            }
            return min(*set_it, mn_up[u]);
        }
    }

    return mn_up[u];
}

int get_mx_up(int u, int v, SparseTablemax& ST) {
    int t = Get(tree[u], in[v]);

    if (t != -1) {
        auto [k, _] = tree[u][t];
        if (in[k] <= in[v] && out[k] >= out[v]) {
            if (mxs[u].size() <= 1) {
                return mx_up[u];
            }
            auto set_it = mxs[u].begin();
            if (get_mx_down(u, ST) - dist[u] == get_mx_down(k, ST) - dist[k] + W[{u, k}]) {
                ++set_it;
            }
            return max(*set_it, mx_up[u]);
        }
    }

    return mx_up[u];
}

void Solve() {
    int n; cin >> n;

    tree.resize(n);
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        --u;
        --v;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
        W[{u, v}] = w;
        W[{v, u}] = w;
    }

    parent.resize(n, vector<int>(LOGN));
    depth.resize(n);
    DFS(0, 0, 0);

    dist.resize(n);
    dfs(0, -1);

    in.resize(n);
    for (int i = 0; i < n; i++) {
        in[i] = -1;
    }
    out.resize(n);
    for (int i = 0; i < n; i++) {
        out[i] = -1;
    }
    vector<int> time(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (in[a[i]] == -1) {
            in[a[i]] = i; time[i] = dist[a[i]];
        }
        else {
            out[a[i]] = i; time[i] = dist[a[i]];
        }
    }

    SparseTablemin STmin(time);
    SparseTablemax STmax(time);

    mns.resize(n);
    mxs.resize(n);
    mn_up.resize(n);
    for (int i = 0; i < n; i++) {
        mn_up[i] = 0;
    }
    mx_up.resize(n);
    for (int i = 0; i < n; i++) {
        mx_up[i] = 0;
    }

    function<void(int, int)> go = [&](int u, int p) {
        if (p != -1) {
            mn_up[u] = mn_up[p] + W[{u, p}];
            if (mn_up[u] > 0) {
                mn_up[u] = 0;
            }
            mx_up[u] = mx_up[p] + W[{u, p}];
            if (mx_up[u] < 0) {
                mx_up[u] = 0;
            }
            if (mns[p].size() > 1) {
                auto it = mns[p].begin();
                if (get_mn_down(p, STmin) - dist[p] == get_mn_down(u, STmin) - dist[u] + W[{u, p}]) {
                    ++it;
                }
                mn_up[u] = min(mn_up[u], *it + W[{u, p}]);
            }
            if (mxs[p].size() > 1) {
                auto it = mxs[p].begin();
                if (get_mx_down(p, STmax) - dist[p] == get_mx_down(u, STmax) - dist[u] + W[{u, p}]) {
                    ++it;
                }
                mx_up[u] = max(mx_up[u], *it + W[{u, p}]);
            }
            if (mn_up[u] > 0) {
                mn_up[u] = 0;
            }
            if (mx_up[u] < 0) {
                mx_up[u] = 0;
            }
        }
        for (auto [v, w] : g[u]) {
            if (v != p) {
                mns[u].insert(get_mn_down(v, STmin) - dist[v] + w);
                mxs[u].insert(get_mx_down(v, STmax) - dist[v] + w);
            }
        }
        for (auto [v, w] : g[u]) {
            if (v != p) {
                go(v, u);
            }
        }
        }; go(0, -1);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        int mn1, mn2, mx1, mx2;
        if (u == v) {
            vector<int> MN;
            auto it1 = mns[u].begin();
            if (mns[u].size() > 0) {
                MN.push_back(*it1);
            }
            ++it1;
            if (mns[u].size() > 1) {
                MN.push_back(*it1);
            }
            MN.push_back(mn_up[u]);

            vector<int> MX;
            auto it2 = mxs[u].begin();
            if (mxs[u].size() > 0) {
                MX.push_back(*it2);
            }
            ++it2;
            if (mxs[u].size() > 1) {
                MX.push_back(*it2);
            }
            MX.push_back(mx_up[u]);

            sort(all(MN));
            mn1 = 0;
            if (MN.size() > 0) {
                mn1 = MN[0];
            }
            mn2 = 0;
            if (MN.size() > 1) {
                mn2 = MN[1];
            }
            sort(all(MX));
            mx1 = 0;
            if (MX.size() > 0) {
                mx1 = MX[MX.size() - 1];
            }
            mx2 = 0;
            if (MX.size() > 1) {
                mx2 = MX[MX.size() - 2];
            }
        }
        else if (lca(u, v) == u) {
            mn1 = get_mn_down(v, STmin) - dist[v];
            mn2 = get_mn_up(u, v, STmin);
            mx1 = get_mx_down(v, STmax) - dist[v];
            mx2 = get_mx_up(u, v, STmax);
        }
        else if (lca(u, v) == v) {
            swap(u, v);
            mn1 = get_mn_down(v, STmin) - dist[v];
            mn2 = get_mn_up(u, v, STmin);
            mx1 = get_mx_down(v, STmax) - dist[v];
            mx2 = get_mx_up(u, v, STmax);
        }
        else {
            mn1 = get_mn_down(v, STmin) - dist[v];
            mn2 = get_mn_down(u, STmin) - dist[u];
            mx1 = get_mx_down(v, STmax) - dist[v];
            mx2 = get_mx_down(u, STmax) - dist[u];
        }
        if (mn1 > 0) {
            mn1 = 0;
        }
        if (mn2 > 0) {
            mn2 = 0;
        }
        if (mx1 < 0) {
            mx1 = 0;
        }
        if (mx2 < 0) {
            mx2 = 0;
        }
        cout << (mx1 + mx2) - (mn1 + mn2) + 1 << '\n';
    }
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
