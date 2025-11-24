// Problem: CF 2081 D - MST in Modulo Graph
// https://codeforces.com/contest/2081/problem/D

/*
D. MST in Modulo Graph
Algorithms/Techniques: Union-Find (Disjoint Set Union), Minimum Spanning Tree (Kruskal's Algorithm), Frequency Counting Sort

Time Complexity: O(N log N + L), where N is the number of unique elements and L is the maximum value in input array.
Space Complexity: O(L), for storing auxiliary arrays up to the maximum value.

The problem involves constructing a complete graph with specific edge weights defined by modulo operations,
and finding the MST. The key insight is to precompute valid edges and apply Kruskal's algorithm with Union-Find.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 5e5 + 5;
int T, n, a[N], f[N], l, m, r[N], c[N], fa[N], ans;
struct edge {
    int u, v, w;
} _e[N * 15], e[N * 15];

int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

int main() {
    cin >> T;
    while (T--) {
        scanf("%d", &n), l = m = ans = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]), f[a[i]] = 1, l = max(l, a[i]); // Mark which numbers appear and find max
        n = 0;
        for (int i = 1; i <= l; i++)
            if (f[i])
                a[++n] = i; // Collect unique sorted values
        for (int i = 1; i < n; i++)
            _e[++m] = (edge){a[i], a[i + 1], a[i + 1] % a[i]}; // Connect consecutive elements
        for (int i = l; i; i--)
            r[i] = f[i] ? i : r[i + 1], f[i] = 0; // Precompute rightmost occurrence, reset f array
        for (int i = 1; i <= n; i++)
            for (int j = a[i] << 1; j <= l; j += a[i])
                if (r[j] - j < a[i])
                    _e[++m] = (edge){a[i], r[j], r[j] - j}; // Add edges based on divisibility and modulo properties
        for (int i = 1; i <= m; i++)
            c[_e[i].w]++; // Count frequency of each weight
        for (int i = 1; i <= l; i++)
            c[i] += c[i - 1]; // Prefix sum to get final positions in sorted order
        for (int i = m; i; i--)
            e[c[_e[i].w]--] = _e[i]; // Sort edges by weight using counting sort
        for (int i = 1; i <= l; i++)
            fa[i] = i, c[i] = 0; // Initialize Union-Find structure
        for (int i = 1, t = 0; i <= m && t < n - 1; i++) {
            int u = find(e[i].u), v = find(e[i].v);
            if (u ^ v)
                fa[v] = u, t++, ans += e[i].w; // Apply Kruskal's algorithm
        }
        printf("%d\n", ans);
    }
}


// https://github.com/VaHiX/codeForces/