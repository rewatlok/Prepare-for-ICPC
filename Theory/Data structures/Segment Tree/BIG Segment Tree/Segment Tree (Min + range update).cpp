class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 2e9);
        lazy.assign(p * 2, { 0, false });

        n = p;
    }

    SegmentTree(const vector<int>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 2e9);
        lazy.assign(p * 2, { 0, false });

        n = p;

        for (int i = 0; i < (int)a.size(); ++i) {
            updateRange(1, 0, n - 1, i, i, a[i], false);
        }
    }

    void plus(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, true);
    }

    void change(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, false);
    }

    int query(int const_l, int const_r) {
        return queryRange(1, 0, n - 1, const_l, const_r);
    }
private:
    vector<int> tree;
    vector<pair<int, bool>> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node].second) {
            if (lazy[node].first != 0) {
                tree[node] += lazy[node].first;
                if (l != r) {
                    lazy[2 * node].first += lazy[node].first;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += lazy[node].first;
                    lazy[2 * node + 1].second = true;
                }
            }
        }
        else {
            if (lazy[node].first != 0) {
                tree[node] = lazy[node].first;
                if (l != r) {
                    lazy[2 * node] = lazy[node];
                    lazy[2 * node + 1] = lazy[node];
                }
            }
        }
        lazy[node] = { 0, false };
    }

    void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
        propagate(node, l, r);
        if (l > r || l > const_r || r < const_l) {
            return;
        }
        if (l >= const_l && r <= const_r) {
            if (isAddition) {
                tree[node] += val;
                if (l != r) {
                    lazy[2 * node].first += val;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += val;
                    lazy[2 * node + 1].second = true;
                }
            }
            else {
                tree[node] = val;
                if (l != r) {
                    lazy[2 * node] = { val, false };
                    lazy[2 * node + 1] = { val, false };
                }
            }
            return;
        }

        int mid = (l + r) / 2;

        updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
        updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int queryRange(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return 2e9;
        }

        propagate(node, l, r);

        if (l >= const_l && r <= const_r) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        int p1 = queryRange(2 * node, l, mid, const_l, const_r);
        int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

        return min(p1, p2);
    }
};
