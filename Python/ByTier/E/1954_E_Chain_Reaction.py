# Problem: CF 1954 E - Chain Reaction
# https://codeforces.com/contest/1954/problem/E

"""
Algorithm: Chain Reaction Problem
Purpose: For each damage value k from 1 to max_health, compute the minimum number of seconds to kill all monsters.
Approach:
- Use a sweep line / coordinate compression technique to process monsters in order of increasing health.
- Maintain a BIT (Binary Indexed Tree) like structure to track active segments.
- Precompute the minimum seconds needed for each possible k using the precomputed f array.
Time Complexity: O(max(a) * log(max(a)) + n * log(n))
Space Complexity: O(max(a) + n)
"""

N = int(input())
ans = []
a = [int(x) for x in input().split()]
b = [(i, a[i]) for i in range(len(a))]
S = sorted(b, key=lambda x: x[1])
m = max(a)
bits = [0] + [1] * N + [0]  # Initialize BIT with 1s for active positions
wtr = [[] for q in range(N)]
f = []
g = 1
last = 0
for i, num in S:  # Process monsters in increasing order of health
    for e in range(num - last):  # For each step between previous and current health
        f.append(g)  # Store the current number of operations needed
    last = num
    bits[i + 1] = 0  # Mark this monster as dead (inactive)
    g += bits[i] + bits[i + 2] - 1  # Update global counter based on neighbors
for d in range(1, m + 1):  # For each damage value from 1 to max_health
    result = 0
    for x in range(1 + (m - 1) // d):  # Sum up contributions for multiples of d
        result += f[d * x]  # Add the precomputed values
    ans.append(result)
print(*ans)


# https://github.com/VaHiX/CodeForces/