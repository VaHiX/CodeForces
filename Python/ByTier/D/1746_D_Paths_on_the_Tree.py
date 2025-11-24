# Problem: CF 1746 D - Paths on the Tree
# https://codeforces.com/contest/1746/problem/D

"""
Algorithm: Tree Dynamic Programming with Topological Sort
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves assigning k paths starting from root to maximize a weighted sum,
where each node's contribution is weighted by how many paths cover it.
This is solved using topological sorting and dynamic Programming on the tree.

Key Techniques:
1. Topological sort to process nodes from leaves to root
2. Dynamic Programming to compute the number of paths covering each node
3. Greedy assignment of extra paths to maximize score

Approach:
1. Compute in-degrees and topologically sort nodes
2. For each node in reverse topological order:
   - Compute depth-weighted scores for its children
   - Distribute paths from parent to children
3. For each node in topological order:
   - Assign extra paths to maximize score contribution
   - Accumulate total value

The key insight is to greedily assign extra paths to children with highest scores.
"""

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())

    p = [0] + list(map(lambda x: int(x) - 1, input().split()))
    s = list(map(int, input().split()))

    # Compute in-degrees for topological sort
    ind = [0] * n
    for v in p[1:]:
        ind[v] += 1

    topo = []
    indc = ind[:]
    st = []
    for i in range(n):
        if ind[i] == 0:
            st.append(i)

    # Build child adjacency list
    ch = [[] for _ in range(n)]
    while st:
        u = st.pop()
        topo.append(u)

        if u == 0:
            continue

        indc[p[u]] -= 1
        if indc[p[u]] == 0:
            st.append(p[u])

        ch[p[u]].append(u)
    assert topo[-1] == 0

    # Compute depth-weighted scores for each node
    dep = [0] * n
    for u in topo[::-1]:
        dep[u] = dep[p[u]] + s[u]

    # Initialize coverage counts and extra assignment tracking
    c = [0] * n
    c[0] = k
    ex = [0] * n  # number of extra paths for each node
    nex = [0] * n  # updated next path count for each node

    out = 0

    # Process nodes in reverse topological order to distribute paths from parent to children
    for u in topo[::-1]:
        if ind[u] == 0:
            continue

        ex[u] = c[u] % ind[u]  # how many children should get one extra path
        drip = c[u] // ind[u]  # how many paths each child gets
        for v in ch[u]:
            c[v] = drip  # distribute paths to each child

    # Final processing to compute total value
    for u in topo:
        if ind[u] == 0:
            out += dep[u] * c[u]
            nex[u] = dep[u]
            continue

        # Get scores of all children
        poss = [nex[v] for v in ch[u]]
        poss.sort(reverse=True)  # sort in descending order for greedy assignment

        # Assign extra paths to maximize value
        out += sum(poss[: ex[u]])  # add contribution of extra paths
        nex[u] = poss[ex[u]]  # remaining maximum value after extra paths

    print(out)


# https://github.com/VaHiX/CodeForces/