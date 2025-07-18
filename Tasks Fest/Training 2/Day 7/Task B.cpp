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

const int inf = 1e18;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

pair<int, int> Get(vector<int>& dp, string& s, char c, int id) {
    int counter = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] != 'n' && s[i] != 'a' && s[i] != 'r' && s[i] != 'e' && s[i] != 'k') {
            continue;
        }

        if (s[i] == c) {
            if (c == 'n') {
                c = 'a';
                counter += 1;
            }
            else if (c == 'a') {
                c = 'r';
                counter += 1;
            }
            else if (c == 'r') {
                c = 'e';
                counter += 1;
            }
            else if (c == 'e') {
                c = 'k';
                counter += 1;
            }
            else if (c == 'k') {
                c = 'n';
                counter += 1;
            }
        }
        else {
            counter -= 1;
        }
    }

    if (c == 'n') {
        return { counter, 0 };
    }
    else if (c == 'a') {
        return { counter, 1 };
    }
    else if (c == 'r') {
        return { counter, 2 };
    }
    else if (c == 'e') {
        return { counter, 3 };
    }
    else if (c == 'k') {
        return { counter, 4 };
    }
}

void Upd(vector<int>& dp, string& s) {
    pair<int, int> upd_n = Get(dp, s, 'n', 0);
    pair<int, int> upd_a = Get(dp, s, 'a', 1);
    pair<int, int> upd_r = Get(dp, s, 'r', 2);
    pair<int, int> upd_e = Get(dp, s, 'e', 3);
    pair<int, int> upd_k = Get(dp, s, 'k', 4);

    vector<int> ndp = dp;

    ndp[upd_n.second] = max(ndp[upd_n.second], dp[0] + upd_n.first);
    ndp[upd_a.second] = max(ndp[upd_a.second], dp[1] + upd_a.first);
    ndp[upd_r.second] = max(ndp[upd_r.second], dp[2] + upd_r.first);
    ndp[upd_e.second] = max(ndp[upd_e.second], dp[3] + upd_e.first);
    ndp[upd_k.second] = max(ndp[upd_k.second], dp[4] + upd_k.first);

    dp = ndp;
}

void Solve() {
    int n, m; cin >> n >> m;

    vector<int> dp(5);
    dp[0] = 0;
    dp[1] = -inf;
    dp[2] = -inf;
    dp[3] = -inf;
    dp[4] = -inf;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        Upd(dp, s);
    }

    int ans = 0;
    for (int i = 0; i < 5; i++) {
        ans = max(ans, dp[i] - 2 * i);
    }
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
