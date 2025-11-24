# Problem: CF 2036 C - Anya and 1100
# https://codeforces.com/contest/2036/problem/C

"""
C. Anya and 1100

Purpose:
This code solves a problem where a string of '0' and '1' is modified through queries,
and after each query, we check if the substring "1100" exists in the string.

Approach:
- Precompute number of "1100" substrings in initial string.
- For each query:
  - Calculate how the count changes due to modification at position i.
  - Update count accordingly.
  - Output YES if count > 0, NO otherwise.

Time Complexity: O(|s| + q), where |s| is length of string and q is number of queries.
Space Complexity: O(|s|) for storing the string and performing operations.

Algorithms/Techniques:
- Sliding window technique to efficiently track occurrences of "1100".
- Efficiently updating count during character changes by checking affected windows.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    s = list(input().strip())  # Read string and convert to list for mutability
    q = int(input())
    cnt = 0

    # Count initial occurrences of "1100"
    for i in range(len(s) - 3):  # Loop until 4th from last to avoid index out of bounds
        if "".join(s[i : i + 4]) == "1100":
            cnt += 1

    for _ in range(q):
        i, v = input().split()
        i = int(i) - 1  # Convert to 0-based index
        v = str(v)  # Ensure v is string
        curr = 0  # Count of "1100" in the affected windows before update

        # Check all 4-character windows that include position i
        for j in range(max(0, i - 3), min(len(s), i + 4) - 3):
            if "".join(s[j : j + 4]) == "1100":
                curr += 1

        s[i] = v  # Update the character at position i

        conn = 0  # Count of "1100" in the affected windows after update
        for j in range(max(0, i - 3), min(len(s), i + 4) - 3):
            if "".join(s[j : j + 4]) == "1100":
                conn += 1

        cnt += conn - curr  # Adjust the total count

        print("YES" if cnt > 0 else "NO")


# https://github.com/VaHiX/codeForces/