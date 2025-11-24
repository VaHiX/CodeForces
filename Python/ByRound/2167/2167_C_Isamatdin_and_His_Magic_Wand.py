# Problem: CF 2167 C - Isamatdin and His Magic Wand!
# https://codeforces.com/contest/2167/problem/C

"""
Code Purpose:
This code solves the problem of rearranging an array of integers using a special wizard's wand that can only swap elements if they have different parity (one even, one odd). The goal is to produce the lexicographically smallest possible arrangement using these constrained swaps.

Algorithm:
1. For each test case, read the number of elements and the array of integers.
2. Determine if there are both even and odd numbers in the array.
3. If both parities exist, we can sort the entire array (since we can swap any two elements of different parity, and sorting is possible by repeated swaps).
4. If all elements are even or all are odd, no swaps are possible, so output as is.

Time Complexity: O(n log n) per test case due to sorting when both parities exist.
Space Complexity: O(n) for storing the array.

Techniques:
- Bitwise AND with 1 (x & 1) to check parity (0 for even, 1 for odd)
- Set to quickly determine if both even and odd numbers are present
"""

import sys


def solve():
    int(input().strip())
    a = list(map(int, input().strip().split()))
    # Check if both even and odd numbers exist
    if len(set(x & 1 for x in a)) == 2:
        a.sort()  # If both exist, full sorting is possible
    print(" ".join(map(str, a)))


def run_local():
    sys.stdin = open("input.txt", "r")
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":

    if len(sys.argv) > 1 and sys.argv[1] == "LOCAL":
        run_local()

    else:
        input = sys.stdin.readline
        t = int(input())
        for _ in range(t):
            solve()


# https://github.com/VaHiX/CodeForces/