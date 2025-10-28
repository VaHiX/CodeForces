# Problem: CF 1903 F - Babysitting
# https://codeforces.com/contest/1903/problem/F

"""
Algorithm: Binary Search + DFS-based Graph Coloring
Time Complexity: O(n * m * log(n))
Space Complexity: O(n + m)

This code solves a problem where we need to find the maximum possible minimum
difference between indices of chosen nodes in a vertex cover of a graph. 
It uses binary search on the answer combined with a graph coloring approach,
which is used to check if a vertex cover with a given minimum difference is possible.

The key idea is to try different minimum differences using binary search,
and for each difference, determine if there's a valid vertex cover using
a modified DFS-based coloring algorithm.
"""

def binary_search(f, l, h):
    # Binary search to find the maximum value for which f returns True
    while l + 1 < h:
        mid = (l + h) // 2
        if f(mid):
            l = mid
        else:
            h = mid
    return l


class RestoreableArray:
    # A wrapper around a list that supports restore operations
    def __init__(s, arr):
        s.arr = arr
        s.edits = dict()

    def __getitem__(s, i):
        return s.arr[i]

    def __setitem__(s, i, v):
        # Keep track of changes to allow later restoration
        if i not in s.edits:
            s.edits[i] = s.arr[i]
        s.arr[i] = v

    def restore(s):
        # Restore all changes made since the last apply
        for i, v in s.edits.items():
            s.arr[i] = v
        s.edits.clear()

    def apply(s):
        # Mark current state as committed
        s.edits.clear()


def try_substitute(edges, gap, value, Lt, Rt, i, val):
    # Try to assign a value (True or False) to node i and propagate
    assert value[i] is None
    value[i] = val
    n = len(edges)
    dfs = [i]
    while dfs:
        i = dfs.pop()
        val = value[i]
        assert val is not None
        if val is False:
            # If node i is not in vertex cover, then neighbors must be in it
            for v in edges[i]:
                if value[v] is False:
                    return False  # Conflict: two adjacent nodes both not in cover
                if value[v] is None:
                    value[v] = True
                    dfs.append(v)
        elif val is True:
            # If node i is in vertex cover, check bounds for assignment
            for sgn, L in [(1, Lt), (-1, Rt)]:
                bound = max(min(i + sgn * (gap + 1), n), -1)
                for v in range(i + sgn, bound, sgn):
                    if value[v] is None:
                        # Assign a node with gap constraint
                        L[v] = i
                        dfs.append(v)
                        value[v] = False
                    elif value[v] is True:
                        return False  # Conflict
                    elif value[v] is False:
                        # If already assigned, check if constraints are violated
                        if L[v] is not None:
                            return False
                        L[v] = i
                        value[v] = False
    return True


def can_cover(edges, gap):
    # Check if a valid vertex cover exists with minimum difference at least gap+1
    n = len(edges)
    value = RestoreableArray([None for i in range(n)])
    Lt = RestoreableArray([None for i in range(n)])
    Rt = RestoreableArray([None for i in range(n)])
    for i in range(n):
        if value[i] is None:
            # Try both assignments (True or False) for unvisited nodes
            for val in [False, True]:
                if try_substitute(edges, gap, value, Lt, Rt, i, val):
                    value.apply()
                    Lt.apply()
                    Rt.apply()
                    break
                else:
                    value.restore()
                    Lt.restore()
                    Rt.restore()
            else:
                return False  # No valid assignment possible
    return True


def solve(edges):
    # Use binary search to find the maximum minimum difference
    n = len(edges)
    return binary_search(lambda gap: can_cover(edges, gap - 1), 1, n + 1)


def f1903():
    # Main function to read input and process test cases
    t = int(input())
    for i in range(t):
        n, m = [int(x) for x in input().split()]
        edges = [[] for j in range(n)]
        for j in range(m):
            u, v = [int(x) for x in input().split()]
            u -= 1
            v -= 1
            edges[u].append(v)
            edges[v].append(u)
        print(solve(edges))


f1903()


# https://github.com/VaHiX/CodeForces/