# Problem: CF 2038 G - Guess One Character
# https://codeforces.com/contest/2038/problem/G

"""
Algorithm: Guess One Character
Techniques: Interactive Binary Search, String Matching, Case Analysis

Time Complexity: O(1) per test case (at most 4 queries)
Space Complexity: O(1) (only using a few variables)

The solution uses a series of queries to determine the value of at least one character in the binary string.
It leverages the relationship between counts of substrings "01", "10", "0", "1", and "11" to deduce the string's composition.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def ask(t):
    # Ask the jury about the count of substring t in s
    print(f"1 {t }", flush=True)
    r = int(input())
    if r == -1:
        exit()
    return r


def answer(i, c):
    # Submit the guess that s[i] = c
    print(f"0 {i } {c }", flush=True)
    r = int(input())
    if r == -1:
        exit()


def solve_case():
    _ = int(input())

    # Query count of "01" substring
    c01 = ask("01")
    if c01 == 0:
        # If "01" is never found, the string doesn't have "0" followed by "1"
        # So we check for "10" to determine the pattern
        c10 = ask("10")
        if c10 > 0:
            # If "10" is found, then string has a "1" followed by "0"
            # So first character must be "1"
            answer(1, "1")
        else:
            # If neither "01" nor "10" is found, all characters are same
            # Query count of "0"
            c0 = ask("0")
            if c0 > 0:
                # If "0" is found, then string is all zeros
                answer(1, "0")
            else:
                # If "0" is not found, then string is all ones
                answer(1, "1")
    else:
        # If "01" is found, we can infer something about the structure
        # Query count of "1"
        c1 = ask("1")
        # Query count of "11"
        c11 = ask("11")
        # Compare counts to deduce the first character
        if c11 == c1 - c01:
            # If "11" count equals "1" count minus "01" count, 
            # then the string starts with "0"
            answer(1, "0")
        else:
            # Otherwise, it starts with "1"
            answer(1, "1")


for _ in range(int(input())):
    solve_case()


# https://github.com/VaHiX/CodeForces/