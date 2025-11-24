# Problem: CF 2000 F - Color Rows and Columns
# https://codeforces.com/contest/2000/problem/F

"""
F. Color Rows and Columns

Purpose:
This code solves the problem of coloring rectangles to maximize points (where each complete row or column colored earns 1 point) with a minimum number of operations to score at least k points.

Techniques:
Dynamic Programming (DP) approach:
- For each rectangle, we simulate all possible ways of coloring rows/columns.
- We compute the cost (operations) to achieve different numbers of points from that rectangle.
- Then we combine these costs using DP over rectangles to find a minimum total for k points.

Time Complexity: O(n * max(a,b) * k^2)
Space Complexity: O(k)

Input Format:
- Number of test cases t
- For each case: n (number of rectangles), k (required points)
- Then n lines with a, b for each rectangle

Output:
Minimum number of operations to score at least k points, or -1 if impossible.
"""

inf = 2 * 10**9
for _ in range(int(input())):
    n, k = map(int, input().split())
    d = [inf] * (k + 1)  # DP array: d[i] = min cost to get exactly i points
    d[0] = 0  # Base case: no points costs nothing
    
    for _ in range(n):
        a, b = map(int, input().split())
        cost = reward = 0
        ndp = d[:]  # Copy current DP state
        
        # Enumerate all possible ways to color some rows/columns of this rectangle
        while (a > 0 or b > 0) and reward <= k:
            reward += 1
            # Preferentially color the side with more units left
            if a > b:
                cost += b
                a -= 1
            else:
                cost += a
                b -= 1
            
            # Update DP for all possible combinations of previous points + new points
            for i in range(k - reward + 1):
                ndp[i + reward] = min(ndp[i + reward], d[i] + cost)
        
        d = ndp  # Move to next state
    
    if d[k] == inf:
        print(-1)
    else:
        print(d[k])


# https://github.com/VaHiX/codeForces/