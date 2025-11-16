# Problem: CF 1968 B - Prefiquence
# https://codeforces.com/contest/1968/problem/B

"""
Algorithm: Two Pointers
Purpose: Find the maximum length of a prefix of string 'a' that is a subsequence of string 'b'.
Approach:
- Use two pointers, one for string 'a' (i) and one for string 'b' (j).
- Traverse both strings:
  - If characters at current positions match, increment both pointers and result counter.
  - If they don't match, only increment pointer for 'b'.
- Continue until one of the strings is fully traversed.
Time Complexity: O(n + m) where n is length of 'a' and m is length of 'b'
Space Complexity: O(1) - only using a few variables for pointers and counter.
"""

import sys

input = sys.stdin.readline


def ri():
    return int(input())


def rl(v_type=int):
    return list(map(v_type, input().split()))


def rs():
    return input().rstrip()


def out(x, sep=" "):
    return sep.join(map(str, x))


def solve_case():
    n, m = rl()  # Read lengths of strings a and b
    a = rs()     # Read string a
    b = rs()     # Read string b
    res = 0      # Initialize result counter
    i, j = 0, 0  # Initialize two pointers for strings a and b
    while i < n and j < m:  # Loop while both pointers are within bounds
        if a[i] == b[j]:    # If characters match
            res += 1        # Increment result counter
            i += 1          # Move pointer for a forward
            j += 1          # Move pointer for b forward
        else:
            j += 1          # Move pointer for b forward only (character mismatch)
    return res


if __name__ == "__main__":
    T = int(input())  # Read number of test cases

    ret = [solve_case() for ti in range(1, T + 1)]  # Process each test case
    print(out(ret, "\n"))  # Print results


# https://github.com/VaHiX/CodeForces/