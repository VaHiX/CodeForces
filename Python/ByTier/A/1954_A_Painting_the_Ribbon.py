# Problem: CF 1954 A - Painting the Ribbon
# https://codeforces.com/contest/1954/problem/A

"""
Algorithm/Techniques: Greedy, Math
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem is about determining if Alice can prevent Bob from making all parts of the ribbon the same color.
Key idea:
- If there are m colors and n parts, and Bob can repaint at most k parts,
  Alice needs to ensure that it's impossible for Bob to make all parts the same color.
- The minimum number of parts that need to be "fixed" to make all parts the same color is:
  - If n % m == 0, then each color must be used exactly n/m times.
    So, the number of parts that must be painted differently to achieve a uniform color is: n - n/m.
  - If n % m != 0, then some colors will be used (n//m + 1) times and others (n//m) times.
    So, the number of parts that must be repainted to make all the same color is: n - (n//m + 1).
- If the number of parts that must be repainted exceeds k, then Alice wins (output YES).
  Otherwise, Bob can win (output NO).
"""

w = int(input())
for i in range(w):
    n, m, k = map(int, input().split())
    if n % m == 0:
        # When parts can be evenly distributed among colors
        if (n - (n // m)) <= k:
            print("NO")
        else:
            print("YES")
    else:
        # When parts cannot be evenly distributed, one color will have one extra part
        if (n - ((n // m) + 1)) <= k:
            print("NO")
        else:
            print("YES")


# https://github.com/VaHiX/CodeForces/