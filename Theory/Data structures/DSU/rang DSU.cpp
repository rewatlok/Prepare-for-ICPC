struct DSU {
    vector<int> head;
    vector<int> rang;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] > rang[y]) {
            swap(x, y);
        }

        head[x] = y;

        if (rang[x] == rang[y]) {
            ++rang[y];
        }

        return true;
    }
};
