# Problem: CF 2045 C - Saraga
# https://codeforces.com/contest/2045/problem/C

# Flowerbox
"""
Purpose: 
    Find the minimum length "interesting abbreviation" of two strings S and T.
    An abbreviation is interesting if it can be split into a prefix of S and a suffix of T,
    such that there exist at least two different ways to perform this split.

Algorithms/Techniques:
    - Brute-force character-by-character check for common characters in S and T
    - For each common character, compute how the resulting concatenation of 
      prefix from S and suffix from T can be minimized

Time Complexity: O(|S| * |T|) in worst case, but more efficiently bounded due to 
                 limited alphabet size (26 lowercase letters). Can be considered O(26 * |S| + |T|) ~ O(|S| + |T|).

Space Complexity: O(1) excluding input strings. The only extra space used is for variables and fixed-size alphabet string.

"""

S = input()
T = input()
l = len(S) + len(T)
m = "-1"
s = "abcdefghijklmnopqrstuvwxyz"
for h in s:
    i = 1 + S[1:].find(h)      # Find first occurrence of character h in S (after index 0), +1 for 1-based indexing
    j = T[:-1].rfind(h)        # Find last occurrence of character h in T (before last char), -1 if not found
    if i == 0 or j == -1:      # If either prefix/suffix split is invalid, skip
        continue
    new = S[:i] + T[j:]        # Concatenate prefix up to i and suffix from j onward
    k = len(new)
    if k <= l:                 # Update minimum length abbreviation if current is shorter or equal
        m = new
        l = k
print(m)


# https://github.com/VaHiX/codeForces/