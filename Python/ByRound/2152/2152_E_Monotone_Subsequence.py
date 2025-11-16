# Problem: CF 2152 E - Monotone Subsequence
# https://codeforces.com/contest/2152/problem/E

"""
Algorithm: Monotone Subsequence Finder
This code finds a monotone subsequence of length n+1 in a hidden permutation of length n^2+1.
It uses a greedy approach with "skyscraper queries" to identify visible elements and construct the subsequence.

Key Techniques:
- Greedy algorithm with skyscraper queries to identify visible elements
- Layer-based tracking of elements to build monotone subsequence
- Uses the Erdős–Szekeres theorem which guarantees existence of such a subsequence

Time Complexity: O(n^3) in worst case due to nested loops and querying
Space Complexity: O(n^2) for storing the permutation and layer tracking
"""
import sys

t = int(input())
for _ in range(t):
    n = int(input())
    # curr tracks which indices are still available for querying
    curr = [1] * (n * n + 1)

    def query():
        # Build list of available indices
        l = []
        for i in range(n * n + 1):
            if curr[i]:
                l.append(i + 1)
        # Query the interactor
        print("?", len(l), " ".join(map(str, l)))
        sys.stdout.flush()
        c, *out = map(int, input().split())
        # Return the indices of visible skyscrapers (convert to 0-indexed)
        return [v - 1 for v in out]

    # layer[i] tracks which "layer" (step) the element at index i belongs to
    layer = [n] * (n * n + 1)

    def fin(l):
        # Take first n+1 elements and verify they are in increasing order
        l = l[: n + 1]
        assert l == sorted(l)
        # Output the result in 1-indexed form
        print("!", " ".join(str(v + 1) for v in l))
        sys.stdout.flush()

    good = 0
    # Perform at most n queries
    for i in range(n):
        out = query()
        # Mark these indices as used and assign them to the current layer
        for v in out:
            layer[v] = i
            curr[v] = 0

        # If we found more than n visible skyscrapers, we have a subsequence of length > n
        if len(out) > n:
            fin(out)
            good = 1
            break

    # If no subsequence longer than n was found yet, continue building it
    if good:
        continue

    # Find the last index that belongs to the highest layer, then trace back
    assert n in layer
    out = [layer.index(n)]
    # Trace back through all layers to build the subsequence
    for i in range(n)[::-1]:
        c = out[-1]
        # Move backward until we find an element in the current layer
        while layer[c] != i:
            c -= 1
        out.append(c)

    # Output the final result in reverse order (since we traced back)
    fin(out[::-1])


# https://github.com/VaHiX/CodeForces/