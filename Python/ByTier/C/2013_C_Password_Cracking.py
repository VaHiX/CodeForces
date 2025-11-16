# Problem: CF 2013 C - Password Cracking
# https://codeforces.com/contest/2013/problem/C

"""
Algorithm: Password Cracking
Techniques: Binary search, greedy construction
Time Complexity: O(n^2) in worst case due to up to 2n queries and each query takes O(n) time to check substring
Space Complexity: O(n) for storing the constructed password

The approach uses a greedy method to build the password:
1. First, we construct the password from left to right by trying to append '0' or '1' and checking if the resulting string is a substring.
2. Then, we finish constructing the password by trying to prepend characters from left to right.
"""

import sys

input = sys.stdin.readline


def ask(x):
    print(f"? {x }")
    sys.stdout.flush()
    res = int(input())
    return res


def result(x):
    print(f"! {x }")
    sys.stdout.flush()


for _ in range(int(input())):
    n = int(input())
    ans = ""
    while len(ans) < n:
        if ask(ans + "0"):
            ans += "0"
        elif ask(ans + "1"):
            ans += "1"
        else:
            break
    while len(ans) < n:
        if ask("0" + ans):
            ans = "0" + ans
        else:
            ans = "1" + ans
    result(ans)


# https://github.com/VaHiX/CodeForces/