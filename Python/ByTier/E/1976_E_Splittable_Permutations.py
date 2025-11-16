# Problem: CF 1976 E - Splittable Permutations
# https://codeforces.com/contest/1976/problem/E

"""
Algorithm: Union-Find + Dynamic Programming

The problem models a process where a permutation is split into subarrays, tracking the maximum element in each part.
We need to count how many original permutations can produce the given sequences of left and right maximums.

Approach:
1. Build a linked list using the l and r values to represent how elements are connected after splits
2. Traverse the resulting linked list to form a sequence of max elements
3. Use dynamic programming to compute valid permutations based on the structure formed

Time Complexity: O(n log n) due to sorting and union-find operations
Space Complexity: O(n) for storing the linked list and auxiliary arrays
"""

from sys import *

input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())
MOD = 998244353

n, q = inputlist()
l = list(inputlist())
r = list(inputlist())
ll = [None] * (n + 1)  # Left linked list pointer
rll = [None] * (n + 1)  # Right linked list pointer
start = l[0]  # Starting point of the linked list

# Process each operation to build the linked list structure
for i in range(q):
    if l[i] > r[i]:
        # When l[i] > r[i], we connect l[i]'s right to r[i] and vice versa
        ll[r[i]] = ll[l[i]]  # r[i] points to where l[i] pointed
        if ll[l[i]]:  # If l[i] had a left connection
            rll[ll[l[i]]] = r[i]  # Update that previous left to point to r[i]
        ll[l[i]] = r[i]  # l[i] now points to r[i]
        rll[r[i]] = l[i]  # r[i] points to l[i]
        if r[i] == start:  # If start was the right value, update it
            start = l[i]
    else:
        # When l[i] <= r[i], update the links accordingly
        if rll[r[i]]:  # If r[i] had a right connection
            ll[rll[r[i]]] = l[i]  # Update that connection to point to l[i]
        rll[l[i]] = rll[r[i]]  # Update l[i]'s right to point to r[i]'s previous
        ll[l[i]] = r[i]  # l[i] points to r[i]
        rll[r[i]] = l[i]  # r[i] points to l[i]
        if r[i] == start:  # If start was the right value, update it
            start = l[i]

# Traverse the linked list to get the order of elements
visited = [0] * (n + 1)
order = []
current = start
while current is not None:
    order.append(current)
    visited[current] = 1
    current = ll[current]  # Move to next element in the linked list

# Calculate maxes for dynamic programming
maxes = sorted(
    [order[0]]
    + [max(order[i], order[i + 1]) for i in range(len(order) - 1)]
    + [order[-1]]
)
counts = [0] * (n + 1)
for i in maxes:
    counts[i] += 1  # Count how many times each number appears as a max

# DP array for computing number of valid permutations
dp = [len(maxes)] * (n + 1)
for i in range(2, n + 1):
    dp[i] = dp[i - 1] - counts[i - 1]  # Adjust dp values based on counts

# Final calculation for answer
ans = 1
adjust = 0
for num in reversed(range(1, n + 1)):
    if visited[num]:
        continue  # Skip already processed numbers
    ans *= dp[num] + adjust  # Multiply with current valid options
    ans %= MOD  # Apply modulo
    adjust += 1  # Increment adjustment for next iteration

print(ans)


# https://github.com/VaHiX/CodeForces/