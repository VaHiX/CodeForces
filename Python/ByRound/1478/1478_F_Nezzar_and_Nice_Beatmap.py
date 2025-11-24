# Problem: CF 1478 F - Nezzar and Nice Beatmap
# https://codeforces.com/contest/1478/problem/F

"""
Algorithm: Nezzar and Nice Beatmap
Approach:
- The problem requires ordering points such that for any three consecutive points A, B, C, 
  the angle ABC is strictly less than 90 degrees.
- A greedy heuristic is used:
  - Start with an arbitrary point (here, point 0).
  - At each step, select the point that is farthest from the last added point.
  - This greedy approach is based on the idea that selecting a point further away 
    will help ensure smaller angles in the sequence.

Time Complexity:
- O(n^2) due to nested loops where for each of the n points, we check all remaining points.
- Outer loop runs n times, inner loop runs up to n times.

Space Complexity:
- O(n) for storing the points, answer array, and seen array.
"""

def dist(p, q):
    # Calculate squared distance between two points to avoid sqrt computation
    return (p[0] - q[0]) ** 2 + (p[1] - q[1]) ** 2


n = int(input())
points = []
for i in range(n):
    x, y = map(int, input().split())
    points.append((x, y))

ans = [0]  # Start with the first point (index 0)
seen = [0] * n  # Track visited points
seen[0] = 1  # Mark the first point as visited

for i in range(1, n):
    # Initialize max distance and index
    mx = -1
    idx = -1
    
    # Iterate through all unvisited points
    for j in range(n):
        if seen[j] == 0:
            # Compute squared distance from last point in sequence to current unvisited point
            current_dist = dist(points[j], points[ans[-1]])
            # Select the point with maximum distance (greedy choice)
            if mx < current_dist:
                mx = current_dist
                idx = j
    
    # Add selected point to the result
    ans.append(idx)
    # Mark the point as visited
    seen[idx] = 1

# Print the permutation (1-indexed)
print(*[i + 1 for i in ans])


# https://github.com/VaHiX/CodeForces/