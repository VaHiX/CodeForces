# Problem: CF 1690 F - Shifting String
# https://codeforces.com/contest/1690/problem/F

import math

l = lambda: map(lambda x: int(x) - 1, input().split())


def f(s):
    # Function to find the smallest positive integer i such that shifting s by i positions 
    # results in the same string (i.e., the length of the repeating cycle)
    for i in range(1, len(s) + 1):
        if s == s[i:] + s[:i]:
            return i
    return len(s)  # fallback, though problem guarantees a cycle exists


for t in range(int(input())):
    n = int(input())
    s = input()
    p = [*l()]  # Convert permutation to 0-indexed
    v = [True] * n  # Visited array to track which indices have been processed
    z, i = 1, 0  # z holds the LCM of cycle lengths, i is the current index in permutation
    
    while i < n:
        w = ""  # String representing a cycle in the permutation
        while v[i]:  # Traverse until we see a visited node (cycle completion)
            w += s[i]
            v[i] = False  # Mark current index as visited
            i = p[i]  # Move to next index according to permutation
        i += 1  # Move to next unvisited index
        if len(w) == 0:
            continue  # Skip empty cycles (shouldn't happen, but safeguard)
        r = f(w)  # Find cycle length of the substring w
        z *= r // math.gcd(z, r)  # Update LCM of all cycle lengths
    
    print(z)


# https://github.com/VaHiX/CodeForces/