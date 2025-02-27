class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void change(int left, int right, int val) {
        root = updateRange(root, 0, n - 1, left, right, val);
    }

    int query(int left, int right) {
        return queryRange(root, 0, n - 1, left, right);
    }

private:
    struct Node {
        int minVal;
        int lazy;
        Node* left;
        Node* right;

        Node() : minVal(std::numeric_limits<int>::max()), lazy(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    void propagate(Node* node, int l, int r) {
        if (!node || node->lazy == 0) {
            return;
        }

        node->minVal = node->lazy;

        if (l != r) {
            if (!node->left) {
                node->left = new Node();
            }

            if (!node->right) {
                node->right = new Node();
            }

            node->left->lazy = node->lazy;
            node->right->lazy = node->lazy;
        }

        node->lazy = 0;
    }

    Node* updateRange(Node* node, int l, int r, int left, int right, int val) {
        if (!node) {
            node = new Node();
        }

        propagate(node, l, r);

        if (left > r || right < l) {
            return node;
        }

        if (left <= l && r <= right) {
            node->lazy = val;
            propagate(node, l, r);
            return node;
        }

        int mid = l + (r - l) / 2;

        node->left = updateRange(node->left, l, mid, left, right, val);
        node->right = updateRange(node->right, mid + 1, r, left, right, val);

        node->minVal = min(getMin(node->left), getMin(node->right));

        return node;
    }

    int queryRange(Node* node, int l, int r, int left, int right) {
        if (!node) {
            return std::numeric_limits<int>::max();
        }

        propagate(node, l, r);

        if (left > r || right < l) {
            return std::numeric_limits<int>::max();
        }

        if (left <= l && r <= right) {
            return node->minVal;
        }

        int mid = l + (r - l) / 2;

        return min(queryRange(node->left, l, mid, left, right),
            queryRange(node->right, mid + 1, r, left, right));
    }

    int getMin(Node* node) {
        return node ? node->minVal : std::numeric_limits<int>::max();
    }
};
