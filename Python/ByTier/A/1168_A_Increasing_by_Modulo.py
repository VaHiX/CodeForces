# Problem: CF 1168 A - Increasing by Modulo
# https://codeforces.com/contest/1168/problem/A

"""
Algorithm: Binary Search on Answer + Greedy Validation
Approach:
- We are trying to find the minimum number of operations to make array non-decreasing.
- Each operation allows us to increase values in the array by 1 (mod m).
- The key insight is that we can binary search on the number of operations.
- For a given number of operations `x`, we validate if it's possible to make the array non-decreasing with at most `x` operations.
- In validation step, we greedily process from left to right and simulate how many increments are needed at each position.

Time Complexity: O(n * log(m))
Space Complexity: O(1)
"""

M = int(input().split()[1])
a = list(map(int, input().split()))
l, r = 0, M
while l < r:
    m, p = (l + r) // 2, 0  # m is mid-point of search range, p tracks current max value
    for v in a:
        # If the current element is less than or equal to p, no increment needed on this element
        if (p - v) % M > m:  # if we need more than 'm' increments from current position to make it valid
            if v < p:  # if current value is smaller than previous max
                l = m + 1  # increase lower bound
                break
            p = v  # update the current maximum element seen so far in sequence
    else:
        r = m  # if valid, try to minimize the number of operations
print(l)


# https://github.com/VaHiX/codeForces/