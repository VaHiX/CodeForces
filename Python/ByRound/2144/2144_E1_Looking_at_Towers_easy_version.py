# Problem: CF 2144 E1 - Looking at Towers (easy version)
# https://codeforces.com/contest/2144/problem/E1

"""
Problem: Count subsequences where the left and right visible towers (L and R sets) match the original array.

Approach:
- Transform input to compressed indices for easier handling.
- For each element in order of increasing value, compute contribution to valid subsequences using Fenwick Tree for prefix sums.
- Use dynamic programming for forward and backward passes.
- Combine results with generating function techniques to handle overlapping subproblems.

Time Complexity: O(n^2 * log n) where n is length of array
Space Complexity: O(n)

Algorithms:
- Coordinate compression
- Fenwick Tree / Binary Indexed Tree
- Dynamic Programming
- Prefix Sums and Generating Functions

"""

MOD = 998244353
MAX = 200003
inv2 = pow(2, -1, MOD)  # Modular inverse of 2
p2 = [1] * MAX          # Powers of 2 mod MOD
for i in range(1, MAX):
    p2[i] = p2[i - 1] * 2 % MOD

for _ in range(int(input())):
    n = int(input())
    a = [int(t) for t in input().split()]
    
    # Coordinate compression step
    L = 0
    free = 0
    comp = {}
    for e in sorted(a):
        if e == L:
            continue
        L = e
        comp[e] = free
        free += 1
    a = [comp[e] for e in a]  # Compress original array

    def solve(a):
        front = []      # List of unique values in increasing order
        M = -1          # Max value so far
        for e in a:
            if e > M:
                front.append(e)
                M = e
        
        # Group positions by value
        spots = [[] for _ in range(n)]
        for i, e in enumerate(a):
            spots[e].append(i)
            
        fen = [0] * (n + 1)  # Fenwick Tree for maintaining prefix counts

        def update(i, x):
            """Add x to position i in Fenwick tree."""
            while i <= n:
                fen[i] += x
                i += i & (-i)

        def partial(i):
            """Get sum from index 1 to i in Fenwick tree."""
            S = 0
            while i:
                S += fen[i]
                i -= i & (-i)
            return S

        v = [0] * n     # v[i]: number of valid subsequences ending at index i
        for i in range(front[0]):   # Initialize all indexes that do not affect visibility from left side
            for e in spots[i]:
                update(1 + e, +1)  # Mark these as processed
        
        # Process each transition level from front to next higher value
        for i in range(len(front) - 1):
            h = front[i]
            H = front[i + 1]
            inds = spots[h]
            
            if i == 0:  # First group, initialize all elements as having one subsequence
                for e in inds:
                    v[e] = 1
                    
            # Process transitions within same level
            for j in range(1, len(inds)):
                L = inds[j - 1]
                R = inds[j]
                # Multiply by probability of not having seen previous values yet
                v[R] += v[L] * p2[1 + partial(R) - partial(L)]
                v[R] %= MOD
                
            last = spots[h]
            inds = spots[H]
            
            # Handle transitions from lower to higher value level
            t = 0
            for R in inds:
                if R < last[t]:
                    continue
                while t + 1 < len(last) and last[t + 1] < R:
                    t += 1
                L = last[t]
                # Multiply by transition probability from Fenwick Tree
                v[R] = v[L] * p2[partial(R) - partial(L + 1)] % MOD
                
            # Mark all positions up to current level processed in Fenwick tree for future use
            for t in range(h, H):
                for e in spots[t]:
                    update(1 + e, +1)

        if len(front) == 1:
            # Special case for single unique value
            for e in spots[front[0]]:
                v[e] = 1
                
        # Only those which are part of final visible element should retain value
        for i in range(n):
            if a[i] != M:
                v[i] = 0
                
        return v

    L = solve(a)            # Forward pass: compute valid subsequences ending before last visible element
    R = solve(a[::-1])[::-1] # Backward pass: reverse array and solve same way then reverse result
    
    S = sum(L[i] * R[i] for i in range(n))  # Combine forward and backward passes
    
    T = 0
    t = inv2   # Initialize with inverse of 2 (used in geometric series)
    for i in range(n):
        S += R[i] * T * p2[i]
        T += t * L[i]
        t = t * inv2 % MOD  # Move along the geometric progression

    print(S % MOD)  # Output final result modulo given constant


# https://github.com/VaHiX/codeForces/