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

struct SplayNode {
    int value;

    SplayNode* left;
    SplayNode* right;

    SplayNode* parent;
    SplayNode* path_parent;

    SplayNode(int value) :
        value(value),
        left(nullptr), right(nullptr),
        parent(nullptr), path_parent(nullptr) {}

    void rotate() {
        SplayNode* p = parent;
        bool isRightChild = (p->right == this);

        if (p->parent) {
            if (p->parent->right == p) {
                p->parent->right = this;
            }
            else {
                p->parent->left = this;
            }
            parent = p->parent;
        }
        else {
            parent = nullptr;
        }

        if (isRightChild) {
            p->right = left;
            if (left) {
                left->parent = p;
            }
            left = p;
        }
        else {
            p->left = right;
            if (right) {
                right->parent = p;
            }
            right = p;
        }

        p->parent = this;
        path_parent = p->path_parent;
    }

    void splay() {
        while (parent) {
            if (parent->parent) {
                if ((parent->right == this) == (parent->parent->right == parent)) {
                    parent->rotate();
                }
                else {
                    rotate();
                }
            }
            rotate();
        }
    }
};

class LinkCutTree {
public:
    LinkCutTree(int size) : nodes(size) {
        for (int i = 0; i < size; ++i) {
            nodes[i] = new SplayNode(i);
        }
    }

    ~LinkCutTree() {
        for (SplayNode* node : nodes) {
            delete node;
        }
    }

    void link(int par_idx, int child_idx) {
        SplayNode* par = nodes[par_idx];
        SplayNode* child = nodes[child_idx];

        access(child);
        access(par);

        child->left = par;
        if (par) {
            par->parent = child;
        }
    }

    void cut(int node_idx) {
        SplayNode* node = nodes[node_idx];
        access(node);

        if (node->left) {
            node->left->parent = nullptr;
            node->left = nullptr;
        }
    }

    SplayNode* find_root(int node_idx) {
        SplayNode* node = nodes[node_idx];
        access(node);

        while (node->left) {
            node = node->left;
        }

        access(node);
        return node;
    }

    int lca(int u_idx, int v_idx) {
        SplayNode* u = nodes[u_idx];
        SplayNode* v = nodes[v_idx];

        if (find_root(u_idx) != find_root(v_idx)) {
            return -1;
        }

        access(u);
        SplayNode* lca_node = access(v);

        if (lca_node) {
            return lca_node->value;
        }
        else {
            return -1;
        }
    }

private:
    vector<SplayNode*> nodes;

    SplayNode* access(SplayNode* node) {
        node->splay();

        if (node->right) {
            node->right->path_parent = node;
            node->right->parent = nullptr;
        }

        node->right = nullptr;
        SplayNode* par = node;

        while (node->path_parent) {
            par = node->path_parent;
            par->splay();

            if (par->right) {
                par->right->path_parent = par;
                par->right->parent = nullptr;
            }

            par->right = node;

            if (node) {
                node->parent = par;
            }

            node->path_parent = nullptr;
            node->splay();
        }

        return par;
    }
};

void Solve() {
    int n; cin >> n;

    LinkCutTree lct(n);

    for (int i = 1; i <= n; ++i) {
        string op; int a, b;
        cin >> op >> a >> b;

        if (op == "ADD") {
            lct.link(a, b);
        }
        else if (op == "GET") {
            cout << lct.lca(a, b) << '\n';
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
