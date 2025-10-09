# Problem: CF 2128 C - Leftmost Below
# https://codeforces.com/contest/2128/problem/C

"""
C. Leftmost Below
Algorithm: Greedy simulation with prefix minimum tracking.
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input array)

The problem involves determining if we can reach a target array by performing specific operations.
Each operation selects a value x > min(a), finds the leftmost index i such that a[i] < x,
and increments a[i] by x. 

This solution uses a greedy approach to validate whether the given target array is achievable:
- It iterates through the array and for each element, checks if it can be obtained
  by incrementing some previous value with a valid x.
- The key insight is that at any point, if an element is at least twice the current minimum,
  it is impossible to construct it using operations under the problem rules.

Key lines:
- Line 3: Initialize min_prefix to first element.
- Line 4-7: Loop over array elements, checking constraints on current element vs current minimum.
- Line 8: Update min_prefix at each step to maintain running minimum.
"""

def f(n, arr):
    min_prefix = arr[0]  # Track the minimum value seen so far
    for val in arr:
        if val >= 2 * min_prefix:  # If current value is at least twice the minimum, impossible
            return False
        min_prefix = min(min_prefix, val)  # Update the running minimum
    return True


t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    res = f(n, arr)
    if res:
        print("Yes")
    else:
        print("No")


# https://github.com/VaHiX/codeForces/