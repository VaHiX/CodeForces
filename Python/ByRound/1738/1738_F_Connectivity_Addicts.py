# Problem: CF 1738 F - Connectivity Addicts
# https://codeforces.com/contest/1738/problem/F

"""
Algorithm: Union-Find (DSU) with Greedy Coloring
Approach:
    - For each vertex, we process vertices in decreasing order of their degrees.
    - For each vertex, we greedily expand its component by querying its neighbors until 
      the sum of degrees (score) in the component is at most the square of the number of vertices in it.
    - This ensures that for every color class, the connectivity and the constraint s_c <= n_c^2 are satisfied.

Time Complexity: O(n^2 * alpha(n)) where n is the number of vertices and alpha(n) is the inverse Ackermann function.
Space Complexity: O(n) for the DSU structure and auxiliary arrays.

The solution uses a Disjoint Set Union (DSU) data structure to efficiently manage connected components.
At each step, we query the graph to find neighbors and extend components until the required condition is met.
"""

class DSF:
    def __init__(self, n: int) -> None:
        # Initialize parent array for DSU
        self.par = [i for i in range(n)]
        # Initialize size array for DSU
        self.siz = [1] * n
        # Initialize score array (sum of degrees) for DSU
        self.sco = [0] * n

    def root(self, x: int) -> int:
        # Find root with path compression
        while self.par[x] != x:
            self.par[x] = self.par[self.par[x]]
            x = self.par[x]
        return x

    def union(self, x: int, y: int) -> bool:
        # Union two components and update size and score
        x = self.root(x)
        y = self.root(y)
        if x == y:
            return False
        if self.siz[x] < self.siz[y]:
            x, y = y, x
        self.siz[x] += self.siz[y]
        self.sco[x] += self.sco[y]
        self.par[y] = x
        return True

    def same(self, x: int, y: int) -> bool:
        # Check if two vertices are in the same component
        return self.root(x) == self.root(y)

    def size(self, x: int) -> int:
        # Return size of component containing x
        return self.siz[self.root(x)]

    def score(self, x: int) -> int:
        # Return score (sum of degrees) of component containing x
        return self.sco[self.root(x)]


for _ in range(int(input())):
    n = int(input())
    dsu = DSF(n)
    # Read degrees of all vertices
    dsu.sco = list(map(int, input().split()))
    # Create list of (degree, vertex) pairs for sorting
    X = [(dsu.sco[i], i) for i in range(n)]
    # Sort by degree in descending order
    X.sort(key=lambda x: x[0], reverse=True)
    # Process each vertex in order of decreasing degree
    for _, c in X:
        # While constraint s_c > n_c^2, expand component
        while dsu.size(c) ** 2 < dsu.score(c):
            print("?", c + 1)  # Query vertex c
            dsu.union(c, int(input()) - 1)  # Add neighbor to component
    # Output final coloring
    print("!", *[dsu.root(i) + 1 for i in range(n)])


# https://github.com/VaHiX/CodeForces/