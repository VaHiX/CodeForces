# Problem: CF 1898 A - Milica and String
# https://codeforces.com/contest/1898/problem/A

"""
Problem: Milica and String
Algorithm: Greedy approach to minimize operations
Time Complexity: O(n^2) in worst case due to nested loop and string operations
Space Complexity: O(1) - only using a few variables for tracking

Approach:
- Count initial number of B's in string
- If current B count equals target k, no operations needed
- Otherwise, determine whether we need to increase or decrease B's
- Use greedy method to find earliest position where we can make a single operation to reduce difference
- Change prefix of string to get desired final count of B's

Techniques:
- Greedy selection of operation
- Iterative checking from left to right to find optimal position
"""

e = [*open(0).read().split()][1:]
for n, k, s in zip(*[iter(e)] * 3):
    n = int(n)
    k = int(k)
    B = s.count("B")
    if B == k:
        print(0)
    else:
        # Determine which character to use and direction of change
        x, y = ["AB", "BA"][B > k]
        c = [1, -1][B > k]
        for i in range(n):
            # Update B count by checking if current character matches x
            B += c * (s[i] == x)
            if B == k:
                print(1)
                print(i + 1, y)
                break


# https://github.com/VaHiX/CodeForces/