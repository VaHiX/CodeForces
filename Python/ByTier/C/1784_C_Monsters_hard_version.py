# Problem: CF 1784 C - Monsters (hard version)
# https://codeforces.com/contest/1784/problem/C

"""
Purpose: 
This code solves the "Monsters (hard version)" problem where for each prefix of the monster array,
we need to find the minimum number of type 1 spells required to kill all monsters in that prefix.

The approach:
- We use a greedy strategy combined with sorting and binary search
- For each prefix, we determine how many type 1 spells are needed by analyzing
  the optimal distribution of damage between type 1 and type 2 spells
- The algorithm maintains counters for damaged monsters and uses a sorted list for
  efficient search of monsters that are "invalid" (not satisfying the condition)

Time Complexity: O(n log n) per test case, dominated by sorting operations
Space Complexity: O(n) for storing arrays, dictionaries, and deques
"""

import sys
from bisect import *
from collections import *
from functools import *

input = lambda: sys.stdin.readline().rstrip()

Z = int(input())
for _ in range(Z):
    n = int(input())
    (*arr,) = map(int, input().split())
    poi = 1
    sum1 = 0
    sum2 = 0
    dic = {}
    invalid = {}
    ans = deque()
    orarr = sorted(arr)
    i = 1
    for j in orarr:
        if j >= i:  # if current monster's health is sufficient to be killed with type 1 spells
            dic[j] = dic.get(j, 0) + 1  # track count of such monsters
            sum1 += i  # accumulate sum of minimal type 1 spells needed
            sum2 += j  # accumulate sum of actual monster healths
            i += 1
        else:
            invalid[j] = invalid.get(j, 0) + 1  # track monsters that are invalid for the greedy strategy
    i -= 1
    sum3 = sum2 - sum1  # difference gives us the minimum type 1 spells needed for the current state

    rep = sorted(invalid.keys())  # sorted keys of invalid monsters

    # Process from right to left through original array
    for j in arr[::-1]:  # reverse iteration
        if invalid.get(j, 0) > 0:  # if monster is in invalid list
            ans.appendleft(sum3)  # output the result
            invalid[j] -= 1  # reduce count
            if invalid[j] == 0:  # if no more of this monster, remove from invalid list
                rep.pop(rep.index(j))
        else:  # if monster is not invalid
            ans.appendleft(sum3)
            if rep and j < rep[-1]:  # if there are invalid monsters and current monster is smaller than largest invalid
                k = bisect_right(rep, j)  # find position for replacement
                abc = rep[k]  # get the monster that will be replaced
                dic[abc] += 1  # update counting
                invalid[abc] -= 1  # update invalid
                if invalid[abc] == 0:  # if removed entirely
                    rep.pop(k)
                sum2 = sum2 - j + abc  # update sums
                sum3 = sum2 - sum1
            else:  # if no valid replacement or current monster is larger or equal
                dic[j] -= 1  # reduce count
                sum1 -= i  # update sum1
                sum2 -= j  # update sum2
                i -= 1  # decrease the greedy threshold
                sum3 = sum2 - sum1  # update the difference
    print(*ans)


# https://github.com/VaHiX/CodeForces/