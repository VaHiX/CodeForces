// Problem: CF 657 A - Bear and Forgotten Tree 3
// https://codeforces.com/contest/657/problem/A

/*
 * Problem: Bear and Forgotten Tree 3
 * 
 * Purpose: 
 *   This program checks if there exists a tree with n vertices, 
 *   diameter d, and height h when rooted at vertex 1. If such a tree exists,
 *   it outputs the edges of the tree; otherwise, it outputs -1.
 * 
 * Algorithm:
 *   - The program uses a greedy construction method:
 *     1. It creates a path of length d starting from vertex 1.
 *     2. From the vertex at distance h from root, it adds branches to other nodes.
 *     3. It ensures that the resulting tree satisfies all conditions:
 *        - diameter is d,
 *        - height is h,
 *        - and it has n vertices.
 *
 * Time Complexity: O(n)
 *   The algorithm iterates through all vertices once to construct the edges.
 *
 * Space Complexity: O(1)
 *   Only a constant amount of extra space is used, excluding the output.
 */

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
    int n, d, h;
    cin >> n >> d >> h;
    
    // Check if the given parameters are impossible to satisfy:
    // 1. If h is less than ceil(d/2), impossible to form a diameter of d.
    // 2. If d is less than h, impossible.
    // 3. Special case when n > 2 and d == 1, impossible to form a diameter of 1 with > 2 nodes.
    if (d - d / 2 > h || d / 2 > h || (n > 2 && d == 1))
        return cout << -1, 0;
    
    // Construct the tree:
    // Loop from 1 to n-1 to generate n-1 edges
    for (int c = 1; c < n; 
         printf("%d %d\n", ++c,
                (c - 1 == h && d != h ? 1  // If we're at the vertex that must be connected to root, connect to 1
                 : c > d              ? 2 - (h == 1)  // If beyond diameter, connect to 2 (unless h=1)
                                      : c)))  // Otherwise connect to the previous vertex
        if (c > d && d >= n - 1)  // Break if we're beyond diameter and also not enough nodes left
            break;
    
    return 0;
}


// https://github.com/VaHiX/CodeForces/