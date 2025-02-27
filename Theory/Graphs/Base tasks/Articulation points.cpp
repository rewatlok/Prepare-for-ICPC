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
#include <ranges> 
#include <numeric> 
#include <complex> 
#include <cassert> 

using namespace std;

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

template <typename Container>
void PRINT(const Container& container) {
    for (const auto& e : container) {
        cout << e << ' ';
    } cout << '\n';
}

void print_double(double ans, int num) {
    cout << fixed << setprecision(num) << ans << '\n';
}

const int inf = 1e18;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

vector<int> answer;

vector<vector<int>> g;
vector<int> vis;
vector<int> height;
vector<int> min_height_in_node;

void Erase_dfs(int v, int p) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        if (u == 0) {
            continue;
        }
        Erase_dfs(u, v);
    }
}

void DFS(int v, int p) {
    if (v == 0) {
        for (int i = 0; i < (int)g.size(); i++) {
            vis[i] = false;
        }
    }
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        DFS(u, v);
        if (v != 0 && min_height_in_node[u] >= height[v]) {
            answer.push_back(v + 1);
        }
    }
    if (v == 0) {
        for (int i = 0; i < (int)g.size(); i++) {
            vis[i] = false;
        }
        Erase_dfs(1, 1);
        for (int i = 1; i < (int)g.size(); i++) {
            if (vis[i] == false) {
                answer.push_back(1);
                break;
            }
        }
    }
}

void dfs(int v, int p) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, v);
        min_height_in_node[v] = min(min_height_in_node[v], min_height_in_node[u]);
    }
    for (auto u : g[v]) {
        if (u != p) {
            min_height_in_node[v] = min(min_height_in_node[v], height[u]);
        }
    }
}

void dfs(int v, int p, int h) {
    vis[v] = true;
    height[v] = h;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, p, h + 1);
    }
}

void Solve() {
    int n, m; cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u -= 1;
        v -= 1;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    height.resize(n);
    for (int i = 0; i < n; i++) {
        height[i] = 0;
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    min_height_in_node.resize(n);
    for (int i = 0; i < n; i++) {
        min_height_in_node[i] = (int)1e9;
    }
    min_height_in_node[0] = 0;

    dfs(0, 0, 0);

    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    dfs(0, 0);

    DFS(0, 0);

    set<int> uniq(answer.begin(), answer.end());
    vector<int> answer(uniq.begin(), uniq.end());

    cout << answer.size() << endl;
    for (auto q : answer) {
        cout << q << "\n";
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
