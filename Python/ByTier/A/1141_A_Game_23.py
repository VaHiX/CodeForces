# Problem: CF 1141 A - Game 23
# https://codeforces.com/contest/1141/problem/A

"""
Problem: Game 23
Purpose: Determine the minimum number of moves to transform number n to m by multiplying by 2 or 3.
         Each move multiplies the current number by either 2 or 3.
         If transformation is impossible, return -1.

Algorithms/Techniques:
- Prime factorization approach:
  - We check if m can be obtained from n by only using factors 2 and 3.
  - Reduce m by dividing out all factors of 2 and 3.
  - If the result is 1, then it's possible; otherwise, impossible.
  - Count how many times we divided by 2 and 3 to get the total moves.

Time Complexity: O(log(m/n)) - We keep dividing until m equals n or becomes impossible.
Space Complexity: O(1) - Only using a few variables regardless of input size.

Input:
- Two integers n and m (1 <= n <= m <= 5*10^8)

Output:
- Number of moves (0 if n == m, -1 if impossible)
"""

n, m = map(int, input().split())
x = 0
r = m / n  # Ratio of m to n; we'll reduce this by factors of 2 and 3
for i in [2, 3]:  # Check for factors 2 and 3
    while r % i == 0:  # While ratio is divisible by current factor
        r /= i  # Divide the ratio by factor
        x += 1  # Increment move counter
print(x if r == 1 else -1)  # If ratio becomes 1, return moves; else return -1


# https://github.com/VaHiX/codeForces/