# Problem: CF 2138 B - Antiamuny Wants to Learn Swap
# https://codeforces.com/contest/2138/problem/B

"""
B. Antiamuny Wants to Learn Swap

Purpose:
This code determines whether a given subarray of a permutation is "perfect". A subarray is perfect if the minimum number of operations 
using both adjacent swaps and swaps of elements two positions apart equals the minimum number of operations using only adjacent swaps.

Algorithm:
- Preprocess the array to compute:
  - le[i]: index of nearest element to the left that is strictly greater than a[i]
  - ri[i]: index of nearest element to the right that is strictly smaller than a[i]
- Use segment-like computation and suffix minimums to determine for each index how far it can "reach" using operation 2.
- For each query, compare the "reachability" to determine if operation 2 helps reduce the number of operations.

Time Complexity:
O(n + q) per test case where n is size of array and q is number of queries.

Space Complexity:
O(n) for storing arrays and stacks.
"""

def solve():
    n, q = map(int, input().split())  # Read n (size of array) and q (number of queries)
    arr = list(map(int, input().split()))  # Read the permutation
    ans = []
    le = [-1] * n  # le[i] stores index of element to the left that is greater than arr[i]
    st = []  # Stack for monotonic processing from left to right
    
    # Compute le array: nearest greater element on the left
    for i, a in enumerate(arr):
        while st and arr[st[-1]] <= a:
            st.pop()  # Pop smaller or equal elements
        if st:
            le[i] = st[-1]
        st.append(i)
    
    ri = [n] * n  # ri[i] stores index of element to the right that is smaller than arr[i]
    st = []  # Stack for monotonic processing from right to left
    
    # Compute ri array: nearest smaller element on the right
    for i in range(n - 1, -1, -1):
        a = arr[i]
        while st and arr[st[-1]] >= a:
            st.pop()  # Pop larger or equal elements
        if st:
            ri[i] = st[-1]
        st.append(i)
    
    seg = [n] * n  # Segment-like array for reachability calculation
    for i in range(n):
        if le[i] >= 0:
            seg[le[i]] = min(seg[le[i]], ri[i])  # Update segment with rightmost reachable index
    
    res = [n] * n  # Final result array storing minimum reach from the right
    m = n  # Minimum reach so far
    for i in range(n - 1, -1, -1):
        m = min(m, seg[i])  # Calculate suffix minimums
        res[i] = m
    
    # Process queries
    for i in range(q):
        l, r = map(int, input().split())
        l -= 1  # Convert to 0-indexed
        r -= 1
        if r >= res[l]:  # If farthest reach is beyond current subarray end -> operation 2 not helpful
            ans.append("NO")
        else:
            ans.append("YES")  # Operation 2 helps, so not perfect
    
    print("\n".join(ans))


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    solve()


# https://github.com/VaHiX/codeForces/