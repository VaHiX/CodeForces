# Problem: CF 1702 E - Split Into Two Sets
# https://codeforces.com/contest/1702/problem/E

"""
Algorithm: Union-Find (Disjoint Set Union) + Graph Analysis
Purpose: Determine if a set of dominoes can be split into two groups such that no number appears twice in either group.

The problem reduces to checking whether the dominoes form a collection of cycles where each node has degree 2, 
and we can color the edges in two colors such that no two adjacent edges share the same color. This is equivalent 
to checking if the graph is composed of cycles of even length.

Time Complexity: O(n * α(n)) where α(n) is the inverse Ackermann function, nearly constant.
Space Complexity: O(n) for the Union-Find structure and auxiliary arrays.

Approach:
1. For each domino (u, v), we increment the degree count of both u and v.
2. We perform Union-Find operations to group connected components.
3. We count how many nodes belong to each component.
4. Check if all components are cycles of even length and all nodes have degree 2.
"""

R = lambda: map(int, input().split())
(t,) = R()


def find(i):
    # Find root of the component with path compression
    while fa[i] != i:
        fa[i] = fa[fa[i]]  # Path compression
        i = fa[i]
    return i


while t:
    t -= 1
    (n,) = R()
    n += 1  # Adjust for 1-based indexing
    z = "YES"
    fa = list(range(n))  # Union-Find parent array
    c, sons = [0] * n, [0] * n  # c: degree count, sons: component size
    
    # Read dominoes and build graph
    for _ in range(n - 1):
        u, v = R()
        c[u] += 1  # Increment degree of u
        c[v] += 1  # Increment degree of v
        fa[find(u)] = find(v)  # Union u and v
    
    # Count number of nodes in each component
    for i in range(1, n):
        sons[find(i)] += 1
    
    # Validate conditions for splitting: 
    # Each node must have degree 2, and each component must be even-sized
    for i in range(1, n):
        if sons[i] & 1 or c[i] != 2:  # If component size is odd or node degree is not 2
            z = "NO"
            break
    
    print(z)


# https://github.com/VaHiX/CodeForces/