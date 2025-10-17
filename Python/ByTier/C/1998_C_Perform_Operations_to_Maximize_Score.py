# Problem: CF 1998 C - Perform Operations to Maximize Score
# https://codeforces.com/contest/1998/problem/C

"""
Purpose:
This code solves the problem of maximizing the score by performing at most k operations on an array a,
where each operation increments an element a[i] if b[i] == 1. The score is defined as the maximum value
of a[i] + median of the array obtained by removing a[i] from a.

Algorithm:
- The approach involves sorting the array based on values and using a greedy method to decide how many
  operations to apply to each element to maximize the median of the resulting array.
- A key idea is to identify the median position and determine how to best use the operations to increase
  elements near the median to optimize the final score.
- We use a frequency map of elements and process elements from the median toward the end to determine
  optimal operation application.

Time Complexity: O(n log n + n) - Due to sorting and linear iteration through elements.
Space Complexity: O(n) - For storing and processing the sorted array and auxiliary data structures.
"""

import sys
from collections import defaultdict

input = sys.stdin.readline
for koko in range(int(input())):
    d = defaultdict(lambda: (0, 0)) # Frequency map, (count, number of 1s in b for those elements)
    n, k = map(int, input().strip().split())
    prev_k = k
    a = list(map(int, input().strip().split()))
    b = list(map(int, input().strip().split()))
    a = [(a[i], b[i]) for i in range(n)]
    a = sorted(a, key=lambda x: x[0]) # Sort by values
    # Process elements from middle to end to determine how many 1s they have
    for i in range((n // 2) - 1, n):
        d[a[i][0]] = (d[a[i][0]][0] + 1, d[a[i][0]][1] + (1 - a[i][1]))
    l = list(d.keys())
    l2 = [(0) for i in range((n // 2) - 1)]
    # Store elements before median
    for i in range((n // 2) - 1):
        l2[i] = a[i]
    start = a[n // 2 - 1][0] # Median element
    next_i = 1
    last_i = len(l)
    median = start
    val = 0
    num = 1
    # Greedily apply operations to optimize the median
    while k > 0:
        if d[start][1] == 0: # If no 1s at current start
            if next_i == last_i:
                break # No more elements
            else:
                # Apply operations to shift to next element
                k -= (l[next_i] - start) * d[start][0]
                val = l[next_i] - start
                num = d[start][0]
                median = l[next_i]
                start = l[next_i]
                next_i += 1
                d[start] = (d[start][0] + num, d[start][1])
        else:
            # If there are 1s, process elements from l2
            vall = d[start][1]
            val2 = vall
            s = 0
            while val2 != 0 and l2 != []:
                ele = l2.pop()
                if ele[1] == 1: # If b[i] == 1
                    val2 -= 1
                    s += ele[0]
            if l2 == [] and val2 != 0:
                k = 0
                break
            # Apply operations to reduce the cost
            k -= min(start * vall - s, k)
            d[start] = (d[start][0], 0) # No more 1s at this element
    
    # Final calculation for the maximum possible score
    val1, val2 = (median - val) + (k + (val * num)) // num, l[-1]
    maxi = val1 + val2
    k = prev_k
    # Evaluate final score for each element
    for i in range(n):
        if a[i][1] == 0:
            kk = 0 # Cannot perform operations
        else:
            kk = k
        val1 = a[i][0] + kk
        if i < n // 2:
            val2 = a[n // 2][0]
        else:
            val2 = a[n // 2 - 1][0]
        maxi = max(val1 + val2, maxi)
    print(maxi)


# https://github.com/VaHiX/CodeForces/