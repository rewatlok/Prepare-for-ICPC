class Implicit_SegmentTree {
public:
    Implicit_SegmentTree(int size) : n(size) {
        tree.resize(2, 0);
        lazy.resize(2, 0);
    }

    void plus(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val);
    }

    int query(int const_l, int const_r) {
        return queryRange(1, 0, n - 1, const_l, const_r);
    }

private:
    std::vector<int> tree;
    std::vector<int> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (r - l + 1);

            if (l != r) {
                ensureNode(node * 2);
                ensureNode(node * 2 + 1);

                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    void ensureNode(int node) {
        if (node >= tree.size()) {
            tree.resize(node + 1, 0);
            lazy.resize(node + 1, 0);
        }
    }

    void updateRange(int node, int l, int r, int const_l, int const_r, int val) {
        propagate(node, l, r);

        if (const_l > r || const_r < l) {
            return;
        }

        if (const_l <= l && r <= const_r) {
            lazy[node] += val;
            propagate(node, l, r);

            return;
        }

        int mid = l + (r - l) / 2;

        ensureNode(node * 2);
        ensureNode(node * 2 + 1);

        updateRange(node * 2, l, mid, const_l, const_r, val);
        updateRange(node * 2 + 1, mid + 1, r, const_l, const_r, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int queryRange(int node, int l, int r, int const_l, int const_r) {
        propagate(node, l, r);

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return tree[node];
        }

        int mid = l + (r - l) / 2;

        ensureNode(node * 2);
        ensureNode(node * 2 + 1);

        int p1 = queryRange(node * 2, l, mid, const_l, const_r);
        int p2 = queryRange(node * 2 + 1, mid + 1, r, const_l, const_r);

        return p1 + p2;
    }
};
