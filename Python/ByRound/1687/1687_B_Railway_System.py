# Problem: CF 1687 B - Railway System
# https://codeforces.com/contest/1687/problem/B

"""
Algorithm: 
This code solves an interactive problem to determine the minimum spanning tree (MST) capacity of a railway system.
The approach uses queries to determine which edges are part of the MST by checking if adding an edge increases the maximum capacity.
It first queries each edge individually to obtain the maximum capacity when only that edge is active. Then it uses these values
to find which edges should be included in the MST.

Time Complexity: O(m^2)
Space Complexity: O(m)

The algorithm works by:
1. First, querying each edge independently to get the impact of that edge on the maximum capacity.
2. Then, iteratively determining whether to include each edge in the final MST by checking if its inclusion affects
   the overall capacity.
3. Finally, outputting the minimum capacity of the full spanning forest, which is the total weight of the MST.

Note: This solution uses at most 2*m queries as required.
"""

n, m = map(int, input().split())
a = []
for i in range(m):
    # Query each edge individually to determine its impact on maximum capacity
    print("?", "0" * i + "1" + "0" * (m - i - 1), flush=1)
    a.append(int(input()))

cur = 0
s = ["0" for i in range(m)]  # s represents the current set of active edges

# Try to build the MST by adding edges one by one
for i in range(m):
    # Find the edge with the smallest impact on maximum capacity (i.e., least important edge)
    x = 0
    for j in range(m):
        if a[x] > a[j]:
            x = j
    
    # Set the selected edge as active in the current solution
    s[x] = "1"
    print("? ", *s, sep="", flush=1)
    c = int(input())
    
    # If including this edge actually increases the maximum capacity, we include it in the MST
    if cur + a[x] == c:
        cur += a[x]
    else:
        # Otherwise, this edge is not needed in the MST, so we unset it
        s[x] = "0"
    
    # Mark the edge as processed by setting its value to a large number
    a[x] = 2000000

# Output the minimum capacity (which is the MST weight)
print("!", cur, flush=1)


# https://github.com/VaHiX/CodeForces/