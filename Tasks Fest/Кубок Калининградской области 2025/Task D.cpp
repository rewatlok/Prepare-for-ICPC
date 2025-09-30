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

int sm(int l, int r, vector<int>& ps) {
    if (l == 0) {
        return ps[r];
    }
    else {
        return ps[r] - ps[l - 1];
    }
}

int get(vector<int>& a) {
    vector<int> ps;
    int s = 0;
    for (int i = 0; i < a.size(); i++) {
        s += a[i];
        ps.push_back(s);
    }

    int ans = 0;

    for (int i = 0; i < a.size(); i++) {
        int cans = 0;

        int dl = i;
        int dr = a.size() - 1 - i;

        if (dl % 2 == 1) {
            cans += a[i - dl / 2 - 1] / 2;
        }
        if (dr % 2 == 1) {
            cans += a[i + dr / 2 + 1] / 2;
        }

        int l = i - dl / 2;
        int r = i + dr / 2;

        cans += sm(l, r, ps);

        ans = max(ans, cans);
    }

    return ans;
}

void Solve() {
    int n, k; cin >> n >> k;

    vector<bool> ok(n, true);
    for (int i = 0; i < k; i++) {
        int t; cin >> t; ok[t - 1] = false;
    }

    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    vector<vector<int>> ALL;

    vector<int> c;
    bool f = false;
    for (int i = 0; i < n; i++) {
        if (ok[i] == false) {
            f = true;
        }
        if (f == true) {
            if (ok[i] == true) {
                c.push_back(A[i]);
            }
            else {
                if (c.size() > 0) {
                    ALL.push_back(c);
                    c.clear();
                }
            }
            ok[i] = false;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ok[i] == true) {
            c.push_back(A[i]);
        }
    }
    if (c.size() > 0) {
        ALL.push_back(c);
        c.clear();
    }

    vector<int> Q;
    for (int i = 0; i < ALL.size(); i++) {
        int a = get(ALL[i]);
        int s = 0;
        for (int z : ALL[i]) {
            s += z;
        }
        int b = s - a;
        Q.push_back(a);
        Q.push_back(b);
    }

    sort(all(Q));
    reverse(all(Q));

    int S = 0;
    for (int i = 0; i < n; i++) {
        S += A[i];
    }

    int CS = 0;
    for (int i = 0; i < Q.size(); i++) {
        CS += Q[i];
        if (CS > S / 2) {
            cout << i + 1;
            return;
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
