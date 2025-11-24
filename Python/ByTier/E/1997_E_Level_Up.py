# Problem: CF 1997 E - Level Up
# https://codeforces.com/contest/1997/problem/E

"""
Algorithm: Binary Indexed Tree (Fenwick Tree) with Binary Search
Time Complexity: O(n * log^2(n) + q * log(n))
Space Complexity: O(n)

This solution uses a Binary Indexed Tree (BIT) to efficiently track and update 
the number of fights Monocarp has completed, and binary search to determine 
the current level based on fight count. For each monster, it calculates the 
fight number at which the level increases and determines if the monster is 
fled or fought.
"""

import math

Mon, que = map(int, input().split(" "))
level = list(map(int, input().split(" ")))

# BIT (Binary Indexed Tree) to track number of fights
bit = [0] * (Mon + 1)
res = [0] * Mon

# Process each monster to determine fight number when level increases
for i in range(Mon):
    idx = 0
    val = 0
    # Binary search on BIT to find the fight number when level is sufficient
    for b in range(math.floor(math.log2(Mon + 1)), -1, -1):
        idx2 = idx | (1 << b)
        if idx2 > Mon:
            continue
        val2 = val + bit[idx2]
        # Calculate current player level based on fought monsters (val2)
        # Player level = val2 // idx2 + 1
        player_level = val2 // idx2 + 1
        if player_level > level[i]:
            idx = idx2
            val = val2

    res[i] = idx + 1  # Store the fight number at which this monster is encountered
    j = res[i]
    # Update BIT with the fight count
    while j <= Mon:
        bit[j] += 1
        j += j & -j

# Process queries
for _ in range(que):
    index, def_mon = map(int, input().split(" "))
    # If k (def_mon) is greater than or equal to the fight number stored in res,
    # then Monocarp will fight the monster
    if def_mon >= res[index - 1]:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/