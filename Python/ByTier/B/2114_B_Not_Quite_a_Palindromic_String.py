# Problem: CF 2114 B - Not Quite a Palindromic String
# https://codeforces.com/contest/2114/problem/B

"""
B. Not Quite a Palindromic String

Purpose:
This code determines whether it is possible to rearrange the characters of a given binary string
to form exactly k good pairs of indices (i, n - i + 1), where s[i] == s[n - i + 1].

Algorithms/Techniques:
- Greedy approach with mathematical analysis:
    - Count total number of '0's in input string.
    - For a string of length n, there are n/2 pairs to consider.
    - The minimum moves required to get exactly k good pairs is calculated as:
        m = n // 2 - min(c, n - c), where c is count of '0's.
    - Check if m <= k and (m - k) % 2 == 0.

Time Complexity: O(n) per test case, where n is the length of string.
Space Complexity: O(1) excluding input/output storage.
"""

baku = []
for _ in range(int(input())):  # Read number of test cases
    n, k = [int(t) for t in input().split()]  # Read n and k
    c = input().count("0")  # Count of '0's in the string
    m = n // 2 - min(c, n - c)  # Compute minimum moves needed for k good pairs
    baku.append("YES" if m <= k and (m - k) % 2 == 0 else "NO")  # Check if rearrangement is possible
print(*baku)


# https://github.com/VaHiX/codeForces/