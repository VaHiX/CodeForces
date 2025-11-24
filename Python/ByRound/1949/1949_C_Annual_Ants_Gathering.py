# Problem: CF 1949 C - Annual Ants' Gathering
# https://codeforces.com/contest/1949/problem/C

"""
Algorithm: Tree-based greedy approach to determine if all ants can be gathered into one house.
Techniques: 
- Greedy merging of leaf nodes into their neighbors.
- Using degree and ant count to decide movement priorities.
- Tracking leaf nodes with their ant counts in a list of lists.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by iteratively merging leaf nodes into their neighbors, 
always moving ants from a leaf to its neighbor if the neighbor has more ants (or equal).
If at any point a leaf has more ants than its neighbor, it's impossible to gather all ants.
"""

from sys import stdin


def can_gather(tree):
    n = len(tree)
    ant_count = [1] * n  # Every house starts with 1 ant
    leafs = [[], [v for v in range(n) if len(tree[v]) == 1]]  # Initialize leafs list, indexed by ant count
    deg = list(map(len, tree))  # Degree of each node
    min_cnt = 1  # Minimum ant count with active leaf nodes
    for t in range(n - 1):  # For each merge operation
        while not leafs[min_cnt]:  # Find next non-empty level of leafs
            min_cnt += 1
        v = leafs[min_cnt].pop()  # Get a leaf node
        (u,) = (x for x in tree[v] if ant_count[x] > 0)  # Find neighbor u with ants

        if ant_count[v] > ant_count[u]:  # If v has more ants than u, impossible to merge
            return False

        ant_count[u] += ant_count[v]  # Merge ants from v to u
        ant_count[v] = 0  # Clear ants from v
        deg[u] -= 1  # Reduce degree of u
        if deg[u] == 1:  # If u becomes a leaf
            while len(leafs) <= ant_count[u]:  # Extend leafs list if needed
                leafs.append([])
            leafs[ant_count[u]].append(u)  # Add u to leafs at its ant count level
    return True


n = int(stdin.readline())
tree = [[] for i in range(n)]
for i in range(n - 1):
    a, b = [int(w) - 1 for w in stdin.readline().split()]
    tree[a].append(b)
    tree[b].append(a)

print(["NO", "YES"][can_gather(tree)])


# https://github.com/VaHiX/CodeForces/