# Problem: CF 2150 E2 - Hidden Single (Version 2)
# https://codeforces.com/contest/2150/problem/E2

"""
E2. Hidden Single (Version 2)
Interactive problem to find the unique element in a hidden array of size 2n-1,
containing numbers from 1 to n, each appearing twice except one appearing once.
Uses binary search with query optimization.

Algorithms/Techniques:
- Binary search on the answer space
- Bit manipulation for bucketing indices
- Query reduction using set operations

Time Complexity: O(n * log n)
Space Complexity: O(n)

The approach uses a recursive binary search on possible values,
dividing indices into two buckets at each step based on bit representation.
For each query, we check if an element exists in one of the halves,
using that to narrow down the candidates.

"""

from random import randint, seed, shuffle

seed()


def ril():
    return map(int, input().split())


def query(x, inds):
    global queries
    queries += 1
    """
    # This is how you'd implement the actual query if not interactive
    global secret
    for i in inds:
        if secret[i-1] == x:
            return 1
    return 0
    """
    print("?", x, len(inds), *inds)
    r = int(input())
    if r == -1:
        exit(1)
    return r


def gen(n):
    global secret, ANS
    ANS = randint(1, n)
    secret = list(range(1, n + 1)) + list(range(1, n + 1))
    secret.remove(ANS)
    shuffle(secret)
    print(secret, ANS)


def setup(n):
    n2 = 2 * n - 1
    l = 0
    while n2:
        l += 1
        n2 >>= 1
    buckets = [[[], []] for _ in range(l)]
    for k in range(2 * n - 1):
        ok = k + 1
        for i in range(l):
            buckets[i][k & 1].append(ok)
            k >>= 1
    return buckets


def solve(inds, possible: set, start=True):
    # Base case: only one possible value left
    if len(possible) == 1:
        return possible.pop()
    
    # Shuffle indices for randomness
    shuffle(inds)
    ll = len(inds)
    
    # Split into two halves
    bs = [inds[: ll // 2], inds[ll // 2 :]]
    occ = [set(), set()]
    
    # For each candidate value, check which half it appears in
    for x in possible:
        for i in range(2):
            if query(x, bs[i]):
                occ[i].add(x)
            else:
                if i == 0:
                    occ[1].add(x)
                break
    
    # Find elements that appear in both halves (and update set accordingly)
    both = occ[0].intersection(occ[1])
    possible.difference_update(both)
    
    # If this is the start of recursion, decide which half to proceed with
    if start:
        for i in range(2):
            # If remaining count (excluding those found in both) is odd,
            # then unique element must be in the other half
            if (len(bs[i]) - len(both)) % 2 == 1:
                possible.difference_update(occ[1 - i])
                return solve(bs[i], possible, start=False)
        assert False
    else:
        # Continue recursion based on size
        return solve(inds, possible, start=False)


T = int(input())
qs = []
n = 10

N = 2 * n - 1
for _ in range(T):
    queries = 0
    n = int(input())
    possible = set(list(range(1, n + 1)))
    ans = solve(list(range(1, 2 * n)), possible)
    """
    # Alternative implementation that was commented out for performance reasons
    while len(possible) > 1:
        buckets = []
        l = list(range(1, 2*n))
        shuffle(l)
        buckets.append(l[:2*N//4])
        buckets.append(l[2*N//4:4*N//4])
        inds = sample(l, ceil(n*1.00))
        s = set(inds)
        inds2 = []
        for i in range(1, 2*n):
            if i not in s:
                inds2.append(i)
        print(len(inds), len(inds2))
        print(inds, inds2)
        drop = set()
        sz = len(possible)
        iters = 0
        cur = list(possible)
        shuffle(cur)
        for x in cur:
            if 4*iters > sz: break
            iters += 1
            cnt = 0
            miss = 0
            shuffle(buckets)
            for b in buckets:
                if query(x, b):
                    cnt += 1
                    if cnt >= 2:
                        drop.add(x)
                        break
                else:
                    miss += 1
                    if len(buckets) - miss < 2:
                        break
            inds2, inds = inds, inds2
            if query(x, inds) and query(x, inds2):
                drop.add(x)
        for x in drop:
            possible.remove(x)
        print(queries, len(possible))
        print(len(buckets))
    ans = possible.pop()
    """
    print("!", ans)



# https://github.com/VaHiX/CodeForces/