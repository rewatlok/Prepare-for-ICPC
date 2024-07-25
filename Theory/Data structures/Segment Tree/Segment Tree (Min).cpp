class SegmentTreeMin {
public:
    SegmentTreeMin(int size) {
        n = size;
        tree.assign(4 * n, INT_MAX);
        lazy.assign(4 * n, 0);
    }

    SegmentTreeMin(const vector<int>& a) {
        n = (int)a.size();
        tree.assign(4 * n, INT_MAX);
        lazy.assign(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            updateRange(1, 0, n - 1, i, i, a[i], false);
        }
    }

    void plus(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, true);
    }

    void change(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, false);
    }

    int queryMin(int const_l, int const_r) {
        return queryMinRange(1, 0, n - 1, const_l, const_r);
    }

private:
    vector<int> tree;
    vector<int> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (l != r) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
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
                    lazy[2 * node] += val;
                    lazy[2 * node + 1] += val;
                }
            } else {
                tree[node] = val;
                if (l != r) {
                    lazy[2 * node] = val;
                    lazy[2 * node + 1] = val;
                }
            }
            return;
        }
        int mid = (l + r) / 2;
        updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
        updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int queryMinRange(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return INT_MAX;
        }
        propagate(node, l, r);
        if (l >= const_l && r <= const_r) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        int p1 = queryMinRange(2 * node, l, mid, const_l, const_r);
        int p2 = queryMinRange(2 * node + 1, mid + 1, r, const_l, const_r);
        return min(p1, p2);
    }
};
