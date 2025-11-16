# Problem: CF 1973 E - Cat, Fox and Swaps 
# https://codeforces.com/contest/1973/problem/E

"""
Code Purpose:
This solution determines the number of valid (l, r) pairs such that swapping elements 
in a permutation is possible under the constraint that only two elements x and y 
can be swapped if l ≤ x + y ≤ r. The approach uses mathematical analysis to avoid 
brute-force enumeration of all pairs.

Key insights:
- For each pair of indices (i, j) where p[i] ≠ i+1, we check whether these elements can 
  be swapped under any valid (l, r).
- We derive conditions for when a specific (l, r) makes all swaps possible.
- The total number of valid (l, r) pairs is computed based on:
  - Initial assumption that all pairs are valid.
  - Subtracting invalid configurations based on misplacements.

Algorithms/Techniques:
- Mathematical analysis of valid ranges for l and r.
- Deduction of constraints to avoid brute force.

Time Complexity:
O(n), where n is the size of the permutation. Only one pass through the array is needed.

Space Complexity:
O(n) for storing the array and additional variables.
"""

ans = []

for t in range(int(input())):
    n = int(input())
    p = [int(x) for x in input().split()]

    # Start with the maximum possible number of pairs (l, r)
    total = 2 * n + n * (2 * n - 1)

    # Track if there's a special case with unique swaps
    trick = -1
    unsort = []  # Store positions that are out of order
    for i in range(n):
        if p[i] == i + 1:
            continue
        unsort.append(i + 1)
        if trick == -1:
            trick = i + 1 + p[i]
        elif not trick == i + 1 + p[i]:
            trick = -2  # Indicate mixed sums

    # Adjust total based on special cases
    if trick > 0:
        total -= 2 * n - 1
    if trick == -2:
        total -= 2 * n

    # Adjust for positions that are not in correct order
    if len(unsort) > 0:
        a = n - unsort[0]  # Distance from start to first misplaced element
        total -= a * (a - 1) // 2  # Subtract contribution from first part
        b = unsort[-1]  # Index of last misplaced element
        total -= b * (b - 1) // 2  # Subtract contribution from last part

    ans.append(total)

for a in ans:
    print(a)


# https://github.com/VaHiX/CodeForces/