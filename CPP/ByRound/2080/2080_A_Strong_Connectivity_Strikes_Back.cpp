// Problem: CF 2080 A - Strong Connectivity Strikes Back
// https://codeforces.com/contest/2080/problem/A

/*
 * Problem: Strong Connectivity Strikes Back
 *
 * Description:
 * Given a directed graph, find the maximum number of edges whose directions can be erased such that the
 * resulting graph uniquely determines the original edge orientations based on strongly connected components.
 * Output the size of such maximum set and the count of all possible sets modulo 10^9 + 7.
 *
 * Algorithms:
 * - Tarjan's algorithm for finding strongly connected components (SCC)
 * - Graph traversal using DFS
 * - Modular arithmetic operations
 *
 * Time Complexity: O(n * m) where n is number of vertices and m is number of edges,
 *                  due to nested loops in processing SCCs and edge sets.
 *
 * Space Complexity: O(n + m), for storing graph structure, component colors, timestamps,
 *                   and auxiliary data structures like stacks and arrays.
 */

#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;
vector<vector<int>> gr;         // Adjacency list of the graph
vector<int> st;                 // Stack for Tarjan's algorithm
vector<int> t;                  // Timestamps for nodes during DFS traversal
int timer = 0;                  // Timer for DFS timestamps
int cc = 0;                     // Number of strongly connected components
vector<int> comp_color;         // Color (component ID) for each node
int banned_from = -1, banned_to = -1;  // For temporarily excluding an edge during SCC computation

void dfs(int v) {
    int tin = timer++;          // Assign timestamp to current node
    t[v] = tin;                 // Store discovery time
    st.push_back(v);            // Push into stack for component detection

    for (auto to : gr[v]) {
        if (v == banned_from && to == banned_to)
            continue;           // Skip this edge temporarily
        if (t[to] == -1) {      // If not visited yet
            dfs(to);            // Recursively visit neighbor
            t[v] = min(t[v], t[to]);  // Update low-link value
        } else if (comp_color[to] == -1) {
            t[v] = min(t[v], t[to]);  // Back edge case
        }
    }

    // If root of component found
    if (tin == t[v]) {
        while (st.back() != v) {   // Pop from stack until root is reached
            comp_color[st.back()] = cc;
            st.pop_back();
        }
        comp_color[v] = cc;
        st.pop_back();
        cc++;
    }
}

// Function to perform DFS and compute SCCs
void scc_colors() {
    st.clear();                 // Clear stack
    timer = 0;                  // Reset timer
    t.assign(gr.size(), -1);    // Initialize timestamps to -1
    comp_color.assign(gr.size(), -1);  // Initialize component colors to -1

    for (int i = 0; i < gr.size(); ++i) {
        if (t[i] == -1) {       // If unvisited
            dfs(i);
        }
    }
}

int ans = 0;                   // Final answer to be returned as number of erasable edges
int cnt = 1;                   // Counters for valid ways to remove edges (modulo 1e9 + 7)
const int MOD = 1e9 + 7;

int main() {
    int n, m, group;
    cin >> n >> m >> group;
    gr.resize(n);
    vector<pair<int, int>> edges(m);

    // Read input graph and store in adjacency list
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        u--, v--;                // Convert to 0-based indexing
        gr[u].push_back(v);
    }

    scc_colors(); // Find strongly connected components

    {
        vector<vector<int>> comp_gr_cnt(cc, vector<int>(cc));   // Edge count between SCCs
        vector<set<int>> comp_gr(cc);                           // Adjacency set of SCCs

        for (auto [u, v] : edges) {
            comp_gr_cnt[comp_color[u]][comp_color[v]]++;         // Count edges
            if (comp_color[u] != comp_color[v]) {               // If different components
                comp_gr[comp_color[u]].insert(comp_color[v]);
            }
        }

        for (int u = 0; u < cc; ++u) {
            for (int v : comp_gr[u]) {
                vector<bool> used(cc);
                used[u] = true;
                deque<int> q = {u};
                while (!q.empty()) {
                    int i = q.front();
                    q.pop_front();
                    for (auto to : comp_gr[i]) {
                        if (used[to] || i == u && to == v)
                            continue;
                        used[to] = true;
                        q.push_back(to);
                    }
                }
                if (used[v]) {
                    ans += comp_gr_cnt[u][v];   // Add to answer if path exists
                } else {
                    cnt = 1ll * cnt * comp_gr_cnt[u][v] % MOD;  // Multiply ways to select
                    ans += comp_gr_cnt[u][v] - 1;              // Subtract non-essential edges
                }
            }
        }
    }

    auto initial_comp_color = comp_color;
    vector<vector<int>> comps(cc);
    for (int i = 0; i < n; ++i) {
        comps[comp_color[i]].push_back(i);   // Group vertices by component
    }

    vector<vector<bool>> used_edges(n, vector<bool>(n)); // Tracks removed edges

    for (int color = 0; color < comps.size(); ++color) { // For each SCC
        const auto &comp = comps[color];
        vector<pair<int, int>> comp_edges;

        for (int u : comp) {
            for (int v : gr[u]) {
                if (initial_comp_color[v] != color)     // Only internal edges
                    continue;
                comp_edges.emplace_back(u, v);
            }
        }

        vector<vector<pair<int, int>>> S(comp_edges.size()); // Each subset of erased edges

        for (int i = 0; i < comp_edges.size(); ++i) {
            auto [u, v] = comp_edges[i];
            banned_from = u, banned_to = v;
            scc_colors();

            // Check which new components we can get by deleting edge (u,v)
            for (auto [u1, v1] : comp_edges) {
                if (comp_color[u1] != comp_color[v1]) {   // Different SCCs
                    S[i].emplace_back(u1, v1);
                }
            }

            if (comp_color[u] == comp_color[v]) {
                S[i].emplace_back(u, v);  // Self-loop case
            }

            banned_from = -1, banned_to = -1;   // Reset for next iteration
        }

        sort(S.begin(), S.end(),
             [](auto &a, auto &b) { return a.size() < b.size(); });  // Sort by size

        int minimal_count = 0;
        for (auto &S_e : S) {
            bool minimal = true;
            for (auto [u, v] : S_e) {
                if (used_edges[u][v]) {
                    minimal = false;
                    break;
                }
            }
            if (minimal) {
                minimal_count++;
                cnt = 1ll * cnt * S_e.size() % MOD;   // Multiply number of choices
                for (auto [u, v] : S_e) {
                    used_edges[u][v] = true;
                }
            }
        }

        ans += comp_edges.size() - minimal_count; // Add remaining non-minimal edges
    }

    cout << ans << '\n';
    cout << cnt << '\n';
}


// https://github.com/VaHiX/codeForces/