# Problem: CF 1965 C - Folding Strip
# https://codeforces.com/contest/1965/problem/C

"""
Algorithm: Folding Strip
Techniques: String manipulation, prefix sum simulation, greedy approach

Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(n) for storing the processed string t

The solution processes the binary string to remove consecutive triplets of same characters,
then simulates a running sum to determine the minimum and maximum "depth" during folding.
The result is the difference between max and min depths, which corresponds to the minimum
possible length after optimal folding.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    int(input())
    s = list(input())
    t = []
    for i in s:
        t.append(i)
        if len(t) >= 3 and t[-3] == t[-2] == t[-1]:
            t.pop()
            t.pop()
    s = t
    mn = 0
    mx = 0
    sgn = 0
    now = 0
    prev = "2"
    for i in t:
        if i == prev:
            sgn ^= 1  # Toggle sign when character changes
        prev = i
        if sgn == 0:
            now += 1
        else:
            now -= 1
        mn = min(mn, now)
        mx = max(mx, now)

    print(mx - mn)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/