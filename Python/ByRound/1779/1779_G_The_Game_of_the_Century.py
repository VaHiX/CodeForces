# Problem: CF 1779 G - The Game of the Century
# https://codeforces.com/contest/1779/problem/G

"""
Code Purpose:
This code solves the problem of finding the minimum number of road segments to reverse in a triangular village grid such that every intersection is reachable from every other intersection. The village is structured as an equilateral triangle with roads forming a grid of smaller triangles, and each road segment has a fixed direction. The goal is to make the graph strongly connected by reversing the minimum number of edges.

Algorithms/Techniques:
- Graph traversal techniques for connectivity
- Greedy approach with observation about triangle structure
- Bit manipulation and modular arithmetic
- Preprocessing and filtering based on parity and orientation

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing input grid
"""

res = []
for _ in range(int(input())):
    n = int(input())
    g = [[int(t) for t in input()] for _ in range(3)]

    # If the last elements of all three rows are the same, no changes needed
    if g[0][-1] == g[1][-1] == g[2][-1]:
        res.append(0)
        continue

    # Calculate sum of last elements of each row
    S = g[0][-1] + g[1][-1] + g[2][-1]

    # Find index of row where last element is not equal to S // 2
    h = 0
    for i in range(1, 3):
        if not g[i][-1] == S // 2:
            h = i
            break

    # For each row, find the farthest (from the end) element that is different from the last element
    run = []
    for i in range(3):
        lastocc = -1
        for t in range(n - 1):
            if g[i][t] == 1 ^ g[i][-1]:  # XOR checks if different
                lastocc = t
        run.append(n - 1 - lastocc)

    # Compute minimum cost using two strategies
    ans = min(run[h], run[(h + 1) % 3])
    ans2 = min(run[h], run[(h + 2) % 3])
    res.append(min(n, ans + ans2))


print(*res)


# https://github.com/VaHiX/CodeForces/