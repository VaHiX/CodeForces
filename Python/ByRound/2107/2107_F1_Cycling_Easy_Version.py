# Problem: CF 2107 F1 - Cycling (Easy Version)
# https://codeforces.com/contest/2107/problem/F1

"""
F1. Cycling (Easy Version)
Algorithm: Greedy + Brute-force with optimization
Time Complexity: O(n^2) per test case in worst case due to nested operations and sorting.
Space Complexity: O(n) for storing the array and auxiliary arrays.

Approach:
- We simulate the process of moving Leo ahead of cyclist 1.
- The cost comes from two sources:
  1. Swapping elements (cost = j - i)
  2. Moving in front of a cyclist (cost = a[i])
- The key idea is to try different strategies based on how we can rearrange the array to minimize total cost.
- We consider three scenarios for minimizing cost:
  1. Direct greedy approach.
  2. Try placing minimum value at front and simulate rest.
  3. Try placing maximum value at front and simulate rest.
"""

import sys

input = sys.stdin.readline
inp = lambda: int(input())
insl = lambda: [*map(int, input().split())]


def greedy(arrr):
    # Greedy simulation to move Leo in front of the first cyclist
    arr = [*arrr]
    res = arr[0]  # Initial cost is the value at index 0 (Leo starts behind last)
    for i in range(1, len(arr)):
        if arr[i - 1] < arr[i]:
            # Swap to ensure decreasing order (to reduce future costs)
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            res += 1  # Cost of swapping
        res += arr[i]  # Cost of moving in front of current cyclist
    return res


t = inp()
for _ in range(t):
    n = inp()
    a = insl()
    a = a[::-1]  # Reverse the array to process from back to front as per description
    
    if len(set(a)) == 1:
        # All elements are same; just direct path costs
        print(a[0] * n)
        continue

    x, y, *_ = sorted([*set(a)])  # Get unique values in sorted order (min, max)
    xi, yi = a.index(x), a.index(y)  # Find first occurrence of min and max
    
    print(
        min(
            greedy(a),  # Direct greedy strategy
            xi + greedy([x] + a[:xi] + a[xi + 1 :]),  # Place min at front and simulate
            yi + greedy([y] + a[:yi] + a[yi + 1 :]),  # Place max at front and simulate
        )
    )


# https://github.com/VaHiX/codeForces/