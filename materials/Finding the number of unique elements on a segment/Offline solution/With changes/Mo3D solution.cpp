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

int BLOCK_SIZE = 1000;

struct Trio {
    int First;
    int Second;
    int Third; // 1 -> Query ---> First == l; Second == r;
    // 2 -> Update ---> First = ind; Second == new_elem;
};

class Mo3D {
public:
    struct QUERY {
        int l, r, t, id;

        bool operator<(const QUERY& other) const {
            int block1_l = l / BLOCK_SIZE;
            int block2_l = other.l / BLOCK_SIZE;

            if (block1_l != block2_l) {
                return block1_l < block2_l;
            }

            int block1_r = r / BLOCK_SIZE;
            int block2_r = other.r / BLOCK_SIZE;

            if (block1_r != block2_r) {
                return block1_r < block2_r;
            }

            return t > other.t;
        }
    };





    // --- STATE --- //

    map<int, int> cnt;
    int z = 0;

    void ADD(int G) {
        cnt[a[G]] += 1;

        if (cnt[a[G]] == 0) {
            // no changes
        }
        else if (cnt[a[G]] == 1) {
            ++z;
        }
        else if (cnt[a[G]] == 2) {
            --z;
        }
        else {
            // no changes
        }
    }

    void REM(int G) {
        cnt[a[G]] -= 1;

        if (cnt[a[G]] == 0) {
            --z;
        }
        else if (cnt[a[G]] == 1) {
            ++z;
        }
        else if (cnt[a[G]] == 2) {
            // no changes
        }
        else {
            // no changes
        }
    }
    
    void ADD_TIME() {
        auto pos_newval = changes[T];

        int pos = pos_newval.first;
        int newval = pos_newval.second;

        if (pos >= L && pos <= R) {
            cnt[a[pos]] -= 1;

            if (cnt[a[pos]] == 0) {
                --z;
            }
            else if (cnt[a[pos]] == 1) {
                ++z;
            }
            else if (cnt[a[pos]] == 2) {
                // no changes
            }
            else {
                // no changes
            }

            cnt[newval] += 1;

            if (cnt[newval] == 0) {
                // no changes
            }
            else if (cnt[newval] == 1) {
                ++z;
            }
            else if (cnt[newval] == 2) {
                --z;
            }
            else {
                // no changes
            }
        }

        a[pos] = newval;
    }

    void REM_TIME() {
        auto pos_oldval = unchanges[T];

        int pos = pos_oldval.first;
        int oldval = pos_oldval.second;

        if (pos >= L && pos <= R) {
            cnt[a[pos]] -= 1;

            if (cnt[a[pos]] == 0) {
                --z;
            }
            else if (cnt[a[pos]] == 1) {
                ++z;
            }
            else if (cnt[a[pos]] == 2) {
                // no changes
            }
            else {
                // no changes
            }

            cnt[oldval] += 1;

            if (cnt[oldval] == 0) {
                // no changes
            }
            else if (cnt[oldval] == 1) {
                ++z;
            }
            else if (cnt[oldval] == 2) {
                --z;
            }
            else {
                // no changes
            }
        }

        a[pos] = oldval;
    }

    void add_time() {
        T++;
        ADD_TIME();
    }

    void rem_time() {
        REM_TIME();
        T--;
    }

    void add_right() {
        R++;
        ADD(R);
    }

    void add_left() {
        L--;
        ADD(L);
    }

    void rem_right() {
        REM(R);
        R--;
    }

    void rem_left() {
        REM(L);
        L++;
    }

    auto get_ans() {
        return z;
    }

    // --- STATE --- //





    Mo3D(vector<Trio> Q_, vector<int> a_) : a(a_), ended_a(a_) {
        BLOCK_SIZE = (int)cbrtl(pow((int)a.size(), 2)) + 1;

        int t = -1; int j = 0;
        for (int i = 0; i < (int)Q_.size(); i++) {
            if (Q_[i].Third == 1) {
                Q.push_back({ Q_[i].First, Q_[i].Second, t, j });
                ++j;
            }
            else {
                ++t;
                changes.push_back({ Q_[i].First, Q_[i].Second });
                unchanges.push_back({ Q_[i].First, ended_a[Q_[i].First] });
                ended_a[Q_[i].First] = Q_[i].Second;
            }
        }
        sort(Q.begin(), Q.end());

        ans.resize((int)Q.size());
        L = 0; R = -1, T = -1;
    }

    void GO() {
        for (int i = 0; i < (int)ans.size(); i++) {
            while (R < Q[i].r) {
                add_right();
            }

            while (L > Q[i].l) {
                add_left();
            }

            while (R > Q[i].r) {
                rem_right();
            }

            while (L < Q[i].l) {
                rem_left();
            }

            while (T < Q[i].t) {
                add_time();
            }

            while (T > Q[i].t) {
                rem_time();
            }

            ans[Q[i].id] = get_ans();
        }
    }

    void print_ans() {
        for (auto p : ans) {
            cout << p << ' ';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a, ended_a;

    vector<pair<int, int>> changes;
    vector<pair<int, int>> unchanges;

    int L, R, T;
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Trio> Q;

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string Type; cin >> Type;

        if (Type == "!") {
            int pos, val; cin >> pos >> val;
            --pos;
            Q.push_back({ pos, val, 2 });
        }
        else {
            int l, r; cin >> l >> r;
            --l;
            --r;
            Q.push_back({ l, r, 1 });
        }
    }

    Mo3D W(Q, a); W.GO();
    W.print_ans();
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
