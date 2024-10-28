// kruskal 能够处理有向边或者无向边，适用于稀疏图
//
// 结构体存边，对边进行排序，并初始化一个并查集，当 "边数 = 点数 - 1" 时停止。
//
struct Edge {
    int u, v, w;
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        u--, v--;
    }

    ranges::sort(edges, [&](const Edge& e1, const Edge& e2) { return e1.w < e2.w; });

    vector<int> pa(n);
    iota(pa.begin(), pa.end(), 0);

    function<int(int)> find = [&](int x) {
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    };

    ll sum = 0; // 最小生成树的边权和
    int tot = 0; // 连边数
    bool ok = false; // 判断是否有最小生成树
    for (auto& [u, v, w] : edges) {
        int ru = find(u), rv = find(v);
        if (ru == rv) {
            continue;
        }
        sum += w;
        pa[ru] = rv;
        tot++;
        if (tot == n - 1) {
            ok = true;
            break;
        }
    }

    if (ok) {
        cout << sum << "\n";
    } else {
        cout << "orz\n";
    }
}
// The node-index starts from 0
