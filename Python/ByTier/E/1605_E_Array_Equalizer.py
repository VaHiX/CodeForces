# Problem: CF 1605 E - Array Equalizer
# https://codeforces.com/contest/1605/problem/E

"""
Problem: Array Equalizer
Algorithm: Mathematical optimization with prefix sums and slope optimization
Time Complexity: O(n log n + q log q) where n is array size and q is number of queries
Space Complexity: O(n + q)

This solution uses a mathematical approach to determine the minimum operations needed
to transform array 'a' into array 'b' where b[0] is unknown. The key insight is that
each operation affects multiples of an index, which creates a pattern that can be
optimized using prefix sums and slope optimization techniques.

The solution tracks the "offset" of operations needed at each position and uses
a sorted list of queries to efficiently compute results.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]


from math import gcd


class Fraction:
    def __init__(self, num, den=1):
        if type(num) == float or type(num) == str:
            assert den == 1
            if type(num) == float:
                S = str("{:.10f}".format(num))
            else:
                S = num
            N = len(S)
            point = -1
            for i in range(N):
                if S[i] == ".":
                    point = i
            if point != -1:
                F = Fraction(int(S[:point] + S[point + 1 :]), 10 ** (N - 1 - point))
            else:
                F = Fraction(int(S), 1)
            self.num = F.num
            self.den = F.den
        elif type(num) == type(den) == int:
            inf = 10**9
            if den == 0:
                if num > 0:
                    self.num = inf
                    self.den = 1
                elif num < 0:
                    self.num = -inf
                    self.den = 1
                else:
                    raise Exception
                return
            den, num = max((den, num), (-den, -num))
            g = gcd(den, num)
            self.num = num // g
            self.den = den // g
        else:
            raise Exception

    def __str__(self):
        return str(self.num) + "/" + str(self.den)

    def __pos__(self):
        return self

    def __neg__(self):
        num, den = self.num, self.den
        return Fraction(-num, den)

    def __add__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return Fraction(num1 * den2 + num2 * den1, den1 * den2)

    def __sub__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return Fraction(num1 * den2 - num2 * den1, den1 * den2)

    def __mul__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return Fraction(num1 * num2, den1 * den2)

    def __truediv__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return Fraction(num1 * den2, num2 * den1)

    def __pow__(self, x):
        assert type(x) == int
        num, den = self.num, self.den
        if x >= 0:
            return Fraction(num**x, den**x)
        else:
            return Fraction(den ** (-x), num ** (-x))

    __radd__ = __add__

    def __rsub__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = other.num, other.den
        num2, den2 = self.num, self.den
        return Fraction(num1 * den2 - num2 * den1, den1 * den2)

    __rmul__ = __mul__

    def __rtruediv__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = other.num, other.den
        num2, den2 = self.num, self.den
        return Fraction(num1 * den2, num2 * den1)

    def __eq__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return num1 == num2 and den1 == den2

    def __lt__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return num1 * den2 < num2 * den1

    def __le__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return num1 * den2 <= num2 * den1

    def __gt__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return num1 * den2 > num2 * den1

    def __ge__(self, other):
        if type(other) != Fraction:
            other = Fraction(other)
        num1, den1 = self.num, self.den
        num2, den2 = other.num, other.den
        return num1 * den2 >= num2 * den1

    def floor(self):
        return self.num // self.den


n = int(input())
a = list(map(int, input().split()))
b0 = list(map(int, input().split()))
b0[0] = 0  # Set b[0] to 0 for calculation
b1 = [1] + [0] * (n - 1)  # Represents the coefficient for the first element

off = 0  # Base offset that doesn't depend on b[0]
query = []  # List to store transformation queries

res1 = 0  # Running sum for slope optimization
res2 = 0  # Running sum for constant optimization
for i in range(1, n + 1):
    c0 = a[i - 1] - b0[i - 1]  # Difference at position i
    c1 = -b1[i - 1]  # Coefficient for b[0] effect
    if c1 == 0:
        # If coefficient is 0, no dependency on b[0]
        off += abs(c0)
    else:
        # Store query with slope information for optimization
        p, q = max((c1, c0), (-c1, -c0))
        query.append((-1, p, q, -c0 / c1))  # (-1 indicates base operation, p=coefficient, q=constant, threshold)
        res1 -= p
        res2 -= q
    # Propagate the effect to multiples of i
    for j in range(2 * i, n + 1, i):
        b0[j - 1] += c0
        b1[j - 1] += c1

q = int(input())
# Read queries
for i in range(q):
    x = int(input())
    query.append((i, x, -1, x))  # (query_index, b[0] value, ignored, sort_key)

# Sort queries by threshold value (where slope changes)
query.sort(key=lambda x: x[3])
ans = [off] * q  # Initialize answer array with base offset

# Process all queries 
for t, x, y, _ in query:
    if t == -1:
        # Process base transformation operations
        res1 += 2 * x
        res2 += 2 * y
    else:
        # Compute result for query t
        ans[t] += x * res1 + res2

print(*ans, sep="\n")


# https://github.com/VaHiX/CodeForces/