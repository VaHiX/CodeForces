# Problem: CF 1879 C - Make it Alternating
# https://codeforces.com/contest/1879/problem/C

"""
Algorithm: Make it Alternating
Approach:
1. The problem requires transforming a binary string into an alternating string (0101... or 1010...) by deleting minimum number of characters.
2. Key insight: We can group consecutive identical characters and determine how many deletions are needed to break up long sequences.
3. The minimum deletions = total length - number of groups.
4. To compute number of ways:
   - Each group contributes a certain number of choices for deletion (equal to group size)
   - Total ways = product of choices for each group.
   - But we also need to consider that the deletions themselves form a sequence, so there are multiple orders of doing the same deletions.

Time Complexity: O(n) where n is total length of input string across all test cases.
Space Complexity: O(n) for storing grouped character counts.

Techniques:
- Grouping consecutive identical elements
- Combinatorial counting with modular arithmetic
- Modular multiplication for large results
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


tt = inp()
for _ in range(tt):
    s = insr()
    myList = []
    curElem = s[0]
    curCount = 0
    for c in s:
        if c != curElem:
            curElem = c
            if curCount > 1:
                myList.append(curCount)
            curCount = 1
        else:
            curCount += 1
    if curCount > 1:
        myList.append(curCount)
    numWays = 1
    deletions = sum(myList) - len(myList)
    for num in myList:
        numWays = (numWays * num) % 998244353
    for i in range(2, deletions + 1):
        numWays = (numWays * i) % 998244353
    print(deletions, numWays)


# https://github.com/VaHiX/CodeForces/