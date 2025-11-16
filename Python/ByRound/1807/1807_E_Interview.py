# Problem: CF 1807 E - Interview
# https://codeforces.com/contest/1807/problem/E

"""
Algorithm: Binary Search on Pile Indices
Purpose: Find the pile containing the special stone (weighing 2 grams) among n piles,
         where each pile has a certain number of stones (each stone weighs 1 gram,
         except one special stone that weighs 2 grams).
         The solution uses binary search to minimize queries to at most 30.

Time Complexity: O(n + log n) per test case
Space Complexity: O(n) for prefix sum array

Approach:
1. Precompute prefix sums for all pile weights to quickly calculate sum of any subarray.
2. Use binary search over the pile indices:
   - For each step, query the sum of the left half of the current range.
   - Compare the actual result with the expected sum (if no special stone in range).
   - Adjust the binary search bounds accordingly.
3. When the search converges, the remaining index points to the pile with the special stone.
"""

import sys

input = sys.stdin.readline
out = []
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    # Build prefix sum array to quickly compute sums of subarrays
    p = [a[0]]
    for j in range(1, n):
        p.append(p[-1] + a[j])
    
    # Binary search bounds
    s, e = 1, n
    
    # Binary search loop to find pile with special stone
    while s <= e:
        mid = (e + s) // 2
        # Query sum of elements from index s to mid
        # The range is [s, mid] which is s to mid (1-indexed)
        print("?", mid - s + 1, " ".join(map(str, range(s, mid + 1))), flush=True)
        x = int(input())
        
        # Calculate expected sum (if no special stone in queried range)
        curr = p[mid - 1]  # prefix sum up to mid (0-indexed)
        if s != 1:
            curr -= p[s - 2]  # subtract prefix sum up to s-2 to get sum from s to mid
        
        # If actual sum matches expected (no special stone), move to right half
        if x == curr:
            s = mid + 1
        else:
            # Special stone is in the current range, move to left half
            e = mid - 1
    
    # Output the index of pile with special stone (1-indexed)
    print("!", s, flush=True)


# https://github.com/VaHiX/CodeForces/