// Problem: CF 1926 F - Vlad and Avoiding X
// https://codeforces.com/contest/1926/problem/F

/*
Algorithm: Backtracking with memoization
Time Complexity: O(2^k) where k is the number of black cells that form the forbidden pattern
Space Complexity: O(1) as we use fixed size 7x7 grid and recursion stack depth is bounded

Approach:
1. Identify all black cells that have all four diagonal neighbors also black (forbidden pattern)
2. Split these cells into two groups based on (i+j) % 2 to avoid conflicts
3. Use backtracking to find minimum operations by trying to flip each cell in groups
4. For each forbidden pattern, try flipping any of the 4 involved cells to break the pattern
5. Return minimum operations required to eliminate all forbidden patterns
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <stddef.h>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <functional>
#include <iterator>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimization("O3")
#pragma GCC optimization("tree-vectorize")

#define int long long
#define INF 1000000007
#define PI 3.14159265358979323846
#define cinarr(arr, n) fr(i, 0, n) cin >> arr[i];
#define coutarr(arr, n) fr(i, 0, n) cout << arr[i] << " ";
#define vall(arr) arr.begin(), arr.end()

using namespace std;

// Helper function to find if a cell is part of forbidden pattern
bool isForbidden(int i, int j, vector<vector<char>>& arr) {
    return (arr[i][j] == 'B' && arr[i - 1][j - 1] == 'B' &&
            arr[i - 1][j + 1] == 'B' && arr[i + 1][j - 1] == 'B' &&
            arr[i + 1][j + 1] == 'B');
}

// Recursive backtracking function to find minimum operations
int f(vector<pair<int, int>>& v, int ind, vector<vector<char>>& arr) {
    // Base case: no more forbidden patterns to process
    if (ind >= v.size())
        return 0;
    
    int i = v[ind].first;
    int j = v[ind].second;
    
    // If current pattern is not present, skip this cell
    if (!isForbidden(i, j, arr)) {
        return f(v, ind + 1, arr);
    }
    
    int ans = INF;
    
    // Try flipping the center cell
    arr[i][j] = 'W';
    ans = min(ans, 1 + f(v, ind + 1, arr));
    arr[i][j] = 'B';
    
    // Try flipping the top-right cell
    arr[i - 1][j + 1] = 'W';
    ans = min(ans, 1 + f(v, ind + 1, arr));
    arr[i - 1][j + 1] = 'B';
    
    // Try flipping the bottom-left cell
    arr[i + 1][j - 1] = 'W';
    ans = min(ans, 1 + f(v, ind + 1, arr));
    arr[i + 1][j - 1] = 'B';
    
    // Try flipping the bottom-right cell
    arr[i + 1][j + 1] = 'W';
    ans = min(ans, 1 + f(v, ind + 1, arr));
    arr[i + 1][j + 1] = 'B';
    
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int tt;
    cin >> tt;
    while (tt--) {
        int n = 7;
        vector<vector<char>> arr(7, vector<char>(7));
        
        // Read input grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }
        
        vector<pair<int, int>> v, v2; // Split forbidden cells into two groups
        
        // Identify forbidden patterns and group them
        for (int i = 1; i < n - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (isForbidden(i, j, arr)) {
                    // Group cells based on parity of (i+j) to avoid conflicts
                    if ((i + j) % 2)
                        v.push_back({i, j});
                    else
                        v2.push_back({i, j});
                }
            }
        }
        
        // Calculate minimum operations for both groups
        cout << f(v, 0, arr) + f(v2, 0, arr) << '\n';
    }
    return 0;
}


// https://github.com/VaHiX/CodeForces/