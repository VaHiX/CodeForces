# Problem: CF 2154 B - Make it Zigzag
# https://codeforces.com/contest/2154/problem/B

"""
B. Make it ZigZag

Algorithm:
- For odd indices (1-based), we want a[i] < a[i+1]
- For even indices (1-based), we want a[i] > a[i+1]
- First pass: update even indices to be the maximum up to that point
- Second pass: make sure each element satisfies the zigzag condition by reducing it if necessary, counting the operations

Time Complexity: O(n) - linear pass through the array
Space Complexity: O(1) - only using a few variables, no extra space needed
"""

import sys
from array import array

input = sys.stdin.readline
write = sys.stdout.write


def solve():
    n = int(input())
    ans = 0

    a = array("q", map(int, input().split()))

    maximum = 0
    for i in range(n):
        maximum = max(maximum, a[i])
        if i % 2:  # If i is odd (1-based indexing)
            a[i] = maximum

    for i in range(0, n, 2):  # Iterate through even indices (0-based)
        if i > 0 and a[i] >= a[i - 1]:
            ans += a[i] - a[i - 1] + 1
            a[i] = a[i - 1] - 1
        if i < n - 1 and a[i] >= a[i + 1]:
            ans += a[i] - a[i + 1] + 1
            a[i] = a[i + 1] - 1

    write(str(ans) + "\n")


def main():
    t = int(input())
    while t:
        solve()
        t -= 1


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/