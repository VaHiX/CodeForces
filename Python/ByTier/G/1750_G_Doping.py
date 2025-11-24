# Problem: CF 1750 G - Doping
# https://codeforces.com/contest/1750/problem/G

def solve():
    """
    Reads two integers (size, mod) and then a permutation of [1..size].
    Prints 'size' integers computed under modulus 'mod'.
    
    Algorithm:
    - Uses dynamic programming with combinatorics to count valid permutations.
    - Calculates combinations using Pascal's triangle.
    - Tracks remaining elements and their adjacency to determine f(p') values.
    - Accumulates results in a bottom-up manner to compute final output.
    
    Time Complexity: O(n^3)
    Space Complexity: O(n^2)
    """
    import sys

    data = sys.stdin.read().split()
    size, mod = int(data[0]), int(data[1])
    perm = [int(x) - 1 for x in data[2:]]

    def modmul(a, b, c=0):
        return (a * b + c) % mod

    # Precompute combinations using Pascal's triangle
    comb = [[1]]
    for r in range(2010):
        prev = comb[-1]
        row = [1]
        for c in range(r):
            row.append((prev[c] + prev[c + 1]) % mod)
        row.append(1)
        comb.append(row)

    # Precompute factorials
    fact = [1]
    for i in range(1, 3000):
        fact.append((fact[-1] * i) % mod)

    # Track remaining elements and pair count
    rem = [1] * size
    pair_count = size - 1
    base = 0
    out = [[0] * (size + 1) for _ in range(size + 1)]

    # Process permutation elements one by one
    for step in range(size):
        # Count different adjacent configurations
        diff, spec = [0] * 3, [0] * 3
        for pos in range(perm[step]):
            if rem[pos] == 0:
                continue
            adj = 0
            if pos > 0 and rem[pos - 1]:
                adj += 1
            if step > 0 and pos == perm[step - 1] + 1:
                spec[adj] += 1
            else:
                diff[adj] += 1
        # Update output based on current configuration
        for adj in range(3):
            pl = pair_count - adj
            if pl < 0 or (diff[adj] + spec[adj]) == 0:
                continue
            remain = size - step - 1
            for sq in range(pl + 1):
                w = comb[pl][sq]
                order = remain - sq
                if order < 0:
                    continue
                cost = modmul(w, fact[order])
                out[base][sq] += modmul(cost, diff[adj] + spec[adj])
                out[base][sq] %= mod
                if spec[adj]:
                    out[base][sq + 1] += cost
                    out[base][sq + 1] %= mod
        rem[perm[step]] = 0
        # Adjust pair count based on neighbors being removed
        if perm[step] > 0 and rem[perm[step] - 1]:
            pair_count -= 1
        if perm[step] < size - 1 and rem[perm[step] + 1]:
            pair_count -= 1
        if step > 0 and perm[step] == perm[step - 1] + 1:
            base += 1

    # Accumulate results bottom-up
    while len(out) > 1:
        bot = out.pop()
        for i in range(size):
            out[-1][i] += bot[i]
            out[-1][i] %= mod
            if i > 0:
                out[-1][i] += bot[i - 1]
                out[-1][i] %= mod

    fr = out[0]
    res = []
    # Convert accumulated result to final answer
    for i in range(size):
        val = fr[size - 1 - i]
        for j in range(i):
            val -= modmul(res[j], comb[size - j - 1][size - i - 1])
            val %= mod
        res.append(val % mod)

    print(" ".join(map(str, res)))


solve()


# https://github.com/VaHiX/CodeForces/