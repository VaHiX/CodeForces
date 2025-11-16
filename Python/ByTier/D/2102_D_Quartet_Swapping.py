# Problem: CF 2102 D - Quartet Swapping
# https://codeforces.com/contest/2102/problem/D

"""
D. Quartet Swapping

Purpose:
This code solves the problem of finding the lexicographically smallest permutation achievable by swapping elements at positions (i, i+2) and (i+1, i+3) simultaneously for any valid index i.

Algorithm:
1. First, identify cycles in the given permutation to calculate parity.
2. Separate the array into two subarrays: even-indexed and odd-indexed elements.
3. Sort both subarrays individually.
4. Reconstruct the result by placing sorted even-indexed elements at even indices and sorted odd-indexed elements at odd indices.
5. Check the parity again after reconstruction to see if a swap is needed for lexicographic correctness.

Time Complexity: O(n log n) due to sorting steps.
Space Complexity: O(n) for storing arrays and auxiliary storage.
"""

def solve():
    n = int(input())
    lst = list(map(int, input().split()))
    used = [0] * n
    cnt = 0
    # Find number of cycles in the permutation using DFS
    for i in range(n):
        if not used[i]:
            cnt += 1
            x = i
            while not used[x]:
                used[x] = 1
                x = lst[x] - 1  # Adjust for 0-based indexing
    
    ans = [0] * n
    a = []
    b = []
    # Separate even and odd indexed elements
    for i in range(0, n, 2):
        a.append(lst[i])
    for i in range(1, n, 2):
        b.append(lst[i])
    
    a.sort()  # Sort even-indexed elements
    b.sort()  # Sort odd-indexed elements
    
    # Fill ans with sorted elements at correct positions
    for i in range(len(a)):
        ans[i * 2] = a[i]
    for i in range(len(b)):
        ans[i * 2 + 1] = b[i]
    
    used = [0] * n
    c2 = 0
    # Recalculate number of cycles after modification
    for i in range(n):
        if not used[i]:
            c2 += 1
            x = i
            while not used[x]:
                used[x] = 1
                x = ans[x] - 1
    
    # Adjust last two elements if parity mismatch
    if (n - cnt) % 2 != (n - c2) % 2:
        ans[n - 3], ans[n - 1] = ans[n - 1], ans[n - 3]
    print(" ".join(map(str, ans)))


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/codeForces/