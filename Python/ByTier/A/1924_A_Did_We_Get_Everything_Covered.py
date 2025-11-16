# Problem: CF 1924 A - Did We Get Everything Covered?
# https://codeforces.com/contest/1924/problem/A

"""
Purpose: 
    Determine if all possible strings of length n formed using the first k lowercase letters 
    occur as subsequences in the given string s. If not, output one such missing string.

Algorithms/Techniques:
    - Sliding window approach to count how many unique characters from first k letters 
      appear in segments of string s
    - Greedily build the answer string by tracking which characters are missing

Time Complexity: O(m + n*k) where m is length of string s, n is length of desired strings, k is number of letters used
Space Complexity: O(k) for the cnt array and O(n) for the ans list

Approach:
    - Traverse the string s and keep track of unique characters seen in current segment
    - When we see all k characters, we've found one subsequence that includes all characters
    - Count how many such full segments we can form
    - If formed count >= n, then all combinations can be made as subsequences
    - Otherwise, construct a missing string by ensuring we include a character not in the last partial segment
"""

import sys

input = lambda: sys.stdin.readline()
t = int(input())
for _ in range(t):
    n, k, m = map(int, input().split())
    s = input().rstrip()
    cnt = [0] * k  # Track presence of characters (0 or 1)
    cnti = 0       # Count of full segments with all k characters
    cnts = 0       # Count of unique chars in current segment
    ans = []       # Store characters from full segments
    for i in range(m):
        ix = ord(s[i]) - ord("a")  # Convert char to index (0-25)
        if cnt[ix] == 0:           # If not seen in current segment
            cnt[ix] = 1            # Mark as seen
            cnts += 1              # Increment count of unique chars
        if cnts == k:              # If we've seen all k chars in this segment
            cnts = 0               # Reset counter for next segment
            cnti += 1              # Increment segment count
            ans.append(chr(ord("a") + ix))  # Store last char of segment
            for j in range(k):     # Reset segment tracking
                cnt[j] = 0
    if cnti >= n:                  # If enough full segments to form all n-length strings
        print("YES")
    else:
        print("NO")
        # Find first character not in the last partial segment
        for ii in range(k):
            if cnt[ii] == 0:
                ans.append(chr(ii + ord("a")))  # Add that character
                break
        # Fill remaining positions with 'a' (the smallest character)
        ans = ans + ["a"] * (n - len(ans))
        print("".join(ans))


# https://github.com/VaHiX/CodeForces/