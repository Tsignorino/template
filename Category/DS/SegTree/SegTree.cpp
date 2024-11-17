static constexpr ll inf = 9e18;

template <class Info, class Tag>
class SegTree {
private:
    int n;
    vector<Info> tree;
    vector<Tag> tag;

    void apply(int o, const Tag& t) { tag[o].apply(t), tree[o].apply(t); }
    void push(int o) { apply(o << 1, tag[o]), apply(o << 1 | 1, tag[o]), tag[o] = Tag(); }
    void pull(int o) { tree[o] = tree[o << 1] + tree[o << 1 | 1]; }

public:
    SegTree() : n(0) {}
    SegTree(int n_, Info v_ = Info()) { init(vector(n_, v_)); }
    template <class T>
    SegTree(vector<T>& init_) {
        init(init_);
    }

    template <class T>
    void init(const vector<T>& init_) {
        n = init_.size();
        tree.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());

        function<void(int, int, int)> build = [&](int o, int l, int r) -> void {
            if (l == r) {
                tree[o] = init_[l];
                return;
            }
            int m = l + (r - l) / 2;
            build(o << 1, l, m);
            build(o << 1 | 1, m + 1, r);
            pull(o);
        };
        build(1, 0, n - 1);
    }

public:
    void modify(int id, const Info& v, int o, int l, int r) {
        if (l == r) {
            tree[o] = v;
            return;
        }
        push(o);
        int m = l + (r - l) / 2;
        if (id <= m) {
            modify(id, v, o << 1, l, m);
        } else {
            modify(id, v, o << 1 | 1, m + 1, r);
        }
        pull(o);
    }
    void modify(int id, const Info& v) { modify(id, v, 1, 0, n - 1); }

    void modify(int L, int R, const Tag& t, int o, int l, int r) {
        if (L <= l && r <= R) {
            apply(o, t);
            return;
        }
        push(o);
        int m = l + (r - l) / 2;
        if (L <= m) {
            modify(L, R, t, o << 1, l, m);
        }
        if (m < R) {
            modify(L, R, t, o << 1 | 1, m + 1, r);
        }
        pull(o);
    }
    void modify(int L, int R, const Tag& t) { modify(L, R, t, 1, 0, n - 1); }

    Info query(int id, int o, int l, int r) {
        if (l == r) {
            return tree[o];
        }
        push(o);
        int m = l + (r - l) / 2;
        if (id <= m) {
            return query(id, o << 1, l, m);
        }
        return query(id, o << 1 | 1, m + 1, r);
    }
    Info query(int id) { return query(id, 1, 0, n - 1); }

    Info query(int L, int R, int o, int l, int r) {
        if (L <= l && r <= R) {
            return tree[o];
        }
        push(o);
        int m = l + (r - l) / 2;
        if (R <= m) {
            return query(L, R, o << 1, l, m);
        }
        if (m < L) {
            return query(L, R, o << 1 | 1, m + 1, r);
        }
        return query(L, R, o << 1, l, m) + query(L, R, o << 1 | 1, m + 1, r);
    }
    Info query(int L, int R) { return query(L, R, 1, 0, n - 1); }

    Info queryAll() { return tree[1]; }

    template <class F>
    int findFirst(int L, int R, F& pred, int o, int l, int r) {
        if (l > R || r < L || !pred(tree[o])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        push(o);
        int idx = findFirst(L, R, pred, o << 1, l, m);
        if (idx == -1) {
            idx = findFirst(L, R, pred, o << 1 | 1, m + 1, r);
        }
        return idx;
    }
    template <class F>
    int findFirst(int l, int r, F& pred) {
        return findFirst(l, r, pred, 1, 0, n);
    }

    template <class F>
    int findLast(int L, int R, F& pred, int o, int l, int r) {
        if (l > R || r < L || !pred(tree[o])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        push(o);
        int idx = findLast(L, R, pred, o << 1 | 1, m + 1, r);
        if (idx == -1) {
            idx = findLast(L, R, pred, o << 1, l, m);
        }
        return idx;
    }
    template <class F>
    int findLast(int l, int r, F& pred) {
        return findLast(l, r, pred, 1, 0, n);
    }

    // todo
    void maintainL(int o, int l, int r, int pre) {
        if (tree[o].difl > 0 && tree[o].maxlowl < pre) {
            return;
        }
        if (l == r) {
            tree[o].max = tree[o].maxlowl;
            tree[o].maxl = tree[o].maxr = l;
            tree[o].maxlowl = tree[o].maxlowr = -inf;
            return;
        }
        int m = (l + r) / 2;
        push(o);
        maintainL(o << 1, l, m, pre);
        pre = max(pre, tree[o << 1].max);
        maintainL(o << 1 | 1, m + 1, r, pre);
        pull(o);
    }
    void maintainL() { maintainL(1, 0, n - 1, -1); }

    void maintainR(int o, int l, int r, int suf) {
        if (tree[o].difr > 0 && tree[o].maxlowr < suf) {
            return;
        }
        if (l == r) {
            tree[o].max = tree[o].maxlowl;
            tree[o].maxl = tree[o].maxr = l;
            tree[o].maxlowl = tree[o].maxlowr = -inf;
            return;
        }
        int m = (l + r) / 2;
        push(o);
        maintainR(o << 1 | 1, m + 1, r, suf);
        suf = max(suf, tree[o << 1 | 1].max);
        maintainR(o << 1, l, m, suf);
        pull(o);
    }
    void maintainR() { maintainR(1, 0, n - 1, -1); }
};

struct Tag {
    ll add = 0;
    void apply(const Tag& t) { add += t.add; }
};
struct Info {
    ll sum = 0, len = 0;
    void apply(const Tag& t) { sum += len * t.add; }
};
Info operator+(const Info& a, const Info& b) {
    return Info(a.sum + b.sum, a.len + b.len);
}

// 当维护的信息较多，且传入构造的参数有条件时，
// 该函数可以用需要传入的参数新建节点
Info newInfo(char ch) {
    Info o;
    //
    return o;
}