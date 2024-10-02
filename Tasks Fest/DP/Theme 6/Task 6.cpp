#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;

    vector<int> M(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> M[i];
    }

    vector<int> C(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> C[i];
    }

    vector<vector<int>> DP(m + 1);
    for (int i = 0; i < m + 1; i++) {
        DP[i].resize(n + 1);
    }

    for (int i = 0; i < m + 1; i++) {
        DP[i][0] = 0;
    }

    for (int i = 0; i < n + 1; i++) {
        DP[0][i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            DP[i][j] = DP[i][j - 1];
            if (i - M[j] >= 0) {
                DP[i][j] = max(DP[i][j], DP[i - M[j]][j - 1] + C[j]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            ans = max(ans, DP[i][j]);
        }
    }

    cout << ans;

    return 0;
}
