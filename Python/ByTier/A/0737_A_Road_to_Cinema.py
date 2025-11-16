# Problem: CF 737 A - Road to Cinema
# https://codeforces.com/contest/737/problem/A

"""
Code Purpose:
This code solves the problem of finding the minimum cost car that can reach the cinema in time.
The approach uses binary search on the fuel tank capacity to determine the minimum price car that satisfies the time constraint.
Key Algorithms/Techniques:
1. Binary search on the answer (fuel capacity)
2. Greedy assignment of driving modes (accelerated vs normal)
3. Preprocessing of gas station positions
Time Complexity: O(n log n + k log(max_distance) + log(max_capacity) * log(n))
Space Complexity: O(n + k)

The solution involves:
1. Sorting cars by fuel capacity
2. Filtering out dominated cars (same or higher price with lower capacity)
3. Preprocessing gas station positions
4. Binary search on fuel capacity
5. Checking feasibility using greedy strategy
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")


n, k, s, t = na()
cv = [na() for _ in range(n)]
cv = sorted(cv, key=lambda x: x[1]) # Sort by fuel capacity

# Filter out dominated cars - keep only those that are not dominated by previous ones
z = []
for i in range(n):
    if len(z) == 0:
        z.append(cv[i])
    else:
        # Remove all cars with higher price than current one
        while z and z[-1][0] >= cv[i][0]:
            z.pop()
        z.append(cv[i])

g = [0] + sorted(na()) + [s] # Add start and end points to gas stations

d = 0
ans = 10**18

# Function to check if a car with given fuel capacity can reach on time
def check(v):
    res = 0
    for j in range(k + 1): # For each segment between gas stations
        D = g[j + 1] - g[j] # Length of current segment
        if D > v: # If segment length exceeds tank capacity, impossible to complete
            return False
        if v <= 2 * D: # If tank capacity is small enough to use accelerated mode
            res += 3 * D - v # Time = 3*D - v (accelerated for D km, then normal for D km, total D*2 + D = 3D, but we save fuel)
        else: # If tank capacity is sufficient to drive entire segment in normal mode
            res += D # Time = D
    if res <= t:
        return True
    else:
        return False

# If even the car with maximum capacity can't make it, impossible
if check(z[-1][1]) == False:
    print(-1)
    exit()

ok = len(z) - 1 # Upper bound for binary search
ng = -1 # Lower bound for binary search

# Binary search on fuel capacity
while ok - ng > 1:
    mid = (ok + ng) // 2
    if check(z[mid][1]): # If capacity 'mid' works, try smaller
        ok = mid
    else: # If capacity 'mid' doesn't work, try larger
        ng = mid

print(z[ok][0]) # Output minimum price among valid cars


# https://github.com/VaHiX/CodeForces/