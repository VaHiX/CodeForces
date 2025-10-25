// Problem: CF 1900 C - Anji's Binary Tree
// https://codeforces.com/contest/1900/problem/C

/**
 * Problem: Determine minimum number of character changes needed to ensure
 *          that a traversal from root to any leaf follows valid path rules.
 *          'L' and 'R' characters determine left/right movement in the tree.
 *          
 * Approach:
 * - Build a tree representation from input (node characters and children)
 * - Use DFS to traverse the tree
 * - At each node, calculate:
 *   - How many changes needed if we don't change the node's character to 'L' 
 *     (a = 1 if current node != 'L')
 *   - How many changes needed if we don't change the node's character to 'R' 
 *     (b = 1 if current node != 'R')
 *   - If leaf node, return 0
 *   - If only one child, go to that child
 *   - If two children, return minimum of both paths
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

// DFS function to calculate minimum changes needed
int dfs(vector<pair<char, pair<int, int>>> &v, int i) {
    // Base case: if leaf node
    if (v[i].second.first == 0 && v[i].second.second == 0)
        return 0;
    
    int a = 0, b = 0;
    // If current node's character is not 'L', we need to change it
    if (v[i].first != 'L')
        a = 1;
    // If current node's character is not 'R', we need to change it  
    if (v[i].first != 'R')
        b = 1;
    
    int ans = 0;
    
    // If leaf node (should not happen here if we already checked)
    if (v[i].second.first == 0 && v[i].second.second == 0)
        return ans;
    // Only right child exists
    else if (v[i].second.first == 0)
        ans = dfs(v, v[i].second.second) + b;
    // Only left child exists
    else if (v[i].second.second == 0)
        ans = dfs(v, v[i].second.first) + a;
    // Both children exist, take minimum path
    else
        ans = min(dfs(v, v[i].second.first) + a, dfs(v, v[i].second.second) + b);
    
    return ans;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // Vector to store node info: {character, {left_child, right_child}}
    vector<pair<char, pair<int, int>>> v(n + 1);
    v[0].second.first = 0, v[0].second.second = 0;
    
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        v[i].first = s[i - 1];
        v[i].second.first = a;
        v[i].second.second = b;
    }
    
    int ans = dfs(v, 1);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tt;
    cin >> tt;
    while (tt--)
        solve();
    
    return 0;
}


// https://github.com/VaHiX/CodeForces/