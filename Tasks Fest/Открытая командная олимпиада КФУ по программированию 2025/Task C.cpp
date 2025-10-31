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

int md = 1'000'000'009;
vector<int> fib = { 1, 1, 2, 3, 5, 8, 13, 21, 34 };

int comb(int x) {
    return fib[x];
}

int cnt(int a, int b, int n) {
    int prg = -2;
    int cg = 0;
    int res = 1;
    vector<int> bad;
    for (int i = 0; i < n; i++) {
        int x = (a >> i) & 1;
        int y = (b >> i) & 1;
        if (x == 0 && y == 0) {
            return 0;
        }
        if (x == 0 && y == 1) {
            if (prg == i - 1) {
                cg += 1;
            }
            else {
                res = (res * comb(cg)) % md;
                cg = 1;
            }
            prg = i;
        }
        if (x == 1 && y == 1) {
            bad.push_back(i);
        }
    }

    if (bad.size() % 2 == 1) {
        return 0;
    }

    while (bad.size()) {
        int x = bad.back();
        bad.pop_back();

        int y = bad.back();
        bad.pop_back();

        if (y + 1 != x) {
            return 0;
        }
    }

    return (res * comb(cg)) % md;
}

vector<vector<int>>mt;

vector<vector<int>>mult(vector<vector<int>> a, vector<vector<int>>b) {
    vector<vector<int>>o(a.size(), vector<int>(b.size()));
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            o[i][j] = 0;
            for (int k = 0; k < n; k++) {
                o[i][j] += a[i][k] * b[k][j];
                o[i][j] %= md;
            }
        }
    }
    return o;
}
vector<vector<int>> fst_pw(vector<vector<int>> mt, int m) {
    if (m == 1) {
        return mt;
    }
    if (m % 2 == 0) {
        return fst_pw(mult(mt, mt), m / 2);
    }
    return mult(fst_pw(mt, m - 1), mt);
}

void Solve() {
    int n, m; cin >> n >> m;
    int k = pow(2, n);
    mt = vector<vector<int>>(k, vector<int>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            mt[i][j] = cnt(j, i, n);
        }
    }
    cout << fst_pw(mt, m)[k - 1][k - 1];
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
