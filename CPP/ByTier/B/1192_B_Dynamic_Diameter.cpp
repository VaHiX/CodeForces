/*
 * Problem URL : https://codeforces.com/contest/1192/problem/B
 * Submit Date : 2025-09-02
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stack>
#include <cmath>
using namespace std;

using ll = long long;

struct Node {
    ll min_d;
    ll max_d;
    ll best;
    ll best_l;
    ll best_r;
    ll lazy;
    Node() : min_d(0), max_d(0), best(0), best_l(0), best_r(0), lazy(0) {}
};

vector<vector<pair<int, ll>>> graph;
vector<tuple<int, int, ll>> edges;
vector<ll> current_edge_weight;
vector<int> child_node;

vector<int> parent_vec;
vector<ll> depth_node;
vector<int> in_time;
vector<int> out_time;
vector<ll> D;
int timer = 0;
int n, q;
ll w;

vector<Node> seg_tree;

void dfs_times(int u, int parent, ll depth) {
    in_time[u] = timer;
    D[timer] = depth;
    timer++;
    for (auto &edge : graph[u]) {
        int v = edge.first;
        ll weight = edge.second;
        if (v == parent) continue;
        parent_vec[v] = u;
        depth_node[v] = depth + weight;
        dfs_times(v, u, depth + weight);
        D[timer] = depth;
        timer++;
    }
    out_time[u] = timer - 1;
}

Node merge(Node &L, Node &R) {
    Node res;
    res.min_d = min(L.min_d, R.min_d);
    res.max_d = max(L.max_d, R.max_d);
    res.best_l = max({L.best_l, R.best_l, R.max_d - 2 * L.min_d});
    res.best_r = max({R.best_r, L.best_r, L.max_d - 2 * R.min_d});
    res.best = max({L.best, R.best, L.best_r + R.max_d, L.max_d + R.best_l});
    res.lazy = 0;
    return res;
}

void push(int node_idx, int l, int r) {
    if (seg_tree[node_idx].lazy != 0) {
        seg_tree[node_idx].min_d += seg_tree[node_idx].lazy;
        seg_tree[node_idx].max_d += seg_tree[node_idx].lazy;
        seg_tree[node_idx].best_l -= seg_tree[node_idx].lazy;
        seg_tree[node_idx].best_r -= seg_tree[node_idx].lazy;
        if (l != r) {
            seg_tree[2*node_idx+1].lazy += seg_tree[node_idx].lazy;
            seg_tree[2*node_idx+2].lazy += seg_tree[node_idx].lazy;
        }
        seg_tree[node_idx].lazy = 0;
    }
}

void build_seg_tree(int node_idx, int l, int r) {
    if (l == r) {
        seg_tree[node_idx].min_d = D[l];
        seg_tree[node_idx].max_d = D[l];
        seg_tree[node_idx].best = 0;
        seg_tree[node_idx].best_l = -D[l];
        seg_tree[node_idx].best_r = -D[l];
        seg_tree[node_idx].lazy = 0;
        return;
    }
    int mid = (l + r) / 2;
    build_seg_tree(2*node_idx+1, l, mid);
    build_seg_tree(2*node_idx+2, mid+1, r);
    seg_tree[node_idx] = merge(seg_tree[2*node_idx+1], seg_tree[2*node_idx+2]);
}

void update_seg_tree(int node_idx, int l, int r, int ql, int qr, ll add) {
    push(node_idx, l, r);
    if (qr < l || r < ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        seg_tree[node_idx].lazy = add;
        push(node_idx, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update_seg_tree(2*node_idx+1, l, mid, ql, qr, add);
    update_seg_tree(2*node_idx+2, mid+1, r, ql, qr, add);
    push(2*node_idx+1, l, mid);
    push(2*node_idx+2, mid+1, r);
    seg_tree[node_idx] = merge(seg_tree[2*node_idx+1], seg_tree[2*node_idx+2]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q >> w;
    graph.resize(n);
    edges.resize(n-1);
    current_edge_weight.resize(n-1);
    child_node.resize(n-1);

    for (int i = 0; i < n-1; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        edges[i] = make_tuple(a, b, c);
        current_edge_weight[i] = c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    parent_vec.resize(n, -1);
    depth_node.resize(n, 0);
    in_time.resize(n);
    out_time.resize(n);
    D.resize(2*n-1, 0);

    dfs_times(0, -1, 0);

    for (int i = 0; i < n-1; i++) {
        int a = get<0>(edges[i]);
        int b = get<1>(edges[i]);
        if (parent_vec[b] == a) {
            child_node[i] = b;
        } else {
            child_node[i] = a;
        }
    }

    int size = 2*n - 1;
    seg_tree.resize(4 * size);
    build_seg_tree(0, 0, size-1);

    ll last = 0;
    for (int i = 0; i < q; i++) {
        ll d, e;
        cin >> d >> e;
        d = (d + last) % (n-1);
        e = (e + last) % w;
        int edge_index = d;
        ll new_weight = e;
        ll old_weight = current_edge_weight[edge_index];
        ll delta = new_weight - old_weight;
        current_edge_weight[edge_index] = new_weight;

        int child = child_node[edge_index];
        update_seg_tree(0, 0, size-1, in_time[child], out_time[child], delta);

        last = seg_tree[0].best;
        cout << last << '\n';
    }

    return 0;
}
