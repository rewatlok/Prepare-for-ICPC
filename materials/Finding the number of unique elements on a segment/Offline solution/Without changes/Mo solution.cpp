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

class Mo {
public:
    struct QUERY {
        int l;
        int r;
        int id;

        bool operator<(const QUERY& other) const {
            int block1 = l / BLOCK_SIZE;
            int block2 = other.l / BLOCK_SIZE;

            if (block1 != block2) {
                return block1 < block2;
            }

            if (block1 % 2 == 1) {
                return r < other.r;
            }
            else {
                return r > other.r;
            }
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





    Mo(vector<pair<int, int>> Q_, vector<int> a_) : a(a_) {
        BLOCK_SIZE = (int)sqrt((int)a.size()) + 1;

        for (int i = 0; i < (int)Q_.size(); i++) {
            Q.push_back({ Q_[i].first, Q_[i].second, i });
        }
        sort(Q.begin(), Q.end());

        ans.resize((int)Q.size());
        L = 0; R = -1;
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

            ans[Q[i].id] = get_ans();
        }
    }

    void print_ans() {
        for (auto p : ans) {
            cout << p << '\n';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a;

    int L, R;
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> Q;

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        --l;
        --r;
        Q.push_back({ l, r });
    }

    Mo W(Q, a); W.GO();
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
