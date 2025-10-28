# Problem: CF 2023 C - C+K+S
# https://codeforces.com/contest/2023/problem/C

"""
C+K+S Problem

This problem deals with matching edges between two strongly connected directed graphs such that:
- Each vertex in graph 1 has exactly one outgoing edge (if it's outgoing)
- Each vertex in graph 2 has exactly one incoming edge (if it's incoming)
- The resulting graph maintains cycle lengths divisible by k
- Edges go from one graph to another

Algorithm Overview:
1. Use coloring BFS to determine color classes for each vertex in both graphs such that all cycles have length divisible by k.
2. For each graph, build a frequency vector of the color classes based on vertex types (incoming/outgoing).
3. Apply Z-algorithm to check if there's a valid assignment of colors between the two graphs that avoids creating cycles of length not divisible by k.

Time Complexity: O(n + m1 + m2)
Space Complexity: O(n + m1 + m2)

Algorithms Used:
- BFS for graph coloring (mod k)
- Z-algorithm for pattern matching in frequency arrays
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def z_algo(S):
    # Z-algorithm to find matches of a pattern within a string in O(n) time.
    N = len(S)
    A = [0] * N
    i = 1
    j = 0
    A[0] = l = len(S)
    while i < l:
        while i + j < l and S[j] == S[i + j]:
            j += 1
        if not j:
            i += 1
            continue
        A[i] = j
        k = 1
        while l - i > k < j - A[k]:
            A[i + k] = A[k]
            k += 1
        i += k
        j -= k
    return A


def f(n, k, edge):
    # BFS to color all nodes in a graph with colors mod k such that cycles are divisible by k.
    seen = [-1] * n
    seen[0] = 0  # Start with color 0 for node 0
    todo = [0]
    while todo:
        v = todo.pop()
        for u in edge[v]:
            if seen[u] == -1:  # If not yet colored
                seen[u] = (seen[v] + 1) % k  # Set next color in cycle
                todo.append(u)
    return seen


def g(n, X, Y):
    # Z-algorithm application on concatenated strings to detect valid alignments.
    z = z_algo(X + Y + Y)
    ok = [0] * n
    for i in range(n):
        if z[i + n] >= n:
            ok[i] = 1
    return ok


def solve():
    n, k = map(int, input().split())
    a1 = list(map(int, input().split()))
    edge1 = [[] for i in range(n)]
    m1 = int(input())
    for _ in range(m1):
        x, y = map(lambda x: int(x) - 1, input().split())  # Convert to 0-indexed
        edge1[x].append(y)
    a2 = list(map(int, input().split()))
    m2 = int(input())
    edge2 = [[] for i in range(n)]
    for _ in range(m2):
        x, y = map(lambda x: int(x) - 1, input().split())  # Convert to 0-indexed
        edge2[x].append(y)
    
    if sum(a1) + sum(a2) != n:
        print("NO")
        return
    if sum(a1) == n or sum(a2) == n:
        print("YES")
        return

    col1 = f(n, k, edge1)
    col2 = f(n, k, edge2)

    v1 = [0] * k
    v2 = [0] * k

    # Build frequency vectors for color classes in both graphs based on vertex types (i.e., in/out).
    for i in range(n):
        if a1[i] == 0:
            # For incoming vertices, we subtract 2 to offset the modulo.
            v1[col1[i] - 2] += n + 1
        else:
            v1[col1[i]] += 1
        if a2[i] == 0:
            v2[col2[i]] += 1
        else:
            v2[col2[i]] += n + 1

    # Use Z-algorithm to check compatibility of the two frequency vectors.
    print("YES" if k in z_algo(v1 + [-1] + v2 * 2) else "NO")


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/