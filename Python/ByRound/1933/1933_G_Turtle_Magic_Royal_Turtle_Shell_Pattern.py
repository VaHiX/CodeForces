# Problem: CF 1933 G - Turtle Magic: Royal Turtle Shell Pattern
# https://codeforces.com/contest/1933/problem/G

"""
Code Purpose:
This code solves the "Turtle Magic: Royal Turtle Shell Pattern" problem where we need to calculate the number of valid ways to place fortune cookies (circle or square) in an n×m grid such that no three consecutive cells in any of the 8 directions (horizontal, vertical, or diagonal) have the same shape.

Algorithms/Techniques:
- Bitmasking and state tracking: The solution uses a bitmask approach to track valid configurations.
- Dynamic programming on small grid patterns: Precomputed valid patterns for small sections of the grid.
- Checking constraints: After each operation, the code validates whether any new constraint is violated.

Time Complexity: O(q * log(n*m)) where q is the number of operations and n, m are the dimensions.
Space Complexity: O(1) as we use a fixed-size array for state tracking.

Note: This is a simplified version assuming certain properties that allow for precomputed valid patterns.
"""

def LI():
    return list(input().split())

def II():
    return int(input())

def MII():
    return map(int, input().split())

def main():
    n, m, q = MII()
    # Precomputed valid patterns for each state (represented in binary masks)
    checks = [3, 6, 12, 9]
    # Initialize 2x4 matrix to represent state
    v = [[1] * 4 for _ in range(2)]
    ans = 8
    print(ans)
    for _ in range(q):
        x, y, t = LI()
        x = int(x)
        y = int(y)
        # Convert shape to binary (1 for circle, 0 for square)
        t = 1 if t[0] == "c" else 0
        # Iterate through the two possible states
        for cur in range(2):
            # Swap x and y for different orientation processing
            x, y = y, x
            # Calculate current bit pattern
            a = (y & 1) ^ t
            b = x % 4
            # For each of the 4 possible states
            for i in range(4):
                # Check if bit pattern matches and update states
                if v[cur][i] and checks[i] >> b & 1 != a:
                    ans -= 1
                    v[cur][i] = 0
        print(ans)
    return


t = II()
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/