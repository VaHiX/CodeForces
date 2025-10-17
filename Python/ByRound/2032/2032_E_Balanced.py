# Problem: CF 2032 E - Balanced
# https://codeforces.com/contest/2032/problem/E

"""
E. Balanced

Purpose:
This problem involves making a cyclic array balanced by applying operations. Each operation at index i increases elements at indices (i-1)%n, i, and (i+1)%n by 1, 2, and 1 respectively. The goal is to determine how many operations to apply at each index so that all elements of the array become equal.

Algorithms/Techniques:
- Difference array technique for efficient range updates.
- Linear transformation and solving system of equations using prefix sums.
- Modular arithmetic for cyclic array handling.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays and intermediate results

"""

def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    
    # Special cases for small n
    if n == 1:
        print(0)
        return
    if n == 3:
        m = max(arr)
        print(*[m - a for a in arr])
        return
    
    # Transform the array using difference method to capture change in adjacent elements
    arr = [-arr[0] + arr[-1]] + [-arr[i] + arr[i - 1] for i in range(1, n)]
    
    # Compute prefix sums for the transformed array
    ans1 = [0] * n
    for i in range(2, 2 * n, 2):
        ans1[i % n] = ans1[(i - 2) % n] + arr[i % n]

    # Compute the alternating sum to determine the base adjustment needed
    ans = [0] * n
    m = 0
    f = 1
    for a in ans1:
        m += f * a
        f = -f
    
    # Adjust if m is odd to make it even (since operations must be integer)
    if m % 2:
        for i in range(n):
            ans1[i] += 1
        m += 1
    
    # Set first element of result array based on m
    ans[0] = m // 2
    
    # Compute all other elements based on previous values and ans1
    for i in range(1, n):
        ans[i] = ans1[i - 1] - ans[i - 1]
    
    # Ensure final result is non-negative by shifting with minimum value
    x = -min(ans)
    print(*[a + x for a in ans])


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    solve()


# https://github.com/VaHiX/codeForces/