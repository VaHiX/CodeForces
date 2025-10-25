# Problem: CF 1404 A - Balanced Bitstring
# https://codeforces.com/contest/1404/problem/A

"""
Algorithm: Balanced Bitstring
Techniques: Sliding window, greedy assignment, modular arithmetic

Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(k) for storing the master array of size k

The problem asks to determine if a given string with '?' characters can be made 
into a k-balanced bitstring by replacing '?' with '0' or '1'. A k-balanced bitstring 
means every substring of length k contains exactly k/2 zeros and k/2 ones.

Approach:
1. For each position in the string, we determine which "group" it belongs to based on modulo k.
2. We iterate through the string and for each character:
   - If it's not '?', we check if the corresponding group already has a fixed value.
   - If there is a conflict (different values in same group), return NO.
3. After processing all characters, we count how many 0s and 1s are in each group.
4. Since each group must contain exactly k/2 0s and 1s, we check if counts are within limits.

Steps:
- Process the string to build a "master" array of size k.
- For each character in the string, assign it to its corresponding group (i % k).
- If there's conflict between fixed values in same group, return NO.
- Count 0s and 1s in master groups.
- Check if no group exceeds k/2 count for either digit.
"""

import sys

input = sys.stdin.buffer.readline


def process(S, k):
    n = len(S)
    # Master array to store fixed values for each modulo group
    master = [None for i in range(k)]
    for i in range(n):
        si = S[i]
        if si != "?":
            # If this position's group already has a value
            if master[i % k] is None:
                # Assign the value to this group
                master[i % k] = si
            elif master[i % k] != si:
                # Conflict found: group was assigned different values
                sys.stdout.write("NO\n")
                return
    counts = [0, 0]  # counts[0] for '0's, counts[1] for '1's
    for c in master:
        if c is not None:
            if c == "0":
                counts[0] += 1
            elif c == "1":
                counts[1] += 1
    # Check if each group can be filled within limits
    if counts[0] <= k // 2 and counts[1] <= k // 2:
        sys.stdout.write("YES\n")
    else:
        sys.stdout.write("NO\n")


t = int(input())
for i in range(t):
    n, k = [int(x) for x in input().split()]
    S = input().decode().strip()
    process(S, k)


# https://github.com/VaHiX/codeForces/