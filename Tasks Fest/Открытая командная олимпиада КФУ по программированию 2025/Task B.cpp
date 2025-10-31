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
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_O_statistics_node_update> Oset;

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

int d[700][700];

void Solve() {
    int m, n; cin >> m >> n;

    int ys, xs, yf, xf; cin >> ys >> xs >> yf >> xf;
    ys--;
    xs--;
    yf--;
    xf--;

    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i].resize(m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    set<pair<int, pair<int, int>> > go;
    go.insert({ 0, {xs, ys} });
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            d[i][j] = inf;
        }
    }
    d[xs][ys] = 0;

    while (go.size() > 0) {
        pair<int, pair<int, int>> v = *go.begin();
        pair<int, int> x = v.ss;
        int w = v.ff;
        go.erase(go.begin());

        for (int i = x.ff - 1; i <= x.ff + 1; i += 2) {
            if (0 <= i && i < n && a[i][x.ss] != 0) {
                if (d[i][x.ss] > w + a[i][x.ss]) {
                    if (go.count({ d[i][x.ss], {i, x.ss} })) {
                        go.erase({ d[i][x.ss], {i, x.ss} });
                    }
                    d[i][x.ss] = w + a[i][x.ss];
                    go.insert({ d[i][x.ss], {i, x.ss} });
                }
            }
        }

        for (int i = x.ss - 1; i <= x.ss + 1; i += 2) {
            if (0 <= i && i < m && a[x.ff][i] != 0) {
                if (d[x.ff][i] > w + a[x.ff][i]) {
                    if (go.count({ d[x.ff][i], {x.ff, i} })) {
                        go.erase({ d[x.ff][i], {x.ff, i} });
                    }
                    d[x.ff][i] = w + a[x.ff][i];
                    go.insert({ d[x.ff][i], {x.ff, i} });
                }
            }
        }
    }

    cout << d[xf][yf];
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
