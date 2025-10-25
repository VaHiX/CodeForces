# Problem: CF 1886 C - Decreasing String
# https://codeforces.com/contest/1886/problem/C

"""
Algorithm: Decreasing String
Techniques: Binary Search, Stack-based String Construction

Time Complexity: O(n) per test case, where n is the length of the string s1.
Space Complexity: O(n) for the stack and temporary storage.

The problem involves generating a sequence of strings by repeatedly removing
the lexicographically largest character from the previous string. Then we
concatenate all those strings into one large string S and find the character
at a specific position.

We use binary search to determine which step in the sequence the position
falls into, and then simulate the construction of the final string using a stack
to maintain the lexicographically minimal sequence.
"""

import sys

input = sys.stdin.readline


def readInt():
    return int(input())


def readStr():
    return input().strip()


def solve():
    s, pos = readStr(), readInt()
    n = len(s)
    lo, hi = 1, n
    while lo < hi:
        mid = (lo + hi) // 2
        # Check if the cumulative length of all s1..smid is >= pos
        if ((2 * n - mid + 1) * mid) // 2 >= pos:
            hi = mid
        else:
            lo = mid + 1
    cnt = hi - 1  # Number of chars removed to reach the target step
    # Adjust pos to be 0-indexed relative to the target string
    pos -= ((2 * n - cnt + 1) * cnt) // 2 + 1
    st = []
    for i in range(n):
        # Pop characters from the stack if they are larger than current char
        # and we still have removals left (cnt > 0)
        while cnt and st and st[-1] > s[i]:
            st.pop()
            cnt -= 1
        st.append(s[i])
    return st[pos]  # Return the character at the adjusted position


ans = []
for _ in range(readInt()):
    ans.append(solve())
print("".join(ans))


# https://github.com/VaHiX/CodeForces/