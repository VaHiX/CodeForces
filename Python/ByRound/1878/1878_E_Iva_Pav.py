# Problem: CF 1878 E - Iva & Pav
# https://codeforces.com/contest/1878/problem/E

"""
Algorithm: 
- For each starting index l from right to left, we compute the bitwise AND of subarrays starting at l.
- We optimize by only updating elements that can contribute to a larger AND value.
- For each query (l, k), we binary search for the maximum r such that f(l, r) >= k.
- The key optimization is to precompute the AND values in a way that allows efficient queries.

Time Complexity: O(n * log(n) + q * log(n)) where n is the array size and q is the number of queries.
Space Complexity: O(n + q) for storing the array, queries, and results.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    q = int(input())
    qs = [[] for _ in range(n)]
    for i in range(q):
        l, k = map(int, input().split())
        qs[l - 1].append((i, k))  # Store queries indexed by starting position (0-based)
    ans = ["-1"] * q
    for l in range(n - 1, -1, -1):  # Traverse from right to left
        x = a[l]
        # Optimize the array a by updating consecutive elements
        for j in range(l + 1, n):
            if x & a[j] == a[j]:
                break  # Stop if the new AND equals the current element
            a[j] &= x  # Update a[j] to reflect the AND with a[l]
        for i, k in qs[l]:  # Process all queries starting at l
            left, right = l, n - 1
            # Binary search for the maximum r such that a[r] >= k
            while left <= right:
                mid = (left + right) // 2
                if a[mid] >= k:
                    left = mid + 1
                else:
                    right = mid - 1
            if right >= l:
                ans[i] = str(right + 1)
    print(" ".join(ans))


# https://github.com/VaHiX/CodeForces/