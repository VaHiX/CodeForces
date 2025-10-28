// Problem: CF 2029 D - Cool Graph
// https://codeforces.com/contest/2029/problem/D

/*
 * Purpose: Solve the "Cool Graph" problem where we must transform a given undirected graph into either a tree or an empty graph
 *          using at most 2 * max(n, m) operations. Each operation toggles the existence of edges between three vertices forming a triangle.
 *
 * Algorithms/Techniques:
 * - Graph transformation using triangle flips
 * - Degree tracking using XOR (bit manipulation)
 * - Greedy selection for building a spanning tree or empty graph
 *
 * Time Complexity:
 * - O(n + m) per test case due to one pass through vertices and edges
 * - Total over all test cases: O(n + m) where n and m are total vertices and edges
 *
 * Space Complexity:
 * - O(n + m) for storing the graph information and operations list
 */

#include <stdio.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int n, m, t[100005]; // t[] tracks the degree parity (XOR) of each vertex
vector<array<int, 3>> ans; // Stores the operations performed

// Function to record an operation on three vertices
void op(int x, int y, int z) { 
    ans.push_back({x, y, z}); 
}

// Function to process one test case
void doing() {
    cin >> n >> m;
    // Reset the degree array
    for (int i = 1; i <= n; i++)
        t[i] = 0;
    
    // Process each edge in the input graph
    for (int i = 1, j, k; i <= m; i++) {
        scanf("%d %d", &j, &k);
        // Ensure j <= k for consistent processing
        if (j > k)
            swap(j, k);
        // If j is not 1, perform an operation on (1, j, k) to eliminate the edge
        if (j > 1)
            op(1, j, k);
        // Toggle the degree parity for both vertices
        t[j] ^= 1, t[k] ^= 1;
    }

    // Find a vertex with odd degree (if exists)
    int p = 0;
    for (int i = 2; i <= n; i++)
        if (t[i])
            p = i;
    
    // If a vertex with odd degree exists, make it even by pairing it with others
    if (p)
        for (int i = 2; i <= n; i++)
            if (!t[i])
                op(1, p, i), p = i;
    
    // Output the number of operations
    cout << ans.size() << "\n";
    // Output each operation in the required format
    for (auto i : ans)
        printf("%d %d %d\n", i[0], i[1], i[2]);
    ans.clear(); // Reset for next test case
}

int main() {
    int T;
    cin >> T;
    while (T--)
        doing();
}


// https://github.com/VaHiX/CodeForces/