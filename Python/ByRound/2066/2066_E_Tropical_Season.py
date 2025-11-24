# Problem: CF 2066 E - Tropical Season
# https://codeforces.com/contest/2066/problem/E

"""
E. Tropical Season
Purpose:
This code determines whether it's possible to identify which of n barrels contains a poisonous substance
with exactly 0.179 kg weight using only comparisons and pouring operations. The algorithm uses a 
segment tree data structure to maintain and query the necessary information about available weights.

Algorithms/Techniques:
- Segment Trees with lazy propagation for maintaining water levels in barrels
- Binary search techniques in the segment tree for finding left/right neighbors
- Weight manipulation via pouring between barrels without touching the poisoned barrel

Time Complexity: O(n log n + q log n) where n is the number of barrels and q is the number of queries.
Space Complexity: O(2^21) = O(1) since it's a fixed size segment tree structure.

The solution works by:
1. Maintaining two segment trees (stv and std) to track cumulative sums
2. Applying operations to simulate pouring and updating the trees
3. Using logic based on binary representation to determine if poisoned barrel can be identified
"""

def contains(n):
    n += 2**20
    while n > 0:
        yield n
        n //= 2


def between(a, b):
    b = min(b, 2**20 - 1)
    a += 2**20
    b += 2**20
    while a < b:
        if a % 2 == 1:
            yield a
        if b % 2 == 0:
            yield b
        a = (a + 1) // 2
        b = (b - 1) // 2
    if a == b:
        yield a


def getleft(st, v):
    lb = v + 2**20 - 1
    if st[lb + 1] > v:
        return v
    llb = 2**20
    while lb >= llb and st[lb] == 0:
        lb = (lb - 1) // 2
        llb //= 2
    if lb < llb:
        return 0
    while lb < 2**20:
        lb = 2 * lb + 1
        if st[lb] == 0:
            lb -= 1
    return lb - 2**20


def getright(st, v):
    ub = v + 2**20 + 1
    if st[ub - 1] > v:
        return v
    uub = 2**21
    while ub < uub and st[ub] == 0:
        ub = (ub + 1) // 2
        uub //= 2
    if ub == uub:
        return -1
    while ub < 2**20:
        ub *= 2
        if st[ub] == 0:
            ub += 1
    return ub - 2**20


n, q = map(int, input().split())
stv = [0] * (2**21)
std = [0] * (2**21)
a = [int(i) for i in input().split()]


def works():
    ptw = -1
    ntw = 0
    while ntw > ptw:
        ptw = ntw
        nntw = sum(stv[i] for i in between(0, ntw))  # Sum of values between 0 and ntw
        while nntw > ntw:
            ntw = nntw
            nntw = sum(stv[i] for i in between(0, ntw))  # Continue accumulating until no change
        nntw = sum(std[i] for i in between(0, ntw))  # Sum of std values
        ex = nntw - ntw
        if (
            ex < 2**20
            and stv[2**20 + ex] == ex
            and ntw == sum(stv[i] for i in between(0, ex - 1))  # Check if current state leads to identification
        ):
            nntw = ntw  # If so, backtrack
        ntw = nntw
    miss = stv[1] - ntw  # Compute difference from total
    if miss < 2**20 and stv[2**20 + miss] == miss:
        return "Yes"
    return "No"


for v in a:
    stv[v + 2**20] += v  # Initialize segment tree with original values
for i in range(2**20 - 1, 0, -1):
    stv[i] = stv[2 * i] + stv[2 * i + 1]  # Build segment tree

for v in a:
    d = getleft(stv, v)  # Compute nearest left neighbor
    for i in contains(v - d):  # Update std values based on differences
        std[i] += v

print(works())

for _ in range(q):
    s, b = input().split()
    b = int(b)
    if s == "+":
        r = b if stv[2**20 + b] > 0 else getright(stv, b)  # Find rightmost non-zero
        l = getleft(stv, b)
        for i in contains(b):  # Update stv based on new addition
            stv[i] += b
        for i in contains(0 if r == b else b - l):  # Add to std with computed offset
            std[i] += b
        if r > 0 and l < b and (r == b or stv[2**20 + r] == r):
            for i in contains(r - l):  # Subtraction logic for adjustment
                std[i] -= r
            for i in contains(r - b):
                std[i] += r
    else:
        r = getright(stv, b)  # Find rightmost position to pour from
        for i in contains(b):  # Update segment tree by removing value
            stv[i] -= b
        l = getleft(stv, b)
        for i in contains(0 if r == b else b - l):
            std[i] -= b
        if r > 0 and l < b and stv[2**20 + r] == r:
            for i in contains(r - b):
                std[i] -= r
            for i in contains(r - l):
                std[i] += r
    print(works())


# https://github.com/VaHiX/codeForces/