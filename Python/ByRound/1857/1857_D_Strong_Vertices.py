# Problem: CF 1857 D - Strong Vertices
# https://codeforces.com/contest/1857/problem/D

"""
Purpose: 
    Find all "strong vertices" in a directed graph constructed from two arrays a and b.
    An edge exists from vertex u to v if a[u] - a[v] >= b[u] - b[v].
    A vertex is strong if there's a path from it to all other vertices.
    
    Key Insight:
        The condition a[u] - a[v] >= b[u] - b[v] can be rewritten as:
        (a[u] - b[u]) >= (a[v] - b[v]).
        This means we can define a value d[i] = a[i] - b[i].
        Then there is an edge from u to v if d[u] >= d[v].
        
    Algorithm:
        1. Compute d[i] = a[i] - b[i] for all i.
        2. Find the maximum value of d.
        3. All vertices i where d[i] equals the maximum are strong vertices.
           (Because they can reach all other vertices with smaller or equal d values).
    
    Time Complexity: O(n) per test case
    Space Complexity: O(n) for storing arrays and intermediate results
    
    This solution works because:
        - If d[u] >= d[v], then there exists an edge from u to v.
        - The maximum d value is the "top" of the DAG (with the highest d).
        - Any vertex with the maximum d can reach any vertex with a smaller d,
          and no vertex can reach a vertex with a larger d.
        - So only vertices with the maximum d value are strong.
"""

def main():
    import sys

    input = sys.stdin.readline
    out = []
    for _ in range(int(input())):
        int(input())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        # Compute d[i] = a[i] - b[i]
        dmax = max(ai - bi for ai, bi in zip(a, b))
        # Collect all vertices with maximum d value
        strong = [str(i + 1) for i, (ai, bi) in enumerate(zip(a, b)) if ai - bi == dmax]
        out.append(str(len(strong)))
        out.append(" ".join(strong))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/