# Problem: CF 1783 F - Double Sort II
# https://codeforces.com/contest/1783/problem/F

"""
Algorithm: Double Sort II
Purpose: Sort two permutations A and B using minimum operations, where each operation swaps elements in both permutations based on a chosen index i.

Approach:
1. Find cycles in permutation A and B.
2. Model the problem as a bipartite matching problem between cycles.
3. Use Kuhn's algorithm (Hungarian algorithm for bipartite matching) to find minimum vertex cover.
4. Output indices that are not covered by the matching as the minimum operations needed.

Time Complexity: O(n^3) due to Kuhn's algorithm in bipartite matching
Space Complexity: O(n^2) for the adjacency matrix in the bipartite graph

Techniques:
- Cycle decomposition in permutations
- Bipartite matching with Kuhn's algorithm
- Minimum vertex cover via maximum matching
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

N = int(input())
A = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed
B = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed


def find_cycle(arr):
    sz = 0
    comp = [-1] * N  # component id for each element
    cycles = []
    for i, a in enumerate(arr):
        if comp[i] == -1:
            curr = [i]
            comp[i] = sz
            j = a
            while comp[j] == -1:
                curr.append(j)
                comp[j] = sz
                j = arr[j]
            cycles.append(curr)
            sz += 1
    return [comp, cycles]  # comp maps element to cycle id, cycles stores each cycle


X, cx = find_cycle(A)  # X: component id for A, cx: list of cycles in A
Y, cy = find_cycle(B)  # Y: component id for B, cy: list of cycles in B
n = len(cx)  # number of cycles in A
k = len(cy)  # number of cycles in B

# Build bipartite graph between cycles of A and B
G = [[] for _ in range(n)]
for i in range(N):
    G[X[i]].append(Y[i])  # Connect cycle id of A[i] to cycle id of B[i]

mt = [-1] * k  # mt[u] = v means u in B is matched to v in A


def khun(v):
    # Kuhn's algorithm for finding augmenting path
    if used[v]:
        return False
    used[v] = True
    for u in G[v]:
        if mt[u] == -1 or khun(mt[u]):  # if u is unmatched or can find augmenting path
            mt[u] = v
            return True
    return False


# Find maximum matching using Kuhn's algorithm
for v in range(n):
    used = [False] * n
    khun(v)

match = [False] * N  # mark indices that are matched to a cycle in B

# For each matched B-cycle, find intersection with cycles in A to mark indices that will be fixed
for i in range(k):
    if mt[i] != -1:
        for digit in cx[mt[i]]:  # iterate over elements in A-cycle
            if digit in cy[i]:  # if this element also in B-cycle
                match[digit] = True
                break

# Indices that are not marked must be operated on
res = [i + 1 for i in range(N) if not match[i]]  # convert back to 1-indexed

print(len(res))
print(" ".join(map(str, res)))


# https://github.com/VaHiX/CodeForces/