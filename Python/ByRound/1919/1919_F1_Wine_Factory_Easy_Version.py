# Problem: CF 1919 F1 - Wine Factory (Easy Version)
# https://codeforces.com/contest/1919/problem/F1

"""
Algorithm/Technique: Segment Tree with Lazy Propagation Simulation

This code simulates a wine-making process through a chain of water towers, each with a wizard that can convert water to wine, and valves connecting consecutive towers with specified capacities.

The simulation uses a segment tree to efficiently track and update the state of water flow and wine conversion at each tower. Each node in the segment tree represents a segment of the towers and stores information about the amount of water, wizard strength, wine produced, and throughput capacity at that segment.

Time Complexity: O(n + q * log n)
Space Complexity: O(n)

The initial segment tree construction is O(n), and each query update is O(log n).
"""

from sys import stdin

n, q = map(int, stdin.readline().split())

amount = list(map(int, stdin.readline().split()))
strength = list(map(int, stdin.readline().split()))
throughput = list(map(int, stdin.readline().split()))
throughput.append(0) # Append 0 to make it size n for easier indexing in segment tree
wine = [0] * n
for i in range(n):
    w = min(amount[i], strength[i]) # Determine how much water is converted to wine at tower i
    amount[i] -= w # Reduce amount of water after wine conversion
    strength[i] -= w # Reduce wizard's remaining strength
    wine[i] += w # Add to wine produced at tower i
    amount[i] = min(amount[i], throughput[i]) # Water that flows to next tower
    throughput[i] -= amount[i] # Update remaining capacity of connection to next tower

# Build segment tree with size 2*n
n2 = 1
while n2 < n:
    n2 <<= 1 # Find next power of 2 to fit all elements

# Pad arrays to size n2 for segment tree storage
for l in [amount, strength, wine, throughput]:
    l.extend([0] * (n2 - n))
    l[0:0] = [0] * (n2 - 1)

# Build segment tree from bottom to top
for i in reversed(range(n2 - 1)):
    l = 2 * i + 1
    r = l + 1
    dw = min(amount[l], strength[r]) # Calculate how much water can flow from left to right
    wine[i] = wine[l] + wine[r] + dw
    db = min(strength[r] - dw, throughput[l]) # Calculate how much strength flows from right to left
    strength[i] = strength[l] + db
    da = min(amount[l] - dw, throughput[r]) # Calculate how much amount flows from left to right
    amount[i] = amount[r] + da
    throughput[i] = min(throughput[l] - db, throughput[r] - da) # Calculate min capacity for connection at current node

# Process queries
for query_id in range(q):
    p, a, b, c = map(int, stdin.readline().split())
    i = p + n2 - 2 # Map array index to segment tree's index
    w = min(a, b) # Water converted to wine at position p
    wine[i] = w # Update wine produced in segment tree
    amount[i] = min(a - w, c) # Update amount of water after conversion
    strength[i] = b - w # Update wizard's strength after wine conversion
    throughput[i] = c - amount[i] # Update throughput capacity

    while i > 0: # Propagate updates from current node up to root
        i = (i - 1) >> 1 # Move to parent node
        l = 2 * i + 1 # Left child
        r = l + 1 # Right child
        dw = min(amount[l], strength[r]) # Calculate water that flows from left to right
        wine[i] = wine[l] + wine[r] + dw # Update wine at current node
        db = min(strength[r] - dw, throughput[l]) # Update strength flow
        strength[i] = strength[l] + db # Update total strength at current node
        da = min(amount[l] - dw, throughput[r]) # Update amount that flows
        amount[i] = amount[r] + da # Update total amount at current node
        throughput[i] = min(throughput[l] - db, throughput[r] - da) # Update throughput at current node
    print(wine[0]) # Print total wine produced


# https://github.com/VaHiX/CodeForces/