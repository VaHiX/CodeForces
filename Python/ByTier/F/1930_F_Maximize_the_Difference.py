# Problem: CF 1930 F - Maximize the Difference
# https://codeforces.com/contest/1930/problem/F

"""
Algorithm: Maximize the Difference
Purpose: For each query, append a value to an array and compute the maximum difference 
         between max and min elements in the array over all possible bitwise OR operations 
         with a non-negative integer x.
         
Time Complexity: O(q * u * log u) where u = 2^(bit_length(n))
Space Complexity: O(u) where u = 2^(bit_length(n))

Techniques:
- Bit manipulation and bitmasking
- BFS-like traversal on bits
- Preprocessing and tracking of seen states
"""

import sys

input = sys.stdin.readline

out = []

t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    l = list(map(int, input().split()))

    # Determine the bit length needed to represent n
    ul = n.bit_length()
    u = 1 << ul  # 2^ul
    ms = u - 1   # Mask to get all bits set

    # f0 and f1 track the states visited in two different iterations
    f0 = [0] * u
    f1 = [0] * u

    v = 0
    res = []
    ans = 0

    for i in range(q):
        # Decrypt v from encrypted input
        v += l[i]
        v %= n

        # First phase: Traverse all submasks of v and update ans based on f1
        st = [v]
        while st:
            u = st.pop()
            if f0[u]:
                continue

            if f1[u]:
                ans = max(ans, u)
            f0[u] = 1

            # For each bit, push the submask (v with that bit cleared)
            for b in range(ul):
                st.append(u & (~(1 << b)))

        # Set v to complement of v (masked to keep only up to ul bits)
        v ^= ms
        st = [v]
        while st:
            u = st.pop()
            if f1[u]:
                continue

            if f0[u]:
                ans = max(ans, u)
            f1[u] = 1

            # For each bit, push the submask (v with that bit cleared)
            for b in range(ul):
                st.append(u & (~(1 << b)))

        v = ans
        res.append(v)
    out.append(" ".join(map(str, res)))
print("\n".join(out))


# https://github.com/VaHiX/CodeForces/