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

struct DSU {
    vector<int> head;
    vector<int> rang;
    int components;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        components = n;
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return head[x] = Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] > rang[y]) {
            swap(x, y);
        }

        head[x] = y;

        if (rang[x] == rang[y]) {
            ++rang[y];
        }

        --components;

        return true;
    }
};

void Solve() {
    int n, m; cin >> n >> m;
    vector<tuple<int, int, long long>> edges(m);

    for (int i = 0; i < m; ++i) {
        int u, v; long long w;
        cin >> u >> v >> w;

        edges[i] = { w, u, v };
    }

    DSU dsu(n);
    long long ans = 0;

    while (dsu.components > 1) {
        vector<int> cheapest(n, -1);
        bool Flag = false;

        for (int i = 0; i < m; ++i) {
            long long w = get<0>(edges[i]);
            int u = get<1>(edges[i]);
            int v = get<2>(edges[i]);

            int set_u = dsu.Find(u);
            int set_v = dsu.Find(v);

            if (set_u != set_v) {
                if (cheapest[set_u] == -1 || get<0>(edges[cheapest[set_u]]) > w) {
                    cheapest[set_u] = i;
                }
                if (cheapest[set_v] == -1 || get<0>(edges[cheapest[set_v]]) > w) {
                    cheapest[set_v] = i;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (cheapest[i] != -1) {
                long long w = get<0>(edges[cheapest[i]]);
                int u = get<1>(edges[cheapest[i]]);
                int v = get<2>(edges[cheapest[i]]);

                if (dsu.Union(u, v)) {
                    ans += w;
                    Flag = true;
                }
            }
        }

        if (Flag == false) {
            break;
        }
    }

    if (dsu.components == 1) {
        cout << ans;
    }
    else {
        cout << "NON-CONNECTED";
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
