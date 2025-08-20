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

struct PersistentImplicitSegmentTree {
    struct Node {
        int sum;
        Node* left;
        Node* right;

        Node() : sum(0), left(nullptr), right(nullptr) {}
        Node(Node* left, Node* right, int sum) : left(left), right(right), sum(sum) {}
    };

    PersistentImplicitSegmentTree(int size) : n(size) {
        roots.push_back(nullptr);
    }

    void change(int pos, int val) {
        Current_root = updatePoint(Current_root, 0, n - 1, pos, val);
    }

    int query_v(int version, int l, int r) {
        return queryRange(roots[version], 0, n - 1, l, r);
    }

    Node* Current_root = nullptr;
    vector<Node*> roots;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            return new Node(nullptr, nullptr, val);
        }

        int mid = l + (r - l) / 2;
        Node* newNode = new Node(*node);

        if (pos <= mid) {
            newNode->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            newNode->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

        newNode->sum = (newNode->left ? newNode->left->sum : 0) + (newNode->right ? newNode->right->sum : 0);

        return newNode;
    }

    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return 0;
        }

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return node->sum;
        }

        int mid = l + (r - l) / 2;

        int leftSum = queryRange(node->left, l, mid, const_l, const_r);
        int rightSum = queryRange(node->right, mid + 1, r, const_l, const_r);

        return leftSum + rightSum;
    }
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, int> last;
    for (int i = 0; i < n; i++) {
        last[a[i]] = -1;
    }

    map<int, int> last_last;
    for (int i = 0; i < n; i++) {
        last_last[a[i]] = -1;
    }

    PersistentImplicitSegmentTree ST(inf);
    for (int i = 0; i < n; i++) {
        if (last[a[i]] == -1 && last_last[a[i]] == -1) {
            ST.change(i, 1);

            last[a[i]] = i;
        }
        else if (last[a[i]] != -1 && last_last[a[i]] == -1) {
            ST.change(i, 1);
            ST.change(last[a[i]], -1);

            last_last[a[i]] = last[a[i]];
            last[a[i]] = i;
        }
        else {
            ST.change(i, 1);
            ST.change(last[a[i]], -1);
            ST.change(last_last[a[i]], 0);

            last_last[a[i]] = last[a[i]];
            last[a[i]] = i;
        }

        ST.roots.push_back(ST.Current_root);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;

        --l;
        --r;

        cout << ST.query_v(r + 1, l, r) << endl;
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
