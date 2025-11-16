# Problem: CF 1715 D - 2+ doors
# https://codeforces.com/contest/1715/problem/D

"""
Algorithm: Bitwise OR constraints satisfaction with lexicographically smallest array
Techniques: 
- Bit manipulation and set operations
- Graph-like constraint propagation

Time Complexity: O(N + Q)
Space Complexity: O(N + Q)

The algorithm works as follows:
1. Initialize each element of the array to 2^31 - 1 (all bits set)
2. For each constraint (i, j, x), update the answer array by ANDing with x
3. Propagate constraints through the graph built from the statements
4. For each node, calculate the XOR of the propagated values to get the final answer
"""

N, Q = map(int, input().split())
ans = [2**31 - 1 for _ in range(N)] # Initialize all elements to maximum possible value
A = [set() for _ in range(N)] # Build adjacency list for constraints

# Process each constraint
for _ in range(Q):
    a, b, x = map(int, input().split())
    a -= 1 # Convert to 0-based indexing
    b -= 1
    A[a].add(b) # Add b to adjacency list of a
    A[b].add(a) # Add a to adjacency list of b
    ans[a] &= x # AND with x to restrict possible values
    ans[b] &= x

# Process each element to find correct value
for i in range(N):
    if i in A[i]: # If self-loop exists
        continue
    t = ans[i] # Start with current value
    for a in A[i]: # For each neighbor
        t &= ans[a] # AND with neighbor's value to propagate constraints
    ans[i] ^= t # XOR to update final value

print(*ans)


# https://github.com/VaHiX/CodeForces/