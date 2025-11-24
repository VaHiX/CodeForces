# Problem: CF 1709 D - Rorororobot
# https://codeforces.com/contest/1709/problem/D

"""
Algorithm: Range Maximum Query (RMQ) with Sparse Table
Techniques: Binary lifting, preprocessing for range queries, simulation of robot movement with k-step commands

Time Complexity: 
- Preprocessing: O(m * log m)
- Each query: O(log m)
- Overall: O(m * log m + q * log m)

Space Complexity: 
- O(m * log m) for sparse table
- Overall: O(m * log m)

The solution uses a sparse table to preprocess maximum blocked heights in ranges,
then for each query, checks if it's possible to reach from start to finish
with k-step commands, considering blocked cells and movement constraints.
"""

def li():
    return [int(i) for i in input().split()]


from math import log2

n, m = li()
t = li()
e = int(log2(m))
sp = [[t[i] + 1] + [0] * (e) for i in range(m)]
for i in range(1, e + 1):
    for j in range(m - (1 << i) + 1):
        sp[j][i] = max(sp[j][i - 1], sp[j + (1 << (i - 1))][i - 1])

for _ in range(li()[0]):
    a, b, x, y, k = li()
    b, y = sorted([b, y]) # Ensure b <= y for easier range processing
    if abs(a - x) % k or abs(b - y) % k: # Check if distances are divisible by k
        print("NO")
        continue
    e = abs(b - y) + 1 # Length of the range [b, y]
    f = int(log2(e)) # Precompute log2 for binary lifting
    a += ((n - a) // k) * k # Adjust start row to make it reachable in k steps
    # Find maximum blocked height in range [b-1, b-1+e%2^f] using sparse table
    ma = max(sp[b - 1][f], sp[b - 1 + e % 2**f][f])

    if ma <= a:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/