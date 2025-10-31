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

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

int o(Point A, Point B, Point C) {
    int val = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    if (val == 0) return 0;
    if (val > 0) return 1;
    if (val < 0) return 2;
}

bool c(Point p, Point q, Point r) {
    if (o(p, q, r) == 0) {
        if (r.x <= max(p.x, q.x) && r.x >= min(p.x, q.x) && r.y <= max(p.y, q.y) && r.y >= min(p.y, q.y)) return true;
    }
    return false;
}

bool f(Point A, Point B, Point C, Point D) {
    if (c(A, B, C)) return true;
    if (c(A, B, D)) return true;
    if (c(C, D, A)) return true;
    if (c(C, D, B)) return true;

    return false;
}

void Solve() {
    int xa, ya, xb, yb, l, n; cin >> xa >> ya >> xb >> yb >> l >> n;
    vector<Point> v;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v.push_back(Point(x, y));
    }
    int m; cin >> m;
    vector<pair<Point, Point>> b;
    for (int i = 0; i < m; i++) {
        int x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
        b.push_back({ Point(x0, y0), Point(x1, y1) });
    }

    for (auto bi : b) {
        if (c(bi.first, bi.second, Point(xa, ya))) {
            cout << -1;
            return;
        }
    }
    for (auto bi : b) {
        if (c(bi.first, bi.second, Point(xb, yb))) {
            cout << -1;
            return;
        }
    }

    vector<vector<int>> DIST(2001, vector<int>(2001, -1));

    queue<Point> q; q.push(Point(xa, ya));
    DIST[xa + 1000][ya + 1000] = 0;

    while (q.size() > 0) {
        Point pt = q.front();
        q.pop();

        int z = DIST[pt.x + 1000][pt.y + 1000];
        if (z >= l) continue;

        for (Point vi : v) {
            Point next(pt.x + vi.x, pt.y + vi.y);
            if (next.x < -1000 || next.x > 1000 || next.y < -1000 || next.y > 1000) continue;
            bool F = true;
            for (auto bi : b) {
                if (f(pt, next, bi.first, bi.second)) {
                    F = false; break;
                }
            }
            if (F == false) continue;
            if (DIST[next.x + 1000][next.y + 1000] == -1) {
                DIST[next.x + 1000][next.y + 1000] = z + 1;
                q.push(next);
            }
        }
    }

    cout << DIST[xb + 1000][yb + 1000];
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
