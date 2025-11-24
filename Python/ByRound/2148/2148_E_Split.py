# Problem: CF 2148 E - Split
# https://codeforces.com/contest/2148/problem/E

"""
E. Split

Purpose:
This code counts the number of "awesome" subarrays in an array `a` of length `n` with respect to a given integer `k`. 
A subarray is awesome if we can distribute its elements among `k` multisets such that each multiset contains exactly 
the same count of each element (i.e., all multisets are "balanced").

Algorithm:
- For each test case, first compute the frequency of each element in the entire array.
- Check if the frequency of every element is divisible by k. If not, there are no awesome subarrays.
- Use a sliding window technique with two pointers (`l` and `r`) to find all valid subarrays:
    - Expand the right pointer `r` until an element's count exceeds its allowed limit (frequency/k).
    - When that happens, shrink the window from the left until the constraint is satisfied again.
    - Count valid subarrays using a formula involving window size.
- Time Complexity: O(n) per test case
- Space Complexity: O(n)

Time Complexity: O(n)
Space Complexity: O(n)
"""

inf = 10000


def inp():
    return [int(e) for e in input().split()]


for ww in range(int(input())):
    n, k = inp()
    a = inp()
    p = [0] * (n + 1)
    for e in a:
        p[e] += 1
    if any([e % k for e in p]):  # Check if all element frequencies are divisible by k
        print(0)
        continue
    l, r = 0, -1
    q = [0] * (n + 1)
    ans = 0
    while r < n - 1:
        r += 1
        x = a[r]
        if q[x] == p[x] // k:  # If current element count in window equals max allowed count
            while q[x] == p[x] // k:  # Shrink window from left until condition holds
                q[a[l]] -= 1
                ans += r - l  # Add all subarrays ending at r and starting from l to r
                l += 1
            q[x] += 1
        else:
            q[a[r]] += 1  # Expand window by adding new element
    d = r - l + 1  # Size of remaining valid window
    ans += d * (d + 1) // 2  # Add all subarrays in this final window using triangular number formula
    print(ans)


# https://github.com/VaHiX/codeForces/