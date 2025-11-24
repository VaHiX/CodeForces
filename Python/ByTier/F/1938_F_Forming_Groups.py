# Problem: CF 1938 F - Forming Groups
# https://codeforces.com/contest/1938/problem/F

"""
Algorithm: Group Formation for Hackathon
Techniques: Segment Tree, Prime Factorization, Greedy Optimization

Time Complexity: O(n * sqrt(n) + n * log(n)) per test case
Space Complexity: O(n * sqrt(n)) 

This code solves the problem of optimally grouping students based on their skill levels 
and finding the minimum ratio of maximum to minimum group skill levels. It uses:
1. Prime factorization to find all valid group counts (divisors of n > 1)
2. Segment trees to efficiently calculate group sums and update them when captain moves
3. Greedy optimization to find the best position and group count
"""

import sys

input = lambda: sys.stdin.readline().strip()

# Sieve of Eratosthenes to find primes up to 10^6
is_prime = [1 for i in range(10**6 + 1)]
for p in range(2, 10**6 + 1):
    if is_prime[p] == 0:
        continue
    for q in range(p, 10**6 + 1):
        if p * q > 10**6:
            break
        is_prime[p * q] = 0


# Segment Tree Implementation for efficient range operations
class segtree:
    n = 1
    size = 1
    log = 2
    d = [0]
    op = None
    e = 10**15

    def __init__(self, V, OP, E):
        self.n = len(V)
        self.op = OP
        self.e = E
        self.log = (self.n - 1).bit_length()
        self.size = 1 << self.log
        self.d = [E for i in range(2 * self.size)]
        for i in range(self.n):
            self.d[self.size + i] = V[i]
        for i in range(self.size - 1, 0, -1):
            self.update(i)

    def set(self, p, x):
        assert 0 <= p and p < self.n
        p += self.size
        self.d[p] = x
        for i in range(1, self.log + 1):
            self.update(p >> i)

    def add(self, p, x):
        y = x + self.get(p)
        self.set(p, y)

    def get(self, p):
        assert 0 <= p and p < self.n
        return self.d[p + self.size]

    def prod(self, l, r):
        assert 0 <= l and l <= r and r <= self.n
        sml = self.e
        smr = self.e
        l += self.size
        r += self.size
        while l < r:
            if l & 1:
                sml = self.op(sml, self.d[l])
                l += 1
            if r & 1:
                smr = self.op(self.d[r - 1], smr)
                r -= 1
            l >>= 1
            r >>= 1
        return self.op(sml, smr)

    def all_prod(self):
        return self.d[1]

    def max_right(self, l, f):
        assert 0 <= l and l <= self.n
        assert f(self.e)
        if l == self.n:
            return self.n
        l += self.size
        sm = self.e
        while 1:
            while l % 2 == 0:
                l >>= 1
            if not (f(self.op(sm, self.d[l]))):
                while l < self.size:
                    l = 2 * l
                    if f(self.op(sm, self.d[l])):
                        sm = self.op(sm, self.d[l])
                        l += 1
                return l - self.size
            sm = self.op(sm, self.d[l])
            l += 1
            if (l & -l) == l:
                break
        return self.n

    def min_left(self, r, f):
        assert 0 <= r and r <= self.n
        assert f(self.e)
        if r == 0:
            return 0
        r += self.size
        sm = self.e
        while 1:
            r -= 1
            while r > 1 and (r % 2):
                r >>= 1
            if not (f(self.op(self.d[r], sm))):
                while r < self.size:
                    r = 2 * r + 1
                    if f(self.op(self.d[r], sm)):
                        sm = self.op(self.d[r], sm)
                        r -= 1
                return r + 1 - self.size
            sm = self.op(self.d[r], sm)
            if (r & -r) == r:
                break
        return 0

    def update(self, k):
        self.d[k] = self.op(self.d[2 * k], self.d[2 * k + 1])

    def __str__(self):
        return str([self.get(i) for i in range(self.n)])


# Greatest Common Divisor function
def gcd(a, b):
    while a != 0:
        b %= a
        if b == 0:
            return a
        a %= b
    return b


def solve():
    n, x = map(int, input().split())
    A = list(map(int, input().split()))
    A = [x] + A  # Insert captain's skill at the beginning
    
    # Precompute prefix sums
    R = [0]
    for i in range(n):
        r = R[-1] + A[i]
        R.append(r)
    
    # Find all divisors of n greater than 1 (valid group counts)
    D = []
    for k in range(2, n + 1):
        if is_prime[k] == 1 and n % k == 0:  # Only consider primes that divide n
            D.append(k)

    m = len(D)
    
    # Initialize segment trees for max and min operations on each group size
    S = [segtree([0 for j in range(D[i])], max, 0) for i in range(m)]
    s = [segtree([0 for j in range(D[i])], min, 10**18) for i in range(m)]

    p = 1  # Best maximum group sum
    q = 0  # Best minimum group sum
    
    # Try all possible group sizes and initial positions (before captain moves)
    for j in range(m):
        k = D[j]
        l = n // k  # Number of elements per group
        for i in range(n):
            a = A[i]  # Current element's skill
            S[j].add(i % k, a)  # Add to segment tree for max
            s[j].add(i % k, a)  # Add to segment tree for min
        a, b = S[j].all_prod(), s[j].all_prod()  # Get max and min group sums
        if p * b > a * q:  # If current ratio is better than previous
            p, q = a, b

    # Try all possible positions for the captain to move to
    for i in range(1, n):
        for j in range(m):
            k = D[j]
            l = (i - 1) % k  # Position before the captain
            ll = i % k       # Position after the captain
            a = A[i]
            # Adjust the two segments affected by captain's movement
            S[j].add(l, a - x)  # Remove old value from left group
            S[j].add(ll, x - a)  # Add new value to right group
            s[j].add(l, a - x)  # Remove old value from left group  
            s[j].add(ll, x - a)  # Add new value to right group
            a, b = S[j].all_prod(), s[j].all_prod()  # Get new max and min
            if p * b > a * q:  # If current ratio is better than previous
                p, q = a, b

    g = gcd(p, q)  # Simplify fraction
    p //= g
    q //= g
    print(p, q)
    return


# Main execution
t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/