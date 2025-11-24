# Problem: CF 2160 F - Twin Polynomials
# https://codeforces.com/contest/2160/problem/F

"""
F. Twin Polynomials

Algorithms/Techniques:
- Dynamic Programming with Modular Arithmetic
- Graph-based constraint checking for valid polynomial mappings
- Preprocessing of base cases and derived values using recurrence relations

Time Complexity: O(MAXN + sum(n)) where MAXN = 400005, sum(n) is the total sum of n across all test cases.
Space Complexity: O(MAXN) for storing precomputed arrays S and Iinc.

This problem involves counting valid "cool" polynomials of degree n satisfying f(x) = g(x), 
where g(x) is the twin polynomial. The approach uses dynamic programming to compute base values,
then applies constraint propagation on the given partial assignments to determine how many valid
completions exist under the cool condition.
"""

MOD = 1_000_000_007


def addm(a, b):
    a += b
    if a >= MOD:
        a -= MOD
    return int(a)


def subm(a, b):
    a -= b
    if a < 0:
        a += MOD
    return int(a)


def mulm(a, b):
    return int((a * b) % MOD)


def main():
    import sys

    input = sys.stdin.readline
    MAXN = 400000 + 5
    S = [0] * MAXN          # S[i] represents number of cool polynomials of degree i
    Iinc = [0] * MAXN       # Iinc[i] represents a derived value used for calculation
    S[0] = 1                # Base case for S[0]
    S[1] = 2                # Base case for S[1]
    for i in range(2, MAXN):
        # Recurrence relation for computing S[i]
        S[i] = addm(addm(S[i - 1], S[i - 1]), mulm(i - 1, S[i - 2]))
    Iinc[0] = 0             # Base case for Iinc[0]
    Iinc[1] = 1             # Base case for Iinc[1]
    for i in range(2, MAXN):
        # Derive Iinc[i] from S
        Iinc[i] = subm(S[i], S[i - 1])
    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        a = list(map(int, input().split()))
        bad = False
        # Check if any given value is out of valid range (0 to n)
        for i in range(1, n + 1):
            if a[i] != -1 and not (0 <= a[i] <= n):
                bad = True
                break
        if bad:
            print(0)
            continue
        partner = [-1] * (n + 1)    # partner[i] stores j such that i is mapped to j
        excluded = [0] * (n + 1)    # excluded[i] indicates whether element i is explicitly excluded
        fixed1 = [0] * (n + 1)      # fixed1[i] indicates whether element i must be fixed to itself
        for i in range(1, n + 1):
            if bad:
                break
            if a[i] == -1:
                continue            # Skip undetermined entries
            if a[i] == 0:
                if fixed1[i] or partner[i] != -1:
                    bad = True      # Conflict in mapping
                    break
                excluded[i] = 1     # Mark node i as excluded
            elif a[i] == i:
                if excluded[i] or partner[i] != -1:
                    bad = True      # Conflict in mapping
                    break
                fixed1[i] = 1       # Mark node i as fixed to itself
            else:
                j = a[i]
                if excluded[j]:
                    bad = True      # Node j cannot be mapped and also excluded
                    break
                if a[j] != -1 and a[j] != i:
                    bad = True      # Conflict in bidirectional mapping
                    break
                if fixed1[j]:
                    bad = True      # Node j is already fixed
                    break
                if partner[i] != -1 and partner[i] != j:
                    bad = True      # Already mapped to different value
                    break
                if partner[j] != -1 and partner[j] != i:
                    bad = True      # Reverse mapping conflict
                    break
                partner[i] = j      # Set up bidirectional mapping
                partner[j] = i
        if bad:
            print(0)
            continue

        # Final check after all mappings
        for i in range(1, n + 1):
            if bad:
                break
            if excluded[i]:
                if partner[i] != -1 or fixed1[i]:
                    bad = True  # Conflicting exclusion with mapping or fixing
                    break
        if bad:
            print(0)
            continue
        if excluded[n]:
            print(0)
            continue
        for i in range(1, n + 1):
            if bad:
                break
            if partner[i] != -1:
                j = partner[i]
                if j < 1 or j > n or partner[j] != i:
                    bad = True  # Invalid mapping or mismatch
                    break
                if i == j and not fixed1[i]:
                    bad = True  # Self-mapping without being fixed is invalid
                    break
        if bad:
            print(0)
            continue
        used = [0] * (n + 1)
        for i in range(1, n + 1):
            if excluded[i] or fixed1[i] or partner[i] != -1:
                used[i] = 1  # Mark as already assigned to avoid double counting
        m = sum(1 for i in range(1, n + 1) if not used[i])
        ans = Iinc[m] if not used[n] else S[m]
        print(ans % MOD)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/