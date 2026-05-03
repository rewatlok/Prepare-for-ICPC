namespace GEOMETRY {
    const long double geometry_eps = 1e-9;

    template<typename T>
    struct r {
        T x;
        T y;

        r() {}
        r(T x_, T y_) : x(x_), y(y_) {}

        T len() const {
            return x * x + y * y;
        }

        long double sqrt_len() const {
            return sqrtl((long double)(x * x + y * y));
        }

        r rot() const {
            return r(-y, x);
        }

        r operator+(const r& a) const {
            return { x + a.x, y + a.y };
        }

        r operator-(const r& a) const {
            return { x - a.x, y - a.y };
        }

        template<typename G>
        r operator*(G k) const {
            return { x * k, y * k };
        }

        template<typename G>
        r operator/(G k) const {
            return { x / k, y / k };
        }

        r& operator+=(const r& a) {
            x += a.x; y += a.y;
            return *this;
        }

        r& operator-=(const r& a) {
            x -= a.x; y -= a.y;
            return *this;
        }

        template<typename G>
        r& operator*=(G k) {
            x *= k; y *= k;
            return *this;
        }

        template<typename G>
        r& operator/=(G k) {
            x /= k; y /= k;
            return *this;
        }

        T operator*(const r& a) const {
            return x * a.x + y * a.y;
        }

        T operator^(const r& a) const {
            return x * a.y - a.x * y;
        }

        bool operator==(const r& a) const {
            return x == a.x && y == a.y;
        }

        bool operator!=(const r& a) const {
            return !(*this == a);
        }

        bool operator<(const r& a) const {
            return len() < a.len();
        }

        bool operator>(const r& a) const {
            return a < *this;
        }

        bool operator<=(const r& a) const {
            return !(a < *this);
        }

        bool operator>=(const r& a) const {
            return !(*this < a);
        }
    };

    template<typename T>
    bool ccw(const r<T>& a, const r<T>& b, const r<T>& c) {
        return ((b - a) ^ (c - a)) > 0;
    }

    template<typename T>
    bool collinear(const r<T>& a, const r<T>& b) {
        return abs(a ^ b) < geometry_eps;
    }

    template<typename T>
    bool collinear(const r<T>& a, const r<T>& b, const r<T>& c) {
        return abs((b - a) ^ (c - a)) < geometry_eps;
    }

    template<typename T>
    istream& operator>>(istream& in, r<T>& p) {
        in >> p.x >> p.y;
        return in;
    }

    template<typename T>
    ostream& operator<<(ostream& out, const r<T>& p) {
        out << p.x << ' ' << p.y;
        return out;
    }

    template<typename T>
    vector<r<T>> get_env(vector<r<T>> points, bool F) {
        sort(points.begin(), points.end(), [](const r<T>& a, const r<T>& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
            });

        if (F == true) {
            // pass
        }
        else {
            reverse(all(points));
        }

        vector<r<T>> env;
        for (const auto& point : points) {
            while (env.size() >= 2 && ((env[env.size() - 1] - env[env.size() - 2]) ^ (point - env[env.size() - 2])) <= 0) {
                env.pop_back();
            }
            env.push_back(point);
        }
        return env;
    }

    template<typename T>
    vector<r<T>> convex_hull(vector<r<T>> points) {
        vector<r<T>> lower = get_env(points, true); lower.pop_back();
        vector<r<T>> upper = get_env(points, false); upper.pop_back();

        vector<r<T>> hull;
        for (const auto& point : lower) {
            hull.push_back(point);
        }
        for (const auto& point : upper) {
            hull.push_back(point);
        }

        return hull;
    }

    template<typename T>
    pair<r<T>, r<T>> tangents_from_point(const vector<r<T>>& hull, const r<T> P) {
        int n = hull.size();

        auto left_edge = [&](int i) {
            r<T> v1 = hull[i] - P;
            r<T> v2 = hull[(i + 1) % n] - P;
            return (v1 ^ v2) > 0;
            };

        int left_tangent = -1;
        {
            int low = 0, high = 2 * n;
            while (low < high) {
                int mid = (low + high) / 2;
                if (left_edge(mid % n)) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }
            left_tangent = low % n;
        }

        auto right_edge = [&](int i) {
            r<T> v1 = hull[i] - P;
            r<T> v2 = hull[(i + 1) % n] - P;
            return (v1 ^ v2) >= 0;
            };

        int right_tangent = -1;
        {
            int low = 0, high = 2 * n;
            while (low < high) {
                int mid = (low + high) / 2;
                if (!right_edge(mid % n)) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }
            right_tangent = low % n;
        }

        return { hull[right_tangent], hull[left_tangent] };
    }

    template<typename T>
    T convex_hull_diameter(const vector<r<T>>& hull) {
        int n = hull.size();

        auto sq_dist = [](const r<T>& a, const r<T>& b) {
            return (a - b).len();
            };

        T ans = 0;
        int r = 0;

        for (int l = 0; l < n; l++) {
            while (sq_dist(hull[l], hull[(r + 1) % n]) > sq_dist(hull[l], hull[r])) {
                r = (r + 1) % n;
            }
            ans = max(ans, sq_dist(hull[l], hull[r]));
        }

        return ans;
    }

    template<typename T>
    r<T> max_hull_point(const vector<r<T>>& hull, T A, T B) {
        int n = hull.size();

        if (n == 0) {
            return r<T>(0, 0);
        }

        if (n <= 30) {
            int best_index = 0;
            T best_val = A * hull[0].x + B * hull[0].y;
            for (int i = 1; i < n; i++) {
                T val = A * hull[i].x + B * hull[i].y;
                if (val > best_val) {
                    best_val = val;
                    best_index = i;
                }
            }
            return hull[best_index];
        }

        auto get_val = [&](int index) {
            return A * hull[index % n].x + B * hull[index % n].y;
            };

        int l = 0;
        int r = n - 1;

        while (r - l > 2) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            if (get_val(m1) < get_val(m2)) {
                l = m1;
            }
            else {
                r = m2;
            }
        }

        int best_index = l;
        T best_val = get_val(best_index);
        for (int i = l; i <= r; i++) {
            T val = get_val(i);
            if (val > best_val) {
                best_val = val;
                best_index = i;
            }
        }

        return hull[best_index];
    }

    template<typename T>
    struct l {
        T k;
        T b;

        l() {}
        l(T k_, T b_) : k(k_), b(b_) {}

        l operator+(const l& line) const {
            return { line.k + k, line.b + b };
        }

        l& operator+=(const l& line) {
            k += line.k; b += line.b;
            return *this;
        }

        l operator-(const l& line) const {
            return { k - line.k, b - line.b };
        }

        l& operator-=(const l& line) {
            k -= line.k; b -= line.b;
            return *this;
        }

        template<typename G>
        l operator*(G q) const {
            return { k * q, b * q };
        }

        template<typename G>
        l operator/(G q) const {
            return { k / q, b / q };
        }

        template<typename G>
        l& operator*=(G q) {
            k *= q; b *= q;
            return *this;
        }

        template<typename G>
        l& operator/=(G q) {
            k /= q; b /= q;
            return *this;
        }

        bool operator<(const l& line) const {
            return k < line.k;
        }

        T operator[](T x) const {
            return k * x + b;
        }
    };

    template<typename T>
    r<T> intersection(const r<T>& a, const r<T>& b, const r<T>& c, const r<T>& d) {
        return r(a + (b - a) * (((c - a) ^ (d - c)) / ((b - a) ^ (d - c))));
    }

    template<typename T>
    bool hp_left(r<T> v, r<T> p, r<T> pt) {
        return (v ^ (pt - p)) >= -geometry_eps;
    }

    template<typename T>
    bool hp_right(r<T> v, r<T> p, r<T> pt) {
        return (v ^ (pt - p)) <= geometry_eps;
    }

    template<typename T>
    r<long double> hp_intersect(r<T> p1, r<T> v1, r<T> p2, r<T> v2) {
        long double cv = (long double)(v1 ^ v2);
        long double t = (long double)((p2 - p1) ^ v2) / cv;
        return r<long double>(p1.x + v1.x * t, p1.y + v1.y * t);
    }

    template<typename T>
    struct halfplane_item {
        r<T> p, v;
        long double ang;
        halfplane_item(r<T> p_, r<T> v_) : p(p_), v(v_) {
            ang = atan2l(v.y, v.x);
        }
        bool operator<(const halfplane_item& o) const {
            if (fabsl(ang - o.ang) > geometry_eps)
                return ang < o.ang;
            return (v ^ p) > (o.v ^ o.p);
        }
    };

    template<typename T>
    vector<r<T>> halfplane_intersection(vector<pair<r<T>, r<T>>> lines) {
        vector<halfplane_item<T>> items;
        for (auto& pr : lines)
            items.emplace_back(pr.first, pr.second);

        sort(items.begin(), items.end());

        vector<halfplane_item<T>> uniq;
        for (auto& it : items)
            if (uniq.empty() || fabsl(it.ang - uniq.back().ang) > geometry_eps)
                uniq.push_back(it);

        deque<halfplane_item<T>> dq;
        deque<r<long double>> pts;

        for (auto& it : uniq) {
            r<long double> v_ld(it.v.x, it.v.y);
            r<long double> p_ld(it.p.x, it.p.y);

            while (!pts.empty() && !hp_left(v_ld, p_ld, pts.back())) {
                dq.pop_back();
                pts.pop_back();
            }
            while (!pts.empty() && !hp_left(v_ld, p_ld, pts.front())) {
                dq.pop_front();
                pts.pop_front();
            }

            if (!dq.empty() && fabsl(dq.back().v ^ it.v) < geometry_eps) {
                if ((it.v * dq.back().v) < 0) {
                    r<long double> backv_ld(dq.back().v.x, dq.back().v.y);
                    r<long double> backp_ld(dq.back().p.x, dq.back().p.y);
                    if (!hp_left(v_ld, p_ld, backp_ld) &&
                        !hp_left(backv_ld, backp_ld, p_ld))
                        return {};
                }
                dq.pop_back();
                if (!pts.empty()) pts.pop_back();
            }

            dq.push_back(it);
            if (dq.size() >= 2) {
                if (fabsl(dq[dq.size() - 2].v ^ dq.back().v) < geometry_eps)
                    return {};
                pts.push_back(hp_intersect(dq[dq.size() - 2].p, dq[dq.size() - 2].v,
                    dq.back().p, dq.back().v));
            }
        }

        r<long double> frontv_ld(dq.front().v.x, dq.front().v.y);
        r<long double> frontp_ld(dq.front().p.x, dq.front().p.y);
        r<long double> backv_ld(dq.back().v.x, dq.back().v.y);
        r<long double> backp_ld(dq.back().p.x, dq.back().p.y);

        while (!pts.empty() && !hp_left(frontv_ld, frontp_ld, pts.back())) {
            dq.pop_back();
            pts.pop_back();
        }
        while (!pts.empty() && !hp_left(backv_ld, backp_ld, pts.front())) {
            dq.pop_front();
            pts.pop_front();
        }

        if (dq.size() <= 2) return {};

        pts.push_back(hp_intersect(dq.back().p, dq.back().v,
            dq.front().p, dq.front().v));

        vector<r<T>> result;
        for (auto& pt : pts)
            result.push_back(r<T>((T)pt.x, (T)pt.y));
        return result;
    }

    template<typename T, bool IsMin>
    class CHT {
    private:
        std::vector<l<T>> hull;
        std::vector<long double> crosses;
        T neutral;

        using Comp = std::conditional_t<IsMin, std::less<T>, std::greater<T>>;
        Comp comp;

        long double intersect(const l<T>& a, const l<T>& b) const {
            if (a.k == b.k) {
                if constexpr (IsMin) {
                    return a.b < b.b ? -1e18 : 1e18;
                }
                else {
                    return a.b > b.b ? -1e18 : 1e18;
                }
            }
            return static_cast<long double>(b.b - a.b) / (a.k - b.k);
        }

    public:
        explicit CHT(T neutral_ = std::numeric_limits<T>::max())
            : neutral(neutral_), comp(Comp()) {
        }

        void add_line(l<T> line) {
            while (hull.size() > 0 && hull.back().k == line.k) {
                if constexpr (IsMin) {
                    if (hull.back().b <= line.b) {
                        return;
                    }
                }
                else {
                    if (hull.back().b >= line.b) {
                        return;
                    }
                }

                hull.pop_back();

                if (crosses.size() > 0) {
                    crosses.pop_back();
                }
            }

            while (hull.size() > 0) {
                if (hull.size() == 1) {
                    crosses.push_back(intersect(hull.back(), line));
                    break;
                }

                long double nx = intersect(hull.back(), line);

                if (nx > crosses.back()) {
                    crosses.push_back(nx);
                    break;
                }
                else {
                    crosses.pop_back();
                    hull.pop_back();
                }
            }

            hull.push_back(line);
        }

        T query(T x) const {
            if (hull.empty()) {
                return neutral;
            }

            if (crosses.empty()) {
                return hull[0][x];
            }

            int i = crosses.size();

            int lo = 0;
            int hi = crosses.size() - 1;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;

                if (x < crosses[mid]) {
                    i = mid;
                    hi = mid - 1;
                }
                else {
                    lo = mid + 1;
                }
            }

            return hull[i][x];
        }
    };

    template<typename T>
    using CHT_min = CHT<T, true>;

    template<typename T>
    using CHT_max = CHT<T, false>;

    template <typename T, typename Compare>
    class li_chao_tree {
    public:
        li_chao_tree(T low, T high, T neutral, Compare comp = Compare())
            : low_range(low), high_range(high), neutral(neutral), comp(comp), root(nullptr) {
        }

        void add_line(T k, T b) {
            l<T> l{ k, b };
            add_line(root, low_range, high_range, l);
        }

        T query(T x) {
            return query(root, low_range, high_range, x);
        }
    private:
        struct node {
            l<T> f;
            node* left = nullptr;
            node* right = nullptr;
            node(const l<T>& f_) : f(f_) {}
        };

        T low_range;
        T high_range;
        T neutral;
        Compare comp;
        node* root;

        void add_line(node*& v, T lo, T hi, l<T> f) {
            if (!v) {
                v = new node(f);
                return;
            }

            T mid = lo + (hi - lo) / 2;

            if (comp(f[mid], v->f[mid])) {
                std::swap(f, v->f);
            }

            if (lo == hi) {
                return;
            }

            if (comp(f[lo], v->f[lo])) {
                add_line(v->left, lo, mid, f);
            }
            else {
                add_line(v->right, mid + 1, hi, f);
            }
        }

        T query(node* v, T lo, T hi, T x) {
            if (!v) {
                return neutral;
            }

            T res = v->f[x];

            if (lo == hi) {
                return res;
            }

            T mid = lo + (hi - lo) / 2;

            if (x <= mid) {
                T candidate = query(v->left, lo, mid, x);
                return comp(res, candidate) ? res : candidate;
            }
            else {
                T candidate = query(v->right, mid + 1, hi, x);
                return comp(res, candidate) ? res : candidate;
            }
        }
    };

    template <typename T>
    using li_chao_tree_min = li_chao_tree<T, std::less<T>>;

    template <typename T>
    using li_chao_tree_max = li_chao_tree<T, std::greater<T>>;

    template<typename T>
    struct FORTUNE {
        long double sweepx;

        const long double EPS = 1e-12;
        const long double INF = 1e18;

        struct ARC {
            const FORTUNE& outer;

            mutable r<T> p;
            mutable r<T> q;

            mutable int id = 0;
            mutable int i;

            ARC(const FORTUNE& outer, r<T> p, r<T> q, int i)
                : outer(outer), p(p), q(q), i(i) {
            }

            long double gety(long double x) const {
                if (q.y == outer.INF) {
                    return outer.INF;
                }

                x += outer.EPS;
                r<T> med = (p + q) * 0.5;
                r<T> dir = (p - med).rot();

                long double D = (x - p.x) * (x - q.x);
                if (D < 0) {
                    D = 0;
                }

                return med.y + ((med.x - x) * dir.x + sqrtl(D) * dir.sqrt_len()) / dir.y;
            }

            bool operator<(const long double& y) const {
                return gety(outer.sweepx) < y;
            }

            bool operator<(const ARC& o) const {
                return gety(outer.sweepx) < o.gety(outer.sweepx);
            }
        };

        using beach = std::multiset<ARC, std::less<>>;
        using beach_iterator = typename beach::iterator;

        struct EVENT {
            long double x;
            int id;
            beach_iterator it;

            EVENT(long double x, int id, beach_iterator it)
                : x(x), id(id), it(it) {
            }

            bool operator<(const EVENT& e) const {
                return x > e.x;
            }
        };

        beach line;
        vector<pair<r<T>, int>> sites;
        priority_queue<EVENT> Q;
        vector<pair<int, int>> edges;
        vector<bool> valid;
        int n;
        int ti;

        FORTUNE(vector<r<T>> p) {
            n = p.size();
            sites.resize(n);
            for (int i = 0; i < n; i++) {
                sites[i] = { p[i], i };
            }
            sort(sites.begin(), sites.end());
        }

        void add_edge(int i, int j) {
            if (i != -1 && j != -1) {
                edges.push_back({ i, j });
            }
        }

        void upd(beach_iterator it) {
            if (it == line.end() || it == line.begin()) {
                return;
            }

            if (it->i != -1) {
                if (it->id != 0) {
                    valid[-it->id] = false;
                }

                if (collinear(it->q - it->p, prev(it)->p - it->p)) {
                    return;
                }

                it->id = --ti;
                valid.push_back(true);

                auto circumcenter = [](r<T> a, r<T> b, r<T> c) {
                    b = (a + b) * 0.5;
                    c = (a + c) * 0.5;
                    return intersection(b, b + (b - a).rot(), c, c + (c - a).rot());
                    };

                r<T> c = circumcenter(it->p, it->q, prev(it)->p);
                long double x = c.x + (c - it->p).sqrt_len();

                if (x > sweepx - EPS && prev(it)->gety(x) + EPS > it->gety(x)) {
                    Q.push(EVENT(x, it->id, it));
                }
            }
        }

        void add(int i) {
            r<T> p = sites[i].first;

            auto c = line.lower_bound(p.y);
            if (c == line.end()) {
                return;
            }

            auto b = line.insert(c, ARC(*this, p, c->p, i));
            auto a = line.insert(b, ARC(*this, c->p, p, c->i));

            add_edge(i, c->i);

            if (a != line.begin()) {
                upd(a);
            }

            upd(b);

            if (next(c) != line.end()) {
                upd(next(c));
            }

            upd(c);
        }

        void remove(beach_iterator it) {
            if (it == line.end()) {
                return;
            }

            auto a = prev(it);
            auto b = next(it);

            line.erase(it);

            if (a != line.end() && b != line.end()) {
                a->q = b->p;
                add_edge(a->i, b->i);

                if (a != line.begin()) {
                    upd(a);
                }
                upd(b);
            }
        }

        void solve(long double X = 1e18) {
            line.insert(ARC(*this, r<T>(-X, -X), r<T>(-X, X), -1));
            line.insert(ARC(*this, r<T>(-X, X), r<T>(INF, INF), -1));

            for (int i = 0; i < n; i++) {
                Q.push(EVENT(sites[i].first.x, i, line.end()));
            }

            ti = 0;
            valid.assign(1, false);

            while (!Q.empty()) {
                EVENT e = Q.top();
                Q.pop();

                sweepx = e.x;

                if (e.id >= 0) {
                    add(e.id);
                }
                else {
                    int e_id = -e.id;
                    if (e_id < (int)valid.size() && valid[e_id]) {
                        remove(e.it);
                    }
                }
            }
        }
    };
}
