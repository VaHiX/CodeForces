# Problem: CF 2152 C - Triple Removal
# https://codeforces.com/contest/2152/problem/C

"""
C. Triple Removal

Purpose:
This problem involves finding the minimum cost to make a subarray of 0s and 1s empty by removing triplets of identical elements.
For each query, we need to compute the total cost of operations on a given range [l, r].

Approach:
1. Precompute prefix sums for zeros and ones to quickly count occurrences in any range.
2. Precompute a prefix sum array that counts how many adjacent equal elements exist.
3. For each query:
   - Check if the number of 0s and 1s are divisible by 3 (required condition).
   - If not, return -1.
   - Otherwise, calculate base number of triplets: len // 3.
   - If there are adjacent equal elements in the range, we can avoid one operation (optimization).
   - Return adjusted triplet count.

Time Complexity: O(n + q) where n is length of array and q is number of queries.
Space Complexity: O(n) for prefix arrays.
"""

t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    v = list(map(int, input().split()))
    z = [0] * (n + 1)  # Prefix sum of zeros
    o = [0] * (n + 1)  # Prefix sum of ones
    for i in range(1, n + 1):
        z[i] = z[i - 1] + (1 if v[i - 1] == 0 else 0)   # Count zeros up to index i
        o[i] = o[i - 1] + (1 if v[i - 1] == 1 else 0)   # Count ones up to index i
    a = [0] * (n + 1)   # Prefix sum of adjacent equal elements
    for i in range(1, n):
        a[i] = a[i - 1] + (1 if v[i - 1] == v[i] else 0)   # Count consecutive same elements
    a[n] = a[n - 1]     # Last element of prefix array
    
    for _ in range(q):
        s, e = map(int, input().split())
        zi = z[e] - z[s - 1]     # Number of zeros in range [s,e]
        oi = o[e] - o[s - 1]     # Number of ones in range [s,e]
        
        if zi % 3 != 0 or oi % 3 != 0:    # If count is not divisible by 3, impossible to empty
            print(-1)
            continue
            
        l = e - s + 1           # Length of the subarray
        b = l // 3              # Base number of triplets needed
        
        if s <= e - 1 and (a[e - 1] - a[s - 1]) > 0:  # If adjacent elements exist, one less operation possible
            print(b)
        else:
            print(b + 1)   # No adjacent same elements, so add one more operation


# https://github.com/VaHiX/CodeForces/