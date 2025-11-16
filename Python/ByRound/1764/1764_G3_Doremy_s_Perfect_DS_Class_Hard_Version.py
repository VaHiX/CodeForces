# Problem: CF 1764 G3 - Doremy's Perfect DS Class (Hard Version)
# https://codeforces.com/contest/1764/problem/G3

"""
Algorithm: Find the index y such that p_y = 1 in a permutation p of size n using at most 20 queries.
Technique: Binary search with a clever trick involving floor division queries.
Time Complexity: O(log n) per query, total O(log n * 20) = O(log n)
Space Complexity: O(1) for variables, O(20) for memoization (bounded by 20 queries)
"""

save = {}


def query(l, r, k):
    # Memoization to avoid repeated queries
    if r == l:
        return 0
    if r - l == n:
        return n // k + 1
    if not (l, r, k) in save:
        print("?", l + 1, r, k)
        save[(l, r, k)] = int(input())
    return save[(l, r, k)]


def submit(y):
    # Output the answer
    print("!", y + 1)


n = int(input())
big = -1


def unpaired(l, r):
    # Helper function to compute a value that helps determine where 1 lies
    # Based on the difference of distinct elements in floor division queries
    return 2 * query(l, r, 2) - (r - l) - (l <= big < r)


L = 0
R = n
while R - L > 2:
    M = (L + R) // 2
    left = unpaired(0, M)
    right = unpaired(M, n)

    if left == right:
        # If both sides give same result, we have a special case
        if (M == 1 and query(M, n, n) == 2) or (M > 1 and query(0, M, n) == 1):
            big = n - 1
            R = M
        else:
            big = 0
            L = M
    elif left < right:
        # If left side is smaller, the element 1 must be on the right
        L = M
    else:
        # If left side is larger, the element 1 must be on the left
        R = M

# Final check when the interval is small
if R - L == 2:
    M = L + 1
    if n % 2 == 0 and big == -1:
        # Special handling for even n
        if (M == 1 and query(M, n, n) == 2) or (M > 1 and query(0, M, n) == 1):
            submit(L)
        else:
            submit(L + 1)
    elif unpaired(0, L) + unpaired(L, n) < unpaired(0, R) + unpaired(R, n):
        # Choose based on which split yields more information
        if unpaired(M, n) < unpaired(R, n):
            submit(L)
        else:
            submit(L + 1)
    else:
        # Choose based on the left side split
        if unpaired(0, M) < unpaired(0, L):
            submit(L + 1)
        else:
            submit(L)
else:
    # Exact middle point
    submit(L)


# https://github.com/VaHiX/CodeForces/