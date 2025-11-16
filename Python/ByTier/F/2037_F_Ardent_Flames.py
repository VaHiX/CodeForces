# Problem: CF 2037 F - Ardent Flames
# https://codeforces.com/contest/2037/problem/F

"""
Algorithm: Binary Search + Two Pointers
Purpose: Find minimum number of attacks to defeat at least k enemies by choosing optimal position p for Xilonen's ground stomp.
Time Complexity: O(n log(max_n) * log(n)) where max_n = 1e9
Space Complexity: O(n) for storing lefts and rights arrays

Approach:
1. Binary search on the number of attacks (1 to 1e9).
2. For each number of attacks, compute the effective damage each enemy receives.
3. Identify the range [left, right) of positions that get damaged for each enemy.
4. Use two pointers technique to check if at least k intervals overlap (i.e., at least k enemies are hit by the attack).
"""

for i in range(int(input())):
    n, m, k = map(int, input().split())
    h = list(map(int, input().split()))
    x = list(map(int, input().split()))
    l = 1
    r = 1000000001
    while l < r:
        attacks = (l + r) // 2
        found = 0
        lefts = []
        rights = []
        for i in range(n):
            # Calculate minimum damage per attack needed to defeat enemy in 'attacks' number of attacks
            damage = (h[i] + attacks - 1) // attacks
            # Skip if damage exceeds max damage (m)
            if damage > m:
                continue
            # Compute range of positions that receive damage
            lefts.append(x[i] - (m - damage))
            rights.append(x[i] + (m - damage) + 1)
        # Sort ranges for two-pointer technique
        lefts.sort()
        rights.sort()
        ptr1 = 0
        ptr2 = 0
        # Use two pointers to count overlapping intervals
        while ptr1 < len(lefts):
            if lefts[ptr1] > rights[ptr2]:
                ptr2 += 1
            elif lefts[ptr1] == rights[ptr2]:
                ptr1 += 1
                ptr2 += 1
            elif lefts[ptr1] < rights[ptr2]:
                ptr1 += 1
                # If we have at least k overlapping intervals, mark success
                if ptr1 - ptr2 >= k:
                    found = 1
        if found == 0:
            l = attacks + 1
        else:
            r = attacks
    if l > 1000000000:
        print(-1)
    else:
        print(l)


# https://github.com/VaHiX/CodeForces/