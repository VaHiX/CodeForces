# Problem: CF 1879 E - Interactive Game with Coloring
# https://codeforces.com/contest/1879/problem/E

"""
Interactive Game with Coloring - Tree Edge Coloring Problem

This problem asks to color edges of a tree such that we can guarantee a win in an interactive game.
The game works as follows:
1. A chip is placed on a vertex (not root) at the start
2. We move the chip towards root in exactly d moves (where d is distance from root)
3. At each step, we're told how many edges of each color are incident to current vertex
4. We choose a color and move the chip along an edge of that color

Algorithm approach:
- First check if all vertices are connected directly to root (star graph)
- If yes, single color suffices
- Otherwise, we need to try to find a valid 2-coloring or 3-coloring
- For general tree, we use a greedy approach to color edges:
  - Try to color using 2 colors first
  - If that fails, use 3 colors
- The key insight is to ensure that from any vertex, the path to root is uniquely determined

Time Complexity: O(n^2) - for processing tree structure and attempts at coloring
Space Complexity: O(n^2) - storing tree structure and color assignments

Algorithms/Techniques:
- Tree traversal (DFS)
- Graph coloring
- Adaptive strategy for interactive problem
"""

n = int(input())
p = list(map(int, input().split()))
zv = [None] * (n - 1)
if len(set(p)) == 1:
    # All vertices connected directly to root - star graph
    # Single color suffices for winning strategy
    print(1)
    print(*([1] * (n - 1)))
    while int(input()) == 0:
        s = input()
        print(1)
    exit(0)
    
# Build adjacency list representation of tree
detei = [None] * n
for i in range(n):
    detei[i] = []
for i in range(n - 1):
    detei[p[i] - 1].append(i + 1)

# Initialize structures for tracking color constraints
det1 = [None] * len(detei[0])  # For storing constraints
for i in range(len(det1)):
    det1[i] = set()

# Recursive function to assign colors and check constraints
def ras(x):
    global a
    z = zv[x - 1]
    for i in detei[x]:
        zv[i - 1] = 3 - z  # Assign alternating colors
        ras(i)
    # If we reached a leaf then check if there's a conflict
    if len(detei[x]) == 1:
        if b:
            # Record the difference in color assignments
            det1[k].add(zv[x - 1] - zv[detei[x][0] - 1])
            if len(det1[k]) >= 2:
                a = False  # Conflict detected

a = b = True  # Flags for color check
# Try 2-coloring strategy
for e in range(len(det1)):
    k = e
    zv[detei[0][k] - 1] = 1  # Start with color 1
    ras(detei[0][k])
if a:
    # 2-coloring failed, fall back to 3-coloring
    b = False
    # Try to fix by changing initial color assignment
    for k in range(len(det1)):
        if len(det1[k]) != 0:
            for i in det1[k]:
                if i == -1:
                    zv[detei[0][k] - 1] = 2
                    ras(detei[0][k])
    print(2)  # Use 2 colors
    print(*zv)
    while int(input()) == 0:
        s = list(map(int, input().split()))
        if s[1] == 1:
            print(2)  # Choose color 2
        else:
            print(1)  # Choose color 1
    exit(0)
else:
    # 3-coloring approach for general case
    def ras2(x):
        z = zv[x - 1]
        for i in detei[x]:
            zv[i - 1] = 1 + z % 3  # Use modular arithmetic for 3 colors
            ras2(i)

    # Assign colors using 3-coloring approach
    for e in range(len(det1)):
        k = e
        zv[detei[0][k] - 1] = 1
        ras2(detei[0][k])
    print(3)  # Use 3 colors
    print(*zv)
    while int(input()) == 0:
        s = list(map(int, input().split()))
        # Choose color based on available edges
        if s[0] != 1:
            if s[1] != 1:
                print(3)
            else:
                print(2)
        elif s[2] != 1:
            print(1)
        else:
            print(3)
    exit(0)


# https://github.com/VaHiX/CodeForces/