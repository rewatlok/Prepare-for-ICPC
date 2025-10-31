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
#pragma GCC optimize("unroll-loops")
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

int n, m;
int dist[17][17];
int dp[1 << 17][17];
int parent[1 << 17][17];
int min_len[1 << 17];

vector<int> get_path(int mask) {
    int e = -1;
    int mn = INF;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            if (dp[mask][i] < mn) {
                mn = dp[mask][i];
                e = i;
            }
        }
    }
    vector<int> path;
    int c = e;
    while (mask) {
        path.push_back(c + 1);
        int p = parent[mask][c];
        if (p == -1) {
            break;
        }
        mask ^= (1 << c);
        c = p;
    }
    return path;
}

void Solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int x, y, t; cin >> x >> y >> t;
        x--; y--;
        dist[x][y] = t;
        dist[y][x] = t;
    }

    for (int mask = 0; mask <= (1 << n) - 1; mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF;
            parent[mask][i] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }

    for (int mask = 0; mask <= (1 << n) - 1; mask++) {
        for (int i = 0; i < n; i++) {
            if (!HAS_BIT(mask, i)) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (!HAS_BIT(mask, j)) {
                    continue;
                }
                if (i == j) {
                    continue;
                }
                if (dist[j][i] == INF) {
                    continue;
                }
                if (dp[mask ^ (1 << i)][j] == INF) {
                    continue;
                }
                int mask_ = mask ^ (1 << i);
                if (dp[mask_][j] + dist[j][i] < dp[mask][i]) {
                    dp[mask][i] = dp[mask_][j] + dist[j][i];
                    parent[mask][i] = j;
                }
            }
        }
    }

    for (int mask = 0; mask <= (1 << n) - 1; mask++) {
        min_len[mask] = INF;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (dp[mask][i] < min_len[mask]) {
                    min_len[mask] = dp[mask][i];
                }
            }
        }
    }

    int best_time = INF;
    int best_s1 = -1;
    int best_s2 = -1;
    int best_s3 = -1;
    for (int s1 = 1; s1 <= (1 << n) - 1; s1++) {
        if (min_len[s1] == INF) {
            continue;
        }
        int f_del_s1 = ((1 << n) - 1) ^ s1;
        for (int s2 = f_del_s1; s2 > 0; s2 = (s2 - 1) & f_del_s1) {
            if ((s2 | f_del_s1) != f_del_s1) {
                continue;
            }
            if (min_len[s2] == INF) {
                continue;
            }
            if ((f_del_s1 ^ s2) == 0) {
                continue;
            }
            if (min_len[f_del_s1 ^ s2] == INF) {
                continue;
            }
            int s3 = f_del_s1 ^ s2;
            if (max(min_len[s1], max(min_len[s2], min_len[s3])) < best_time) {
                best_time = max(min_len[s1], max(min_len[s2], min_len[s3]));
                best_s1 = s1;
                best_s2 = s2;
                best_s3 = s3;
            }
        }
    }

    if (best_time == INF) {
        cout << -1;
    }
    else {
        cout << best_time << '\n';
        PRINT(get_path(best_s1));
        PRINT(get_path(best_s2));
        PRINT(get_path(best_s3));
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
