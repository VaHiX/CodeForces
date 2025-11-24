# Problem: CF 1919 F2 - Wine Factory (Hard Version)
# https://codeforces.com/contest/1919/problem/F2

"""
Segment Tree with Lazy Propagation for Dynamic Wine Factory Problem

This solution uses a segment tree to efficiently compute and update the wine production process
in a factory with n water towers connected by valves.

Algorithms/Techniques:
- Segment Tree: For efficient range queries and updates
- Dynamic Programming on Tree: To track water flow and wine production

Time Complexity: O((n + q) * log n)
Space Complexity: O(n * log n)

The segment tree stores for each node:
- amount: water available at this node
- strength: wizard power at this node
- throughput: maximum flow capacity to next node
- wine: wine production at this node

Each update and query operation takes O(log n) time.
"""

from sys import stdin

n, q = map(int, stdin.readline().split())

amount = list(map(int, stdin.readline().split()))
strength = list(map(int, stdin.readline().split()))
throughput = list(map(int, stdin.readline().split()))
throughput.append(0)  # Add dummy element for easier indexing
wine = [0] * n
for i in range(n):
    w = min(amount[i], strength[i])
    amount[i] -= w
    strength[i] -= w
    wine[i] += w
    amount[i] = min(amount[i], throughput[i])  # Water that can flow to next tower
    throughput[i] -= amount[i]  # Remaining capacity

# Build segment tree
n2 = 1
while n2 < n:
    n2 <<= 1  # Find next power of 2

# Extend arrays to fit segment tree structure
for l in [amount, strength, wine, throughput]:
    l.extend([0] * (n2 - n))
    l[0:0] = [0] * (n2 - 1)

# Build initial segment tree bottom-up
for i in reversed(range(n2 - 1)):
    l = 2 * i + 1
    r = l + 1
    dw = min(amount[l], strength[r])
    wine[i] = wine[l] + wine[r] + dw
    db = min(strength[r] - dw, throughput[l])
    strength[i] = strength[l] + db
    da = min(amount[l] - dw, throughput[r])
    amount[i] = amount[r] + da
    throughput[i] = min(throughput[l] - db, throughput[r] - da)


for query_id in range(q):
    p, a, b, c = map(int, stdin.readline().split())
    i = p + n2 - 2  # Adjust index for leaf node in segment tree
    
    # Update current node values
    w = min(a, b)
    wine[i] = w
    amount[i] = min(a - w, c)
    strength[i] = b - w
    throughput[i] = c - amount[i]
    
    # Propagate changes up the tree
    while i > 0:
        i = (i - 1) >> 1  # Move to parent
        l = 2 * i + 1
        r = l + 1
        dw = min(amount[l], strength[r])
        wine[i] = wine[l] + wine[r] + dw
        db = min(strength[r] - dw, throughput[l])
        strength[i] = strength[l] + db
        da = min(amount[l] - dw, throughput[r])
        amount[i] = amount[r] + da
        throughput[i] = min(throughput[l] - db, throughput[r] - da)
    print(wine[0])


# https://github.com/VaHiX/CodeForces/