# Problem: CF 2107 F1 - Cycling (Easy Version)
# https://codeforces.com/contest/2107/problem/F1

"""
F1. Cycling (Easy Version)
Algorithms/Techniques: Greedy, Brute Force with optimization using sorting and index lookups

Time Complexity: O(n^2) in worst case due to brute-force exploration of all possible swaps,
                 but on average much better due to early pruning and limited number of unique values.

Space Complexity: O(n) for storing the input array and auxiliary arrays during processing.

This problem involves finding the minimum cost for Leo to move from behind the last cyclist to 
in front of the first cyclist using two operations:
1. Move in front of a specific cyclist (cost = agility value of that cyclist)
2. Swap two elements in the array (cost = index difference)

The approach considers three strategies:
- Straight greedy: Try moving one by one from back to front
- Strategy 1: Fix the smallest element at front, then apply greedy
- Strategy 2: Fix the largest element at front, then apply greedy

We evaluate all valid combinations for these strategies and return the minimum cost.
"""

import sys

input = sys.stdin.readline
inp = lambda: int(input())
insl = lambda: [*map(int, input().split())]


def greedy(arrr):
    # Greedy function simulates moving in front of each cyclist in sequence,
    # swapping with previous if needed to ensure decreasing order
    arr = [*arrr]
    res = arr[0]  # Start cost is the first element's value
    for i in range(1, len(arr)):
        # If current element is greater than previous, swap them to maintain a sequence
        if arr[i - 1] < arr[i]:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            res += 1  # Cost of swapping is 1 (incremented)
        res += arr[i]  # Cost of moving in front of current cyclist
    return res


t = inp()
for _ in range(t):
    n = inp()
    a = insl()
    a = a[::-1]  # Reverse the list so that last element becomes first for processing
    if len(set(a)) == 1:
        # All elements are same, so just sum up all costs of moving one by one
        print(a[0] * n)
        continue
    x, y, *_ = sorted([*set(a)])  # Get the two unique values in ascending order
    xi, yi = a.index(x), a.index(y)  # Find index of smallest and largest value
    print(
        min(
            greedy(a),  # Greedy approach directly on reversed array
            xi + greedy([x] + a[:xi] + a[xi + 1 :]),  # Case when we place x in front
            yi + greedy([y] + a[:yi] + a[yi + 1 :]),  # Case when we place y in front
        )
    )



# https://github.com/VaHiX/CodeForces/