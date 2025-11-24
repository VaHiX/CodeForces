# Problem: CF 1965 E - Connected Cubes
# https://codeforces.com/contest/1965/problem/E

"""
Connected Cubes Problem

Algorithm:
- The solution uses a strategy to connect components of each color by placing additional cubes
  in a structured way to ensure connectivity within each color group.
- It creates a "bridge" or "path" around the existing cubes using additional cubes placed in 
  specific positions to connect disconnected components.
- The approach builds structures around the initial grid, placing cubes in layers to ensure all 
  same-colored cubes are connected through face-sharing paths.

Time Complexity:
- O(n * m * k) where n, m, k are the dimensions/number of colors. 
  The algorithm iterates through the grid and creates additional cubes based on the 
  existing structure.

Space Complexity:
- O(n * m * k) for storing the additional cubes that will be output.
"""

n, m, k = map(int, input().split())
a = []

for i in range(n):
    a.append(list(map(int, input().split())))

ans = []

# Fill the first layer (z=1) of the grid with cubes
for x in range(n):
    for y in range(m):
        for z in range(1, n + 1):
            if y % 2 == 1:
                ans.append([x, y, z, a[x][y]])
            else:
                ans.append([x, y, z, a[min(x, n - z)][y]])
        # Additional cubes in higher z layers to support connectivity
        for z in range(n + 1, n + k + 1):
            if y % 2 == 1:
                ans.append([x, y, z, a[x][y]])
            else:
                ans.append([x, y, z, z - n])

# Place additional cubes in a new x-layer (x from n to n+k)
for x in range(n, n + k):
    for y in range(m):
        for z in range(1, n + 1):
            if y % 2 == 1:
                ans.append([x, y, z, x - n + 1])
            else:
                ans.append([x, y, z, a[n - z][y]])
        # Add a final cube in the layer z = n+1 for this x-layer
        ans.append([x, y, n + 1, x - n + 1])

# Add cubes along the boundary of x=n in higher z layers
for y in range(m):
    for z in range(n + 2, n + k + 1):
        ans.append([n, y, z, z - n])

# Add cubes to form a bridge in x-direction for higher values of x
for x in range(n + 1, n + k):
    for z in range(n + 2, n + k + 1):
        ans.append([x, 0, z, max(x - n + 1, z - n)])

# Print the number of additional cubes added
print(len(ans))

# Print the coordinates and colors of all added cubes
for cube in ans:
    print(cube[0] + 1, cube[1] + 1, cube[2] + 1, cube[3])


# https://github.com/VaHiX/CodeForces/