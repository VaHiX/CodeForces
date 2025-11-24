# Problem: CF 2062 F - Traveling Salescat
# https://codeforces.com/contest/2062/problem/F

"""
F. Traveling Salescat

Algorithms/Techniques: 
Dynamic Programming with sorting and preprocessing. Each city is transformed into a point in 2D space (x, y) where x = a[i] + b[i], y = a[i] - b[i]. Then cities are sorted by y-coordinate. For each prefix of sorted cities, we maintain several DP states to compute minimum cost paths of increasing length. The key insight is that the cost between two cities i and j can be expressed as max(a[i] + b[j], b[i] + a[j]) = max(x[i] + y[j], x[j] + y[i]) where x[i] = a[i] + b[i], y[i] = a[i] - b[i].

Time Complexity: O(n^2 * log n) per test case, due to sorting and the nested loop DP updates.
Space Complexity: O(n) for storing DP arrays and intermediate values.
"""

class Q:
    def __init__(self, x, y):  # Transform city parameters into a point
        self.x, self.y = x + y, x - y  # x = a[i] + b[i], y = a[i] - b[i]

    def __lt__(self, rhs):  # Sort by y-coordinate
        return self.y < rhs.y


for _ in range(int(input())):
    n = int(input())
    a = [0] * n
    for i in range(n):
        x, y = map(int, input().split())
        a[i] = Q(x, y)  # Create transformed point
    a.sort()  # Sort by y-coordinate to enable DP processing
    
    l = [10**18] * (n + 1)  # DP array: minimum cost ending at i with last step moving left or backward
    sl = l.copy()          # DP array: cumulative minimum cost for current prefix
    slt = l.copy()         # DP array: minimum cost considering only moving right to rightmost node
    slrt = l.copy()        # DP array: overall minimum cost for path ending at position i
    s = 10**18
    
    for m, t in enumerate(a):  # Process each city in sorted order
        x, y = t.x, t.y
        
        # Update all DP states for all positions from right to left (reverse order)
        for i in range(m, 0, -1):
            slrt[i + 1] = min(slrt[i + 1], sl[i] + x + y, slt[i] + x * 2 + y * 2)  # Update path where we turn or extend
            slt[i + 1] = min(slt[i + 1], slt[i] + x * 2, sl[i] + x - y)       # Extend to right (rightward movement)
            sl[i + 1] = min(sl[i + 1], sl[i] + x * 2, l[i] + x + y)           # Update cumulative cost 
            l[i + 1] = min(l[i + 1], l[i] + x * 2)                            # Move in same direction
        sl[1] = min(sl[1], x - y)      # Initialize for small prefix
        l[1] = min(l[1], x * 2 - y * 2)  # Initialize for backward path
    
    print(*[x // 2 for x in slrt[2:]])  # Output results for k=2 to n, divide by 2 because we computed 2*cost


# https://github.com/VaHiX/codeForces/