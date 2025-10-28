# Problem: CF 1881 A - Don't Try to Count
# https://codeforces.com/contest/1881/problem/A

"""
Algorithm: Simulation with String Concatenation
Approach:
    - Start with the initial string x.
    - Keep doubling the string x by appending it to itself.
    - After each doubling, check if the target string s is a substring of x.
    - If found, return the number of operations performed.
    - If after a reasonable number of operations s is still not found, return -1.

Time Complexity: O(n * m * k), where k is the number of operations (at most 5),
                 n and m are the lengths of strings x and s respectively.
                 Since n * m <= 25, and we perform at most 5 operations,
                 the complexity is effectively constant.

Space Complexity: O(n * k), where k is at most 5, so effectively O(n).
"""

import sys


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())
        x, s = input().rstrip(), input().rstrip()
        if s in x:
            print(0)
            continue
        x *= 2  # Double x initially to start simulation
        ans = 1
        while len(x) <= len(s) * 2:  # Loop until x is large enough to contain s as substring
            if s in x:
                print(ans)
                break
            x *= 2  # Double x again
            ans += 1
        else:
            # If we exit the loop without breaking, check the final x
            print(ans if s in x else -1)


main()


# https://github.com/VaHiX/CodeForces/