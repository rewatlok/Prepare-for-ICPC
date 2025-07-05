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
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

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

const int inf = 1e9;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

vector<int> a;
vector<vector<int>> G;
vector<vector<int>> F;
vector<int> d;
int ans;

void dfs(int u) {
    for (auto v : G[u]) {
        dfs(v);
    }

    if (G[u].size() == 0) {
        d[u] = 1;
        F[u][0] = inf;
    }
    else {
        for (auto v : G[u]) {
            d[u] = min(d[u], d[v] + 1);
        }

        int s = 0;
        for (auto v : G[u]) {
            s += a[v];
        }

        for (auto v : G[u]) {
            for (int i = 0; i < F[u].size(); i++) {
                F[u][i] += F[v][i];
            }
        }

        for (int i = F[u].size() - 1; i > 0; i--) {
            F[u][i] = F[u][i - 1];
        }
        F[u][0] = 0;

        if (a[u] > s) {
            int need = a[u] - s;

            for (int i = 1; i < F[u].size(); i++) {
                if (F[u][i] < need) {
                    ans += F[u][i] * i;
                    need -= F[u][i];
                    F[u][i] = 0;
                }
                else {
                    ans += need * i;
                    F[u][i] -= need;
                    need = 0;
                }

                if (need == 0) {
                    break;
                }
            }
        }
        else {
            F[u][0] = s - a[u];
        }
    }
}

void Solve() {
    a.clear();
    G.clear();
    F.clear();
    d.clear();

    int n; cin >> n;

    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    G.resize(n);
    for (int i = 1; i < n; i++) {
        int pi; cin >> pi;
        --pi;
        G[pi].push_back(i);
    }

    F.resize(n);
    for (int i = 0; i < n; i++) {
        F[i].resize(n + 1);
        for (int j = 0; j < n + 1; j++) {
            F[i][j] = 0;
        }
    }

    d.resize(n);
    for (int i = 0; i < n; i++) {
        d[i] = inf;
    }

    ans = 0; dfs(0);
    cout << ans << '\n';
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

    int multitest = true;
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
