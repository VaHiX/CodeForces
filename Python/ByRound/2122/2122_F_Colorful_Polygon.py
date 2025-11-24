# Problem: CF 2122 F - Colorful Polygon
# https://codeforces.com/contest/2122/problem/F

"""
F. Colorful Polygon

Purpose:
This code constructs a simple polygon with at most 333 vertices such that the number of triangulations 
of the polygon equals (a1 + a2 + ... + an)! / (a1! * a2! * ... * an!). This is based on the fact that 
the number of triangulations of a polygon can be represented as a product of Catalan numbers or via 
a specific construction using "flowers" and "chains".

Algorithms/Techniques:
- A constructive algorithm based on building polygon vertices in a specific pattern (line-by-line arrangement).
- Uses prefix sums and careful vertex placement to ensure correct number of triangulations.

Time Complexity: O(n^2) due to nested loops for constructing points.
Space Complexity: O(n^2) for storing the low and high point arrays which grow roughly quadratically with n.

Input Format:
- First line: integer n (number of elements)
- Second line: n integers a1, a2, ..., an

Output Format:
- First line: number of vertices m
- Next m lines: x, y coordinates of each vertex

"""
n = int(input())
a = [int(t) for t in input().split()]
low = []
high = []
x = y = 0
for i in range(n - 1):
    s, t = a[2 * i : 2 * (i + 1)]  # Take two elements at a time to define segment sizes
    a.append(a[2 * i] + a[2 * i + 1])  # Append sum for next level
    L = max(s, t)  # Determine maximum size to place next structure
    low.append((x, y))  # Add starting point for lower chain
    high.append((x, y + 2))  # Add starting point for upper chain
    for j in range(s - 1):  # Add intermediate points for lower chain
        low.append((x + 5 + j, y))
    for j in range(t - 1):  # Add intermediate points for upper chain
        high.append((x + 5 + j, y + 2))
    low.append((x + L + 10, y))  # End point of lower chain
    high.append((x + L + 11, y + 2))  # End point of upper chain
    if i < n - 2:  # If not the last pair, add connection between chains
        low.append((x + L + 9, y - 1))
    x += L + 10  # Move x coordinate forward
    y -= 4  # Move y coordinate downward
print(len(low) + len(high))
for pt in low:
    print(*pt)
for pt in reversed(high):
    print(*pt)


# https://github.com/VaHiX/codeForces/