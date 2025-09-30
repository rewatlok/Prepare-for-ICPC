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

int get(int l, int r, vector<int>& ps) {
    if (l > r) {
        return 0;
    }
    else {
        if (l == 0) {
            return ps[r];
        }
        else {
            return ps[r] - ps[l - 1];
        }
    }
}

vector<pair<int, int>> get(vector<int> a, int f) {
    vector<pair<int, int>> ans;

    if (f == 3) {
        int s = 0;
        for (int i = 0; i < a.size(); i++) {
            s += a[i];
            ans.push_back({ s, i + 1 });
        }
    }
    else if (f == 1) {
        int s = 0;
        for (int i = a.size() - 1; i >= 0; i--) {
            s += a[i];
            ans.push_back({ s, a.size() - i });
        }
    }
    else {
        vector<int> ps;
        int s = 0;
        for (int i = 0; i < a.size(); i++) {
            s += a[i];
            ps.push_back(s);
        }

        vector<int> mn(a.size() + 1, inf);

        for (int i = 0; i <= a.size(); i++) {
            for (int j = 0; j <= a.size(); j++) {
                if (i + j <= a.size()) {
                    mn[i + j] = min(mn[i + j], get(0, i - 1, ps) + get(a.size() - j, a.size() - 1, ps));
                }
            }
        }

        for (int i = 1; i <= a.size(); i++) {
            ans.push_back({ mn[i], i });
        }
    }

    return ans;
}

void Solve() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            k -= 1;
        }
    }

    vector<vector<int>> C;
    vector<int> c;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            c.push_back(a[i]);
        }
        else {
            if (c.size() > 0) {
                C.push_back(c);
            }
            c.clear();
        }
    }
    if (c.size() > 0) {
        C.push_back(c);
    }
    c.clear();

    vector<vector<pair<int, int>>> Q;
    for (int i = 0; i < C.size(); i++) {
        if (i == 0) {
            if (a[0] != 0) {
                Q.push_back(get(C[i], 1));
            }
            else {
                Q.push_back(get(C[i], 2));
            }
        }
        else if (i == C.size() - 1) {
            if (a[a.size() - 1] != 0) {
                Q.push_back(get(C[i], 3));
            }
            else {
                Q.push_back(get(C[i], 2));
            }
        }
        else {
            Q.push_back(get(C[i], 2));
        }
    }

    vector<pair<int, int>> X = { {0, 0} };
    for (int i = 0; i < Q.size(); i++) {
        for (auto qi : Q[i]) {
            X.push_back(qi);
        }
    }

    vector<vector<int>> DP(k + 1);
    for (int i = 0; i < k + 1; i++) {
        DP[i].resize(X.size());
    }
    int K = DP.size();
    int N = DP[0].size();
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            DP[i][j] = inf;
        }
    }
    for (int i = 0; i < N; i++) {
        DP[0][i] = 0;
    }

    for (int i = 1; i < K; i++) {
        for (int j = 1; j < N; j++) {
            int p = inf;
            if (i - X[j].ss >= 0 && j - X[j].ss >= 0) {
                p = DP[i - X[j].ss][j - X[j].ss] + X[j].ff;
            }
            DP[i][j] = min({ DP[i][j], DP[i][j - 1], p });
        }
    }

    cout << DP[K - 1][N - 1] << '\n';
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
