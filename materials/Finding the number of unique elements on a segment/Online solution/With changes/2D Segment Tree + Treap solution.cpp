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

class SegmentTree2D {
private:
    struct Node {
        map<int, Node*> children;
        int value = 0;
    };

    Node* root;

    void update(Node*& node, int x, int y, int val, int xLeft, int xRight, int yLeft, int yRight) {
        if (!node) {
            node = new Node();
        }

        if (xLeft == xRight && yLeft == yRight) {
            node->value += val;
            return;
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        if (x <= midX) {
            if (y <= midY) {
                update(node->children[0], x, y, val, xLeft, midX, yLeft, midY);
            }
            else {
                update(node->children[1], x, y, val, xLeft, midX, midY + 1, yRight);
            }
        }
        else {
            if (y <= midY) {
                update(node->children[2], x, y, val, midX + 1, xRight, yLeft, midY);
            }
            else {
                update(node->children[3], x, y, val, midX + 1, xRight, midY + 1, yRight);
            }
        }

        node->value = 0;
        for (auto& [_, child] : node->children) {
            if (child) {
                node->value += child->value;
            }
        }
    }

    int query(Node* node, int x1, int y1, int x2, int y2, int xLeft, int xRight, int yLeft, int yRight) {
        if (!node || x1 > xRight || x2 < xLeft || y1 > yRight || y2 < yLeft) {
            return 0;
        }

        if (x1 <= xLeft && xRight <= x2 && y1 <= yLeft && yRight <= y2) {
            return node->value;
        }

        int midX = (xLeft + xRight) / 2;
        int midY = (yLeft + yRight) / 2;

        int sum = 0;
        sum += query(node->children[0], x1, y1, x2, y2, xLeft, midX, yLeft, midY);
        sum += query(node->children[1], x1, y1, x2, y2, xLeft, midX, midY + 1, yRight);
        sum += query(node->children[2], x1, y1, x2, y2, midX + 1, xRight, yLeft, midY);
        sum += query(node->children[3], x1, y1, x2, y2, midX + 1, xRight, midY + 1, yRight);

        return sum;
    }

public:
    SegmentTree2D() { root = nullptr; }

    void update(int x, int y, int value) {
        update(root, x, y, value, 0, inf, 0, inf);
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(root, x1, y1, x2, y2, 0, inf, 0, inf);
    }
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class Treap {
public:
    struct TreapNode {
        int value, priority;
        TreapNode* left, * right;
        int size;

        TreapNode(int v) :
            value(v), priority(rng()),
            left(nullptr), right(nullptr),
            size(1) {
        }
    };

    Treap() : root(nullptr) {}

    void insert(int value) {
        insert(root, new TreapNode(value));
    }

    void remove(int value) {
        remove(root, value);
    }

    int Count_L(int x) {
        return Count_L(root, x);
    }

    int Count_R(int x) {
        return Count_R(root, x);
    }

private:
    TreapNode* root;

    int getSize(TreapNode* node) {
        return node ? node->size : 0;
    }

    void updateSize(TreapNode* node) {
        if (node) {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

    void split(TreapNode* node, int key, TreapNode*& left, TreapNode*& right) {
        if (!node) {
            left = right = nullptr;
            return;
        }

        if (node->value <= key) {
            split(node->right, key, node->right, right);
            left = node;
        }
        else {
            split(node->left, key, left, node->left);
            right = node;
        }

        updateSize(node);
    }

    void merge(TreapNode*& node, TreapNode* left, TreapNode* right) {
        if (!left || !right) {
            node = left ? left : right;
            return;
        }

        if (left->priority > right->priority) {
            merge(left->right, left->right, right);
            node = left;
        }
        else {
            merge(right->left, left, right->left);
            node = right;
        }

        updateSize(node);
    }

    void insert(TreapNode*& node, TreapNode* newNode) {
        if (!node) {
            node = newNode;
            return;
        }

        if (newNode->priority > node->priority) {
            split(node, newNode->value, newNode->left, newNode->right);
            node = newNode;
        }
        else {
            insert(newNode->value <= node->value ? node->left : node->right, newNode);
        }

        updateSize(node);
    }

    void remove(TreapNode*& node, int value) {
        if (!node) {
            return;
        }

        if (node->value == value) {
            TreapNode* temp = node;
            merge(node, node->left, node->right);
            delete temp;
        }
        else {
            remove(value < node->value ? node->left : node->right, value);
        }

        updateSize(node);
    }

    int Count_L(TreapNode* node, int x) {
        if (!node) {
            return 0;
        }

        if (node->value <= x) {
            return 1 + getSize(node->left) + Count_L(node->right, x);
        }
        else {
            return Count_L(node->left, x);
        }
    }

    int Count_R(TreapNode* node, int x) {
        if (!node) {
            return 0;
        }

        if (node->value >= x) {
            return 1 + getSize(node->right) + Count_R(node->left, x);
        }
        else {
            return Count_R(node->right, x);
        }
    }
};

class SegmentTree {
public:
    SegmentTree(const vector<int> a) {
        n = 1;
        while (n < (int)a.size()) {
            n <<= 1;
        }
        tree.resize(2 * n);
        build(a, 1, 0, n - 1);
    }

    void update(int pos, int W, int U) {
        update(1, 0, n - 1, pos, W, U);
    }

    int query_L(int l, int r, int x) {
        return query_L(1, 0, n - 1, l, r, x);
    }

    int query_R(int l, int r, int x) {
        return query_R(1, 0, n - 1, l, r, x);
    }

private:
    int n;
    vector<Treap> tree;

    void build(const vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            if (tl < (int)a.size()) {
                tree[v].insert(a[tl]);
            }
        }
        else {
            int tm = (tl + tr) / 2;

            build(a, 2 * v, tl, tm);
            build(a, 2 * v + 1, tm + 1, tr);

            for (int i = tl; i <= tr; ++i) {
                if (i < (int)a.size()) {
                    tree[v].insert(a[i]);
                }
            }
        }
    }

    void update(int v, int tl, int tr, int pos, int W, int U) {
        if (tl == tr) {
            tree[v].remove(W);
            tree[v].insert(U);
        }
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(2 * v, tl, tm, pos, W, U);
            }
            else {
                update(2 * v + 1, tm + 1, tr, pos, W, U);
            }
            tree[v].remove(W);
            tree[v].insert(U);
        }
    }

    int query_L(int v, int tl, int tr, int l, int r, int x) {
        if (l > r || tl > r || tr < l) {
            return 0;
        }

        if (tl >= l && tr <= r) {
            return tree[v].Count_L(x);
        }

        int tm = (tl + tr) / 2;

        return query_L(2 * v, tl, tm, l, min(r, tm), x) +
            query_L(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x);
    }

    int query_R(int v, int tl, int tr, int l, int r, int x) {
        if (l > r || tl > r || tr < l) {
            return 0;
        }

        if (tl >= l && tr <= r) {
            return tree[v].Count_R(x);
        }

        int tm = (tl + tr) / 2;

        return query_R(2 * v, tl, tm, l, min(r, tm), x) +
            query_R(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x);
    }
};

class Treap_to_Find {
public:
    struct Node {
        int x, y;

        int count;
        int size;

        Node* left;
        Node* right;

        Node(int x, int y) :
            x(x), y(y), count(1), size(1),
            left(nullptr), right(nullptr) {
        }
    };

    Treap_to_Find() : root(nullptr) {}

    void Add(int x) {
        root = insert(root, x, rand());
    }

    void Del(int x) {
        root = delete_key(root, x);
    }

    bool Find(int x) {
        return exists(root, x);
    }

    int Find_ll(int x) {
        ans_ll = -1;
        find_ll(root, x);
        return ans_ll;
    }

    int Find_lr(int x) {
        ans_lr = -1;
        find_lr(root, x);
        return ans_lr;
    }

    int Find_rl(int x) {
        ans_rl = -1;
        find_rl(root, x);
        return ans_rl;
    }

    int Find_rr(int x) {
        ans_rr = -1;
        find_rr(root, x);
        return ans_rr;
    }

private:
    Node* root;
    int ans_ll, ans_lr, ans_rl, ans_rr;

    int get_size(Node* a) {
        return a ? a->size : 0;
    }

    void update_size(Node* a) {
        if (a) {
            a->size = get_size(a->left) + get_size(a->right) + a->count;
        }
    }

    pair<Node*, Node*> split(Node* a, int k) {
        if (!a) {
            return { nullptr, nullptr };
        }
        if (a->x < k) {
            pair<Node*, Node*> lr = split(a->right, k);
            a->right = lr.first;
            update_size(a);
            return { a, lr.second };
        }
        else {
            pair<Node*, Node*> lr = split(a->left, k);
            a->left = lr.second;
            update_size(a);
            return { lr.first, a };
        }
    }

    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->y > b->y) {
            a->right = merge(a->right, b);
            update_size(a);
            return a;
        }
        else {
            b->left = merge(a, b->left);
            update_size(b);
            return b;
        }
    }

    Node* insert(Node* a, int x, int y) {
        pair<Node*, Node*> lr = split(a, x);
        Node* l = lr.first;
        Node* r = lr.second;

        if (l && l->x == x) {
            l->count++;
            update_size(l);
            return merge(l, r);
        }

        Node* new_node = new Node(x, y);
        return merge(merge(l, new_node), r);
    }

    Node* delete_key(Node* a, int x) {
        if (!a) return nullptr;

        if (a->x == x) {
            if (a->count > 1) {
                a->count--;
                update_size(a);
                return a;
            }
            else {
                return merge(a->left, a->right);
            }
        }

        if (x < a->x) {
            a->left = delete_key(a->left, x);
        }
        else {
            a->right = delete_key(a->right, x);
        }

        update_size(a);
        return a;
    }

    bool exists(Node* a, int x) {
        if (!a) {
            return false;
        }
        if (a->x == x) {
            return true;
        }
        if (x < a->x) {
            return exists(a->left, x);
        }
        else {
            return exists(a->right, x);
        }
    }

    void find_ll(Node* a, int x) {
        if (!a) return;
        if (a->x < x) {
            ans_ll = a->x;
            find_ll(a->right, x);
        }
        else {
            find_ll(a->left, x);
        }
    }

    void find_lr(Node* a, int x) {
        if (!a) return;
        if (a->x <= x) {
            ans_lr = a->x;
            find_lr(a->right, x);
        }
        else {
            find_lr(a->left, x);
        }
    }

    void find_rl(Node* a, int x) {
        if (!a) return;
        if (a->x >= x) {
            ans_rl = a->x;
            find_rl(a->left, x);
        }
        else {
            find_rl(a->right, x);
        }
    }

    void find_rr(Node* a, int x) {
        if (!a) return;
        if (a->x > x) {
            ans_rr = a->x;
            find_rr(a->left, x);
        }
        else {
            find_rr(a->right, x);
        }
    }
};

void Solve() {
    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> base(n);
    for (int i = 0; i < n; i++) {
        base[i] = 0;
    }

    SegmentTree LAST(base);

    map<int, int> last_id;
    for (int i = 0; i < n; i++) {
        last_id[a[i]] = -1;
    }

    vector<int> last(n);
    for (int i = 0; i < n; i++) {
        LAST.update(i, 0, last_id[a[i]]);

        last[i] = 1'000'000 - last_id[a[i]];
        last_id[a[i]] = i;
    }

    SegmentTree FUTURE(base);

    map<int, int> future_id;
    for (int i = 0; i < n; i++) {
        future_id[a[i]] = n;
    }

    vector<int> future(n);
    for (int i = n - 1; i >= 0; i--) {
        FUTURE.update(i, 0, future_id[a[i]]);

        future[i] = future_id[a[i]];
        future_id[a[i]] = i;
    }

    vector<int> X;
    for (int i = 0; i < n; i++) {
        X.push_back(last[i]);
    }

    vector<int> Y;
    for (int i = 0; i < n; i++) {
        Y.push_back(future[i]);
    }

    vector<pair<int, int>> points;
    for (int i = 0; i < n; i++) {
        points.push_back({ X[i], Y[i] });
    }

    SegmentTree2D ST;
    for (auto p : points) {
        ST.update(p.first, p.second, 1);
    }

    map<int, Treap_to_Find> POSITIONS;
    for (int i = 0; i < n; i++) {
        POSITIONS[a[i]].Add(i);
    }
    for (int i = 0; i < n; i++) {
        if (POSITIONS[a[i]].Find(-1) == false) {
            POSITIONS[a[i]].Add(-1);
        }
        if (POSITIONS[a[i]].Find(n) == false) {
            POSITIONS[a[i]].Add(n);
        }
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string Type; cin >> Type;

        if (Type == "!") {
            int pos, val; cin >> pos >> val;

            --pos;

            if (a[pos] == val) {
                continue;
            }

            if (future[pos] != n) {
                LAST.update(future[pos], pos, 1'000'000 - last[pos]);
                ST.update(last[future[pos]], future[future[pos]], -1);
            }
            if (1'000'000 - last[pos] != -1) {
                FUTURE.update(1'000'000 - last[pos], pos, future[pos]);
                ST.update(last[1'000'000 - last[pos]], future[1'000'000 - last[pos]], -1);
            }

            if (future[pos] != n) {
                last[future[pos]] = last[pos];
                ST.update(last[future[pos]], future[future[pos]], 1);
            }
            if (1'000'000 - last[pos] != -1) {
                future[1'000'000 - last[pos]] = future[pos];
                ST.update(last[1'000'000 - last[pos]], future[1'000'000 - last[pos]], 1);
            }

            ST.update(last[pos], future[pos], -1);

            POSITIONS[a[pos]].Del(pos);
            POSITIONS[val].Add(pos);

            if (POSITIONS[val].Find(-1) == false) {
                POSITIONS[val].Add(-1);
            }
            if (POSITIONS[val].Find(n) == false) {
                POSITIONS[val].Add(n);
            }

            int Last_for_val = POSITIONS[val].Find_ll(pos);
            int Future_for_val = POSITIONS[val].Find_rr(pos);

            LAST.update(pos, 1'000'000 - last[pos], Last_for_val);
            FUTURE.update(pos, future[pos], Future_for_val);

            last[pos] = 1'000'000 - POSITIONS[val].Find_ll(pos);
            future[pos] = POSITIONS[val].Find_rr(pos);

            a[pos] = val;

            ST.update(last[pos], future[pos], 1);

            if (Future_for_val != n) {
                LAST.update(Future_for_val, Last_for_val, pos);
                ST.update(last[Future_for_val], future[Future_for_val], -1);
            }
            if (Last_for_val != -1) {
                FUTURE.update(Last_for_val, Future_for_val, pos);
                ST.update(last[Last_for_val], future[Last_for_val], -1);
            }

            if (Future_for_val != n) {
                last[Future_for_val] = 1'000'000 - pos;
                ST.update(last[Future_for_val], future[Future_for_val], 1);
            }
            if (Last_for_val != -1) {
                future[Last_for_val] = pos;
                ST.update(last[Last_for_val], future[Last_for_val], 1);
            }
        }
        else {
            int l, r; cin >> l >> r;

            --l;
            --r;

            int min_X = 1'000'000 - l;
            int min_Y = r;

            cout << ST.query(min_X + 1, min_Y + 1, inf, inf) - LAST.query_L(r + 1, n - 1, l - 1) - FUTURE.query_R(0, l - 1, r + 1) << endl;
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
