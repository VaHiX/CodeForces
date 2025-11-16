# Problem: CF 2095 E - Pair Count
# https://codeforces.com/contest/2095/problem/E

"""
E. Pair Count

Given a prime number p, n integers a_1, a_2, ..., a_n, and an integer k,
find the number of pairs of indices (i,j) such that:
(a_i XOR a_j)(a_i^2 XOR a_j^2) ≡ k (mod p)

This solution uses modular exponentiation and frequency counting to compute the result efficiently.

Algorithms/Techniques:
- Modular Exponentiation (Fast Exponentiation)
- Hash Map (Counter) for frequency counting
- Mathematical manipulation using Fermat's Little Theorem to compute modular inverse

Time Complexity: O(n * log(p) + n)
Space Complexity: O(n)

"""
from collections import Counter

n, p, k = map(int, input().split(" "))
a = list(map(int, input().split(" ")))
a.sort()

def mexp(b, pw):
    # Fast modular exponentiation
    r = 1
    while pw:
        if pw & 1:
            r = (r * b) % p
        b = (b * b) % p
        pw >>= 1
    return r

# Transform all elements to their cube mod p
a = [mexp(e, 3) for e in a]
b = Counter(a)  # Count frequencies of transformed values
c = 0

for e in a:
    if e == 0:
        continue
    # Compute u = k * e^(-1) mod p using Fermat's little theorem: e^(-1) ≡ e^(p-2) mod p
    u = (k * mexp(e, p - 2)) % p
    c += b[u]  # Add count of elements equal to u
    if u == e:
        c -= 1  # Avoid counting the pair (i,i) which is not allowed

# Special case handling for zero: if a[0] = 0 and k = 0, all pairs with index 0 contribute
if a[0] == 0 and k == 0:
    c += n - 1

print(c // 2)  # Each valid pair counted twice in the loop


# https://github.com/VaHiX/codeForces/