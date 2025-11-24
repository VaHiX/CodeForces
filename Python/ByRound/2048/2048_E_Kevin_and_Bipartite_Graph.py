# Problem: CF 2048 E - Kevin and Bipartite Graph
# https://codeforces.com/contest/2048/problem/E

"""
Algorithm: Bipartite Graph Edge Coloring to Avoid Monochromatic Cycles

Purpose:
This code solves the problem of coloring edges in a bipartite graph with colors from [1,n] such that no monochromatic cycle exists.
The bipartite graph has 2n vertices on the left and m vertices on the right, and all vertices on the left are connected to all vertices on the right (complete bipartite graph).

Approach:
- The key insight is that a complete bipartite graph cannot have a monochromatic cycle if we color the edges properly.
- We use a specific coloring pattern based on the relationship between n and m:
  1. If m == 1, color all edges with color 1.
  2. If m <= n, assign colors 1 to m cyclically to each row of the left vertices.
  3. If n < m < 2*n, use a more sophisticated assignment to avoid cycles.
  4. If m >= 2*n, it is impossible to avoid monochromatic cycles in any valid coloring, return "NO".

Time Complexity: O(n * m) 
Space Complexity: O(n * m)

Techniques:
- Greedy edge coloring with specific patterns to avoid monochromatic cycles
- Modular arithmetic for indexing
"""

file = False

if __name__ == "__main__":
    if file:
        file_path = "CF_GR_28/inputs/e.txt"
        lines = iter(open(file_path, "r").read().splitlines())
        get_input = lambda: next(lines)
    else:
        get_input = input

    n_test_cases = int(get_input())
    for _ in range(n_test_cases):
        n, m = map(int, get_input().split())
        if m == 1:
            out = [1] * (2 * n)
            print("YES")
            print("\n".join(map(str, out)))
            continue
        if m <= n:
            # For m <= n, we can assign each row of left vertices a different set of colors
            out = [list(range(1, m + 1))] * (2 * n)
            print("YES")
            print("\n".join(" ".join(map(str, edge)) for edge in out))
            continue
        if m < 2 * n:
            # For n < m < 2*n, we use specific coloring pattern with modulo arithmetic
            out = [[-1 for _ in range(m)] for _ in range(2 * n)]
            for i in range(n):
                for j in range(m):
                    # Assign color i+1 to two rows in a cyclic manner to prevent monochromatic cycles
                    out[(2 * i + j) % (2 * n)][j] = i + 1
                    out[(2 * i + j + 1) % (2 * n)][j] = i + 1
            print("YES")
            print("\n".join(" ".join(map(str, edge)) for edge in out))
            continue
        print("NO")


# https://github.com/VaHiX/CodeForces/