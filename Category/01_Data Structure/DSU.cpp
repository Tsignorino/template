// 无向图

struct DSU { // Implement (union by size) + (path compression)
    vector<int> pa, _size;
    int block; // 记录连通块的数量

    DSU(int n) : pa(n), _size(n, 1), block(n) { iota(pa.begin(), pa.end(), 0); }

    // int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }
    int find(int x) {
        int root = x;
        while (pa[root] != root) {
            root = pa[root];
        }
        while (pa[x] != root) {
            int tmp = pa[x];
            pa[x] = root;
            x = tmp;
        }
        return root;
    }

    void merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return;
        }
        if (_size[px] > _size[py]) {
            swap(px, py);
        }
        pa[px] = py;
        _size[py] += _size[px];
        block--;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    int size(int x) { return _size[find(x)]; }
};


// DSU++
struct DSU { // Implement (union by size) + (path compression)
    vector<int> pa;
    vector<int> _size;
    vector<int> _edges;
    vector<int> _loop;
    int block; // 记录连通块的数量

    DSU(int n) {
        pa.resize(n + 1);
        iota(pa.begin(), pa.end(), 0);
        _size.resize(n + 1, 1);
        _edges.resize(n + 1, 1);
        _loop.resize(n + 1, 1);
        block = n;
    }

    // int find(int x) { return x == pa[x] ? x : pa[x] = find(pa[x]); }
    int find(int x) {
        int root = x;
        while (pa[root] != root) {
            root = pa[root];
        }
        while (pa[x] != root) {
            int tmp = pa[x];
            pa[x] = root;
            x = tmp;
        }
        return root;
    }

    bool merge(int x, int y) { // 设 x 是 y 的祖先
        if (x == y) {
            _loop[find(x)] = 1;
        }
        x = find(x), y = find(y);
        _edges[x]++;
        if (x == y) {
            return false;
        }
        if (x < y) {
            swap(x, y);
        }
        pa[y] = x;
        _loop[x] |= _loop[y];
        _size[x] += _size[y];
        _edges[x] += _edges[y];
        block--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); } // 判断是否在同一连通块

    int size(int x) { return _size[find(x)]; } // 返回所在连通块的大小

    bool loop(int x) { return _loop[find(x)]; } // 判断连通块内是否存在自环

    int edges(int x) { return _edges[find(x)]; } // 返回连通块中的边的数量
};


// 可撤销并查集（DSU With Rollback）
struct DSU {
    vector<int> size;
    vector<int> pa;
    vector<array<int, 2>> his;

    DSU(int n) : size(n + 1, 1), pa(n + 1) { iota(pa.begin(), pa.end(), 0); }

    int find(int x) {
        while (x != pa[x]) {
            x = pa[x];
        }
        return x;
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        his.push_back({x, y});
        size[x] += size[y];
        pa[y] = x;
        return true;
    }

    int time() { return his.size(); }

    void revert(int time) {
        while (his.size() > time) {
            auto [x, y] = his.back();
            his.pop_back();
            pa[y] = y;
            size[x] -= size[y];
        }
    }
};
