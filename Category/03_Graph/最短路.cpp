// dijkstra
// 求解 `非负权重加权有向图` 上 `单源最短路`
//
//
// 练习题：
// https://leetcode.cn/problems/minimize-the-maximum-edge-weight-of-graph/    对dijkstra小小修改，也可以二分+dfs
//

// 堆优化 稀疏图
vector<i64> dis(n, inf);
auto dijkstra = [&](int s = 0) -> void {
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
    pq.emplace(0, s); // dis[k], k
    dis[s] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dis[u]) {
            continue;
        }
        for (auto& [v, w] : g[u]) {
            if (dis[v] > d + w) {
                dis[v] = d + w;
                pq.emplace(dis[v], v);
            }
        }
    }
};


// 朴素 稠密图
vector<i64> dis(n, inf);
vector<int> vis(n);
auto plain_dijkstra = [&](int s = 0) {
    dis[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (vis[j] == 0 && (u == -1 || dis[j] < dis[u])) {
                u = j;
            }
        }
        vis[u] = 1;
        for (auto& [v, w] : g[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
            }
        }
    }
};
// The node-index starts from 0


// 0-1 BFS 本质是对 Dijkstra 算法的优化。
// 因为边权只有 0 和 1，我们可以把最小堆换成双端队列，遇到 0 边权就加入队首，遇到 1 边权就加入队尾，
// 这样可以保证队首总是最小的，就不需要最小堆了。
//
void solve() {
    int n = grid.size(), m = grid[0].size();

    vector dis(n, vector<int>(m, inf));
    dis[0][0] = grid[0][0];

    deque<pair<int, int>> q;
    q.emplace_front(0, 0);

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        for (auto& [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int g = grid[nx][ny];
                if (dis[x][y] + g < dis[nx][ny]) {
                    dis[nx][ny] = dis[x][y] + g;
                    g == 0 ? q.emplace_front(nx, ny) : q.emplace_back(nx, ny);
                }
            }
        }
    }
}


// BellmanFord  可以处理有负权，但不能有负环
//
// 时间复杂度 O(nm)
//
void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<int> x(m + 1), y(m + 1), w(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> x[i] >> y[i] >> w[i];
    }

    vector<int> d(n + 1, inf);
    auto BellmanFord = [&]() {
        d[s] = 0;
        for (int k = 1; k < n; ++k) {
            for (int i = 1; i <= m; ++i) {
                d[y[i]] = min(d[y[i]], d[x[i]] + w[i]);
            }
        }
        return 0;
    }();

    for (int i = 1; i <= n; ++i) {
        cout << d[i] << " ";
    }
    cout << "\n";
}



// SPFA
//
// 对于 Bellman-Ford 的过程来说，只有上一次被松弛过的节点，所连接的边才可能引起下一次松弛，
// 可以利用队列维护需要进行松弛的节点。
//
void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        g[x].emplace_back(y, w);
    }

    vector<int> inq(n + 1), cnt(n + 1);
    vector<int> dis(n + 1, numeric_limits<int>::max() / 2);
    auto spfa = [&]() {
        queue<int> q;
        q.emplace(s);
        dis[s] = 0, inq[s] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            inq[x] = 0;
            for (auto [y, w] : g[x]) {
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    if (inq[y]) {
                        continue;
                    }
                    q.emplace(y);
                    inq[y] = 1;
                    if (++cnt[y] > n) { // 有负环
                        return false;
                    }
                }
            }
        }
        return true;
    }();

    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " ";
    }
    cout << "\n";
}



// Floyd-Warshall
// 求解图中任意两点之间的最短路径
// 适用于任何图，不管有向无向，边权正负，但是最短路必须存在（不能有负环）。
//
// 时间复杂度 O(n^3) 空间复杂度 O(n^2)
//
// 练习题：
// https://codeforces.com/contest/2057/problem/E2    2500
//
auto FloydWarshall(int n, vector<array<int, 3>>& edges) { // 顶点数、边列表
    vector g(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    for (const auto& [u, v, d] : edges) {
        g[u][v] = g[v][u] = min(g[u][v], d);
    }

    // g[k][i][j] 表示「经过若干个编号不超过 k 的中间节点」时，从 i 到 j 的最短路长度，其中第一维可以压缩掉
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (g[i][k] == inf) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    // 如果出现 g[i][i] < 0 则说明有负环

    return g;
}

// 动态加边
auto addEdge(int from, int to, int dis, vector<vector<int>>& g) {
    int n = g.size();
    if (dis >= g[from][to]) { // 无法让任何最短路变短
        return;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            g[i][j] = min(g[i][j], g[i][from] + dis + g[to][j]);
        }
    }
}
