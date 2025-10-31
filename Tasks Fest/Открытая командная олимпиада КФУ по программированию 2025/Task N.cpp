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

int md1 = 1200720071;
int md2 = 1000000007;
int pw1[100005];
int pw2[100005];

int H(int x, int y, int ln, vector<vi>& hsh1, vector<vi>& hsh2) {
    int hA = (-hsh1[x][y] * pw1[ln] + hsh1[x][y + ln] + md1 * md1) % md1;
    int hB = (-hsh2[x][y] * pw2[ln] + hsh2[x][y + ln] + md2 * md2) % md2;
    return hA * md2 + hB;
}

void Solve() {
    int n, m; cin >> n >> m;

    pw1[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i <= m + 1; i++) {
        pw1[i] = pw1[i - 1] * 27 % md1;
    }
    for (int i = 1; i <= m + 1; i++) {
        pw2[i] = pw2[i - 1] * 27 % md2;
    }

    vector<string> good, a;
    good.resize(n * 2);
    a.resize(n * 2);

    for (int i = 0; i < n; i++) {
        string x; cin >> x;
        a[i] = x + x;
    }
    for (int i = 0; i < n; i++) {
        string x; cin >> x;
        good[i] = x + x;
    }
    for (int i = n; i < n * 2; i++) {
        a[i] = a[i - n];
        good[i] = good[i - n];
    }

    vector<vi> ha1(n * 2);
    vector<vi> hg1_(n * 2);
    vector<vi> ha2(n * 2);
    vector<vi> hg2_(n * 2);

    for (int i = 0; i < n * 2; i++) {
        ha1[i].assign(m * 2 + 1, 0);
        hg1_[i].assign(m * 2 + 1, 0);
        for (int j = 1; j < m * 2 + 1; j++) {
            ha1[i][j] = (ha1[i][j - 1] * 27 + (a[i][j - 1] - 'a' + 1)) % md1;
            hg1_[i][j] = (hg1_[i][j - 1] * 27 + (good[i][j - 1] - 'a' + 1)) % md1;
        }
    }

    for (int i = 0; i < n * 2; i++) {
        ha2[i].assign(m * 2 + 1, 0);
        hg2_[i].assign(m * 2 + 1, 0);
        for (int j = 1; j < m * 2 + 1; j++) {
            ha2[i][j] = (ha2[i][j - 1] * 27 + (a[i][j - 1] - 'a' + 1)) % md2;
            hg2_[i][j] = (hg2_[i][j - 1] * 27 + (good[i][j - 1] - 'a' + 1)) % md2;
        }
    }

    int ax = -1;
    int ay = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool f = true;
            for (int k = 0; k < n; k++) {
                if (H(k + i, j, m, ha1, ha2) != H(k, 0, m, hg1_, hg2_)) {
                    f = false;
                    break;
                }
            }
            if (f == true) {
                cout << i << ' ' << j << '\n';
                return;
            }
        }
    }

    cout << -1;
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
