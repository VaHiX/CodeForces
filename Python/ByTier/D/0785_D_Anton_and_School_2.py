# Problem: CF 785 D - Anton and School - 2
# https://codeforces.com/contest/785/problem/D

"""
Algorithm: Dynamic Programming with Combinatorics
Purpose: Count the number of distinct subsequences that form a Regular Simple Bracket Sequence (RSBS)
- An RSBS must start with '(' and end with ')', and be properly nested.
- We precompute factorials and their modular inverses for combinations.
- We iterate through each position, and for each opening bracket that can be matched,
  we compute how many valid ways we can form an RSBS using previous opening brackets and 
  following closing brackets.
Time Complexity: O(n)
Space Complexity: O(n)
"""

R = 2 * 10**5
M = 10**9 + 7
F = [1] * (R + 1)
for i in range(1, R + 1):
    F[i] = (F[i - 1] * i) % M
Fhyp = [1] * (R + 1)
Fhyp[R] = pow(F[R], M - 2, M)
for i in range(R - 1, -1, -1):
    Fhyp[i] = (Fhyp[i + 1] * (i + 1)) % M


def C(n, k):
    # Compute combination C(n, k) modulo M
    if n < 0 or k < 0 or n < k:
        return 0
    return (F[n] * Fhyp[n - k] * Fhyp[k]) % M


s = [e == ")" for e in input()]  # Convert input to list of booleans: True for ')', False for '('
n = len(s)
l = [0] * n  # l[i] = number of '(' up to and including position i
l[0] = int(s[0] == 0)  # 0 is '('
for i in range(1, n):
    l[i] = l[i - 1] + (s[i] == 0)
r = [0] * n  # r[i] = number of ')' from position i to end
r[-1] = int(s[-1] == 1)  # 1 is ')'
for i in range(n - 2, -1, -1):
    r[i] = r[i + 1] + (s[i] == 1)
S = 0
# For each possible middle point where we match an opening bracket with a closing one
for i in range(n - 1):
    # Add combinations only if there are both '(' before and ')' after this point, and s[i] is '('
    S += C(l[i] + r[i + 1] - 1, l[i]) * (l[i] > 0 and r[i + 1] > 0 and s[i] == 0)
print(S % M)


# https://github.com/VaHiX/CodeForces/