# Problem: CF 1866 H - Happy Sets
# https://codeforces.com/contest/1866/problem/H

"""
Problem: Happy Sets
Task: Count the number of arrays of N sets, where each set contains integers from 1 to K,
      and the array can be rearranged such that each set is a "child" of the next one.
      A set A is a child of set B if for every x in A, there exists x+1 in B.

Algorithms/Techniques:
- Combinatorics and inclusion-exclusion principle
- Modular arithmetic for large numbers
- Precomputation of factorials
- Fast exponentiation for modular power

Time Complexity: O(N * log(mod)) due to modular exponentiation and loop
Space Complexity: O(N) for storing factorials and auxiliary variables

The solution uses the principle of inclusion-exclusion to count valid sequences
of sets where each set is a child of the next. It computes values using
factorial multiplications, modular exponentiations, and cumulative sums.
"""

from sys import stdin, stdout

inp = lambda: int(input())
strng = lambda: input().strip()
jn = lambda x, l: x.join(map(str, l))
strl = lambda: list(input().strip())
mul = lambda: map(int, input().strip().split())
mulf = lambda: map(float, input().strip().split())
seq = lambda: list(map(int, input().strip().split()))

ceil = lambda x: int(x) if (x == int(x)) else int(x) + 1
ceildiv = lambda x, d: x // d if (x % d == 0) else x // d + 1

flush = lambda: stdout.flush()
stdstr = lambda: stdin.readline()
stdint = lambda: int(stdin.readline())
stdpr = lambda x: stdout.write(str(x))

mod = 998244353


def main():
    [n, h] = seq()  # n is number of sets, h is max value in sets
    tot = 0         # total result
    fac = [1]       # precompute factorials
    prod = 1        # running product for combinations
    
    # Precompute factorials modulo mod
    for i in range(n):
        fac.append((fac[-1] * (i + 1)) % mod)

    # Iterate through all possible number of distinct values (w)
    for w in range(n + 1):
        if w > h:
            continue  # Skip if w exceeds the maximum element h

        # Apply inclusion-exclusion: 
        # (w+1)^(h-w+1) - w^(h-w+1) gives the count of mappings from h elements to w+1 values
        # such that all values from 1 to h are mapped to at least 1 of the w+1 values.
        val = fac[w] * (pow(w + 1, h - w + 1, mod) - pow(w, h - w + 1, mod))

        tot += (val * prod) % mod  # Accumulate contribution to total
        tot %= mod                 # Keep result modulo mod

        prod *= n - w              # Update product for next iteration
        prod %= mod                # Maintain modulo property

    print(tot)  # Print final result


main()


# https://github.com/VaHiX/CodeForces/