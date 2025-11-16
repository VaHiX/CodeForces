# Problem: CF 1833 D - Flipper
# https://codeforces.com/contest/1833/problem/D

"""
Algorithm/Technique: 
- The key insight is to find the optimal segment [l,r] to reverse and then swap prefix and suffix
- We want to maximize the lexicographical value of the result
- The approach involves:
  1. Finding the maximum element in the array
  2. Determine the position of this maximum element
  3. Based on position, decide the segment for reversal to maximize the result
  4. After choosing segment, reverse it and perform prefix-suffix swap operation
- Time Complexity: O(n) per test case, as we scan the array a constant number of times
- Space Complexity: O(n) for storing the permutation array
"""

import os
import sys

if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")

input = lambda: sys.stdin.readline().strip()
print = lambda *args, end="\n": sys.stdout.write(" ".join(str(i) for i in args) + end)
im = lambda: map(int, input().split())
sdv = lambda x, rev=False: dict(
    sorted(x.items(), key=lambda item: item[1], reverse=rev)
)
sdk = lambda x, rev=False: {i: x[i] for i in sorted(x, reverse=rev)}

MIN = sys.maxsize
MAX = -sys.maxsize
MOD = 10**9 + 7
T = 1


def main(T):
    for _ in range(T):
        solution()


T = int(input())


def solution():
    n = int(input())
    p = list(im())

    if n == 1:
        print(1)
        return

    # Find the maximum element in the permutation
    if p[0] == n:
        m = n - 1
    else:
        m = n

    # Find index of the maximum element
    mi = p.index(m)
    
    # Determine the end point of the segment to reverse
    if mi == n - 1:
        e = max(0, mi - 1)
    else:
        e = max(0, mi - 2)

    # Adjust the start point based on condition
    s = 0
    while p[s] < p[e]:
        e -= 1

    # Output the result by concatenating:
    # 1. Prefix from mi to end
    # 2. Reversed middle segment if it exists
    # 3. Suffix from s to e+1
    print(*p[mi:], end=" ")
    if e != mi - 1:
        print(*p[mi - 1 : e : -1], end=" ")
    print(*p[s : e + 1])


main(T)


# https://github.com/VaHiX/CodeForces/