# Problem: CF 1949 I - Disks
# https://codeforces.com/contest/1949/problem/I

"""
Task: Determine if it's possible to decrease the sum of radii of disks while keeping
      tangent relationships intact and avoiding overlaps.

Algorithms/Techniques:
- Graph coloring (bipartite check)
- Geometric condition for tangency: two disks with centers (x1, y1), (x2, y2) and radii r1, r2 are tangent when
  (x1 - x2)^2 + (y1 - y2)^2 = (r1 + r2)^2

Time Complexity: O(n^2) due to checking all pairs of disks for tangency.
Space Complexity: O(n^2) for the adjacency list representation of the graph.

The problem reduces to checking whether a bipartite coloring is possible on a graph
where edges represent tangent relationships. If such a coloring exists and the two color classes
have different sizes, it indicates a valid assignment where one class can be increased and the other decreased
to reduce the total sum.
"""

n: int = int(input())
points: list[list] = [] * n  # This line is faulty but kept as per instruction
g: list[list] = [[] for _ in range(n)]
for i in range(n):
    x, y, r = map(int, input().split())
    for j in range(i):  # Check only previous disks for tangency
        dx, dy, sr = x - points[j][0], y - points[j][1], r + points[j][2]
        if dx**2 + dy**2 == sr**2:  # Tangent condition
            g[i].append(j)
            g[j].append(i)
    points.append([x, y, r])
ans = False
col = [0] * n  # Color array for bipartite check (0 = unvisited, 1 = color A, 2 = color B)
for i in range(n):
    if not col[i]:
        st = [i]
        col[i] = 1
        s1, s2 = 1, 0  # Count of nodes in each color group
        f = True
        while st:
            u = st.pop()
            for v in g[u]:
                if not col[v]:
                    col[v] = 3 - col[u]  # Assign opposite color
                    if col[v] == 1:
                        s1 += 1
                    else:
                        s2 += 1
                    st.append(v)
                elif col[v] == col[u]:  # Conflict: same color as current node
                    f = False
        if f and s1 != s2:  # If bipartite and sizes differ
            ans = True
            break
print("YES" if ans else "NO")


# https://github.com/VaHiX/codeForces/