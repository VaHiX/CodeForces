# Problem: CF 1938 D - Bánh Bò
# https://codeforces.com/contest/1938/problem/D

"""
Code Purpose:
This program calculates the number of uniform bánh bò hấp assemblies for a given grid of size r x c,
where r is a multiple of 6 and c is a multiple of 7. A uniform assembly means all 6x7 subgrids have
the same number of red and white pieces.

Algorithms/Techniques:
- Dynamic Programming with bitmasking to handle state transitions
- Modular exponentiation and combinatorics for computing coefficients
- Precomputation of row and column combinations
- Enumerating valid configurations using state transitions and bitmasking

Time Complexity: O(r * c * 7 * 8 * 7 * 7)
Space Complexity: O(7 * 7 * 8)
"""

def comb(a, b):
    # Compute combination C(a, b) using recursion (not optimized for large inputs)
    if a == b or b == 0:
        return 1
    return (a * comb(a - 1, b - 1)) // b


MOD = 998244353

# Read input
r, c = map(int, input().split())


# Precompute row transition coefficients
# For each number of red pieces in a 6x7 grid (up to 7), compute sum of (C(6, j))^r//6
rm = [sum(pow(comb(i, j), r // 6, MOD) for j in range(i + 1)) for i in range(8)]

# Precompute column transition coefficients
# For each number of red pieces in a 6x7 grid (up to 6), compute sum of (C(7, j))^c//7
cm = [sum(pow(comb(i, j), c // 7, MOD) for j in range(i + 1)) for i in range(7)]

# Mask for bitmask operations
MASK = pow(7, 7)

# State vector to hold transitions
state = [0] * MASK * 8
state[0] = 1

# Process rows one at a time (6 rows per group)
for rr in range(6):
    # Process each column for current row
    for cc in range(7):
        ns = [0] * MASK * 8  # New state

        # Bait value for moving bits
        bait = pow(7, cc)

        # Transition logic: update next state based on current state
        for u in range(cc + 1):
            for v in range(MASK - bait):
                ind = u * MASK + v

                # Apply transitions: adjust states accordingly
                ns[ind] -= 2 * state[ind]  # Subtract twice current value
                ns[ind + MASK] += state[ind]  # Move to next row level
                ns[ind + bait] += state[ind]  # Move to next column level

        # Update state with new values
        state = [v % MOD for v in ns]

    # Update final state using row coefficients
    ns = [0] * MASK * 8
    for u in range(8):
        for v in range(MASK):
            ind = u * MASK + v
            ns[v] += state[ind] * rm[u]  # Multiply with row coefficient
            ns[v] %= MOD

    state = ns

# Final computation: accumulate result
out = 0

# Track column configurations using array z
z = [0] * 8
for i in range(MASK):
    add = state[i]  # Current state value

    # Multiply by column coefficients for each column position
    for i in range(7):
        add = (add * cm[z[i]]) % MOD

    out += add

    # Increment z (simulate bit traversal for column patterns)
    z[0] += 1
    for i in range(7):
        if z[i] == 7:
            z[i] = 0
            z[i + 1] += 1
        else:
            break

# Print result modulo 998244353
print(out % MOD)


# https://github.com/VaHiX/CodeForces/