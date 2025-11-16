# Problem: CF 2164 B - Even Modulo Pair
# https://codeforces.com/contest/2164/problem/B

"""
Problem: Find two distinct elements x and y from a strictly increasing sequence such that x < y and y mod x is even.

Algorithm:
- For each element in the sequence, check all subsequent elements to see if the modulo operation results in an even number.
- Use nested loops to compare pairs (x, y) where x < y.
- Early termination when a valid pair is found.

Time Complexity: O(n^2) in worst case due to nested loops
Space Complexity: O(1) excluding input storage
"""

import sys

t = int(sys.stdin.readline())
out = []
for i in range(t):
    n = int(sys.stdin.readline())
    L = list(map(int, sys.stdin.readline().split()))
    ans = ""
    # Iterate through each number as potential x
    for j, num in enumerate(L):
        # Check all numbers after current number as potential y
        for k in L[j + 1 :]:
            # If the remainder of k divided by num is even
            if (k % num) % 2 == 0:
                ans = str(num) + " " + str(k)
                break
        # If we found a valid pair, break out of outer loop
        if ans != "":
            break
    # If no valid pair found
    if ans == "":
        ans = "-1"
    out.append(ans)
print("\n".join(out))


# https://github.com/VaHiX/CodeForces/