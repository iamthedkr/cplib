typedef vector<vector<int>> graph;

struct lca {
private:
  const int n = 0;
  const int log2_n = 0;
public:
  vector<vector<int>> parent;
  vector<int> depth;
  lca(const graph &g, int root)
      : n(g.size()), log2_n(32 - __builtin_clz(n) + 1),
        parent(log2_n, vector<int>(n)), depth(n) {
    dfs(g, root, -1, 0);
    for (int k = 0; k + 1 < log2_n; k++) {
      for (int v = 0; v < (int)g.size(); v++) {
        if (parent[k][v] < 0)
          parent[k + 1][v] = -1;
        else
          parent[k + 1][v] = parent[k][parent[k][v]];
      }
    }
  }
private:
  void dfs(const graph &g, int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (auto &e : g[v]) {
      if (e != p) dfs(g, e, v, d + 1);
    }
  }
public:
  int operator()(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < log2_n; k++) {
      if ((depth[v] - depth[u]) >> k & 1) {
        v = parent[k][v];
      }
    }
    if (u == v) return u;
    for (int k = log2_n - 1; k >= 0; k--) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }
};