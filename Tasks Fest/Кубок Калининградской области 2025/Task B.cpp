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

const int MAXN = 100005;

int a[MAXN];
int b[MAXN];
int s[MAXN];
int n, q;

struct NODE {
    int sa = 0;
    int sb = 0;
    int sbi = 0;
    int ansb = 0;
    int plen = 0;
    int slen = 0;
    int pbs = 0;
    int sbs = 0;
};

struct Node {
    NODE info;
    NODE flipped_info;
    int tl = 0;
    bool lf = false;
};

Node tree[4 * MAXN];

NODE merge(NODE& left, NODE& right, int left_len, int right_len) {
    if (left_len == 0) {
        return right;
    }

    if (right_len == 0) {
        return left;
    }

    NODE res;

    res.sa = left.sa + right.sa;

    res.sb = left.sb + right.sb;

    res.sbi = left.sbi + right.sbi;

    res.ansb = left.ansb + right.ansb;
    if (left.slen > 0 && right.plen > 0) {
        res.ansb += left.slen * right.pbs;
    }

    res.plen = left.plen;
    if (left.plen == left_len) {
        res.plen += right.plen;
    }

    res.slen = right.slen;
    if (right.slen == right_len) {
        res.slen += left.slen;
    }

    res.pbs = left.pbs;
    if (left.plen == left_len) {
        res.pbs += right.pbs;
    }

    res.sbs = right.sbs;
    if (right.slen == right_len) {
        res.sbs += left.sbs;
    }

    return res;
}

void flip(int v) {
    swap(tree[v].info, tree[v].flipped_info);
    tree[v].lf = (tree[v].lf + 1) % 2;
}

void push(int v) {
    if (tree[v].lf && v * 2 + 1 < 4 * MAXN) {
        flip(2 * v);
        flip(2 * v + 1);
        tree[v].lf = false;
    }
}

void build(int v, int tl, int tr) {
    tree[v].tl = tr - tl + 1;

    if (tl == tr) {
        NODE one_info = { a[tl], b[tl], b[tl] * tl, b[tl], 1, 1, b[tl], b[tl] };
        NODE zero_info = { 0, 0, 0, 0, 0, 0, 0, 0 };

        if (s[tl] == 1) {
            tree[v].info = one_info;
            tree[v].flipped_info = zero_info;
        }
        else {
            tree[v].info = zero_info;
            tree[v].flipped_info = one_info;
        }
    }
    else {
        build(2 * v, tl, (tl + tr) / 2);
        build(2 * v + 1, (tl + tr) / 2 + 1, tr);

        tree[v].info = merge(tree[2 * v].info, tree[2 * v + 1].info, tree[2 * v].tl, tree[2 * v + 1].tl);
        tree[v].flipped_info = merge(tree[2 * v].flipped_info, tree[2 * v + 1].flipped_info, tree[2 * v].tl, tree[2 * v + 1].tl);
    }
}

void update(int v, int tl, int tr, int l, int r) {
    push(v);

    if (l > r) {
        return;
    }

    push(v);

    if (l == tl && r == tr) {
        flip(v);
        return;
    }

    push(v);

    update(2 * v, tl, (tl + tr) / 2, l, min(r, (tl + tr) / 2));
    update(2 * v + 1, (tl + tr) / 2 + 1, tr, max(l, (tl + tr) / 2 + 1), r);

    tree[v].info = merge(tree[2 * v].info, tree[2 * v + 1].info, tree[2 * v].tl, tree[2 * v + 1].tl);
    tree[v].flipped_info = merge(tree[2 * v].flipped_info, tree[2 * v + 1].flipped_info, tree[2 * v].tl, tree[2 * v + 1].tl);
}

NODE query(int v, int tl, int tr, int l, int r) {
    push(v);

    if (l > r) {
        return NODE();
    }

    push(v);

    if (l == tl && r == tr) {
        return tree[v].info;
    }

    push(v);

    NODE left_res = query(2 * v, tl, (tl + tr) / 2, l, min(r, (tl + tr) / 2));
    NODE right_res = query(2 * v + 1, (tl + tr) / 2 + 1, tr, max(l, (tl + tr) / 2 + 1), r);

    int llen = min(r, (tl + tr) / 2) - l + 1;
    if (llen < 0) {
        llen = 0;
    }

    int rlen = r - max(l, (tl + tr) / 2 + 1) + 1;
    if (rlen < 0) {
        rlen = 0;
    }

    return merge(left_res, right_res, llen, rlen);
}

void Solve() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    build(1, 1, n);

    for (int k = 0; k < q; k++) {
        int type, l, r; cin >> type >> l >> r;

        if (type == 1) {
            update(1, 1, n, l, r);
        }
        else {
            int ans = 0;

            NODE nd = query(1, 1, n, l, r);
            ans += nd.sa;

            int slen = 0;
            if (l > 1) {
                slen = query(1, 1, n, 1, l - 1).slen;
            }

            if (slen == 0) {
                ans += nd.ansb;
            }
            else {
                int plen = query(1, 1, n, l, n).plen;

                if (l <= min(r, l + plen - 1)) {
                    NODE qr = query(1, 1, n, l, min(r, l + plen - 1));
                    ans += qr.sbi - (l - 1) * qr.sb;
                }

                if (min(r, l + plen - 1) < r) {
                    NODE qr = query(1, 1, n, min(r, l + plen - 1) + 1, r);
                    ans += qr.ansb;
                }
            }

            cout << ans << '\n';
        }
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
