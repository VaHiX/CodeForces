/**
 * Problem: CF2131D - Arboris Contractio
 * 
 * This program solves a tree problem where we need to find the minimum number of edges
 * to remove so that all remaining connected components are stars (trees with diameter at most 2).
 * 
 * Approach:
 * 1. The problem reduces to finding the maximum number of star centers in the tree.
 * 2. A star center is a node connected to multiple leaves.
 * 3. The answer is (number of leaves - maximum number of leaves connected to any single node).
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the tree
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_NODES = 2e5 + 5;

void solve() {
    int n;
    cin >> n;
    
    // Reset and initialize arrays
    vector<int> degree(n + 1, 0);  // Degree of each node
    vector<int> parent(n + 1, 0);  // Parent of each node (for leaves)
    vector<int> leaf_count(n + 1, 0);  // Number of leaves connected to each node
    
    // Read tree edges
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        parent[u] = v;
        parent[v] = u;
    }
    
    // Handle the special case of n=2 (single edge)
    if (n == 2) {
        cout << "0\n";
        return;
    }
    
    int total_leaves = 0;
    int max_leaves = 0;
    
    // Count leaves and track their connections
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {  // This is a leaf node
            total_leaves++;
            int parent_node = parent[i];
            leaf_count[parent_node]++;
            max_leaves = max(max_leaves, leaf_count[parent_node]);
        }
    }
    
    // The answer is (total_leaves - max_leaves)
    cout << total_leaves - max_leaves << '\n';
}

int main() {
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test_cases;
    cin >> test_cases;
    
    while (test_cases--) {
        solve();
    }
    
    return 0;
}
