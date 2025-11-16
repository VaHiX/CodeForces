# Problem: CF 1906 L - Palindromic Parentheses
# https://codeforces.com/contest/1906/problem/L

"""
Construct a balanced parentheses sequence of length N with longest palindromic subsequence (LPS) of exactly K.

Algorithm:
- If K * 2 < N or K == N, it's impossible to construct such a sequence.
- Otherwise:
  - Use a strategy that builds the sequence by placing a number of balanced parentheses at the start and end
  - The middle part is filled with unbalanced parentheses to adjust the LPS to K
  - The construction logic:
    - Place (k - n//2 + 1)//2 pairs of "()" at the start
    - Place (n - k) opening parentheses
    - Place (n - k) closing parentheses
    - Place (k - n//2)//2 pairs of "()" at the end

Time Complexity: O(N)
Space Complexity: O(N)
"""

n, k = map(int, input().split())
if k * 2 < n or k == n:
    print("-1")
else:
    print(
        (k - n // 2 + 1) // 2 * "()"
        + "(" * (n - k)
        + ")" * (n - k)
        + (k - n // 2) // 2 * "()"
    )


# https://github.com/VaHiX/CodeForces/