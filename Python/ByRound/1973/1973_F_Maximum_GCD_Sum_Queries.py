# Problem: CF 1973 F - Maximum GCD Sum Queries
# https://codeforces.com/contest/1973/problem/F

"""
Algorithm: Maximum GCD Sum Queries
Purpose: Given arrays a, b, and costs c, find the maximum possible GCD sum of a and b after at most d coins of swapping.
Approach:
    - Preprocess primes and divisors for optimization
    - Use bitmasking and dynamic programming concepts to calculate all valid pairs
    - Use two passes (forward and backward) to compute optimal cost-score pairs
    - Binary search for query answers using precomputed results
    
Time Complexity: O(n * sqrt(max_val) + q * log(q))
Space Complexity: O(n * sqrt(max_val))

Where max_val is the maximum element in arrays a and b.
"""

from bisect import bisect_right
from collections import defaultdict
from itertools import product
from math import gcd, lcm
from sys import stdin


def get_primes(val):
    result = []
    p = 2
    while p * p <= val:
        if val % p == 0:
            result.append(p)
            while val % p == 0:
                val //= p
        p += 1
    if val > 1:
        result.append(val)
    return result


def div_cnt(val, primes):
    res = 1
    for p in primes:
        if val == 1:
            break
        cnt = 1
        while val % p == 0:
            cnt += 1
            val //= p
        res *= cnt
    return res


def get_divisors(val, primes):
    res = [1]
    for p in primes:
        if val % p != 0:
            continue
        curr = res.copy()
        mul = 1
        while val % p == 0:
            val //= p
            mul *= p
            res.extend(d * mul for d in curr)
    return sorted(res, reverse=True)


n, q = map(int, stdin.readline().split())
a = list(map(int, stdin.readline().split()))
b = list(map(int, stdin.readline().split()))
c = list(map(int, stdin.readline().split()))
d = list(map(int, stdin.readline().split()))

# Reduce numbers to their common factors to simplify computation
mask = gcd(*(lcm(x, y) for x, y in zip(a, b)))
a = [gcd(val, mask) for val in a]
b = [gcd(val, mask) for val in b]
primes = sorted(set(get_primes(a[0]) + get_primes(b[0])))
items = defaultdict(int)
for x, y, cost in zip(a, b, c):
    items[x << 30 | y] += cost
second_mask = (1 << 30) - 1
del a, b, c
pair_cnt, chosen_pair = min(
    (div_cnt(pair >> 30, primes) * div_cnt(second_mask & second_mask, primes), pair)
    for pair in items
)
chosen_cost = items.pop(chosen_pair)
a_val, b_val = chosen_pair >> 30, chosen_pair & second_mask

# Get divisors of chosen pair values
a_primes = [p for p in primes if a_val % p == 0]
a_divisors = get_divisors(a_val, a_primes)
b_primes = [p for p in primes if b_val % p == 0]
b_divisors = get_divisors(b_val, b_primes)


def calc_options(flip=False):
    # Create dictionary to store count and cost for each pair
    count_and_cost = {x << 30 | y: 0 for x, y in product(a_divisors, b_divisors)}

    for pair, flip_cost in items.items():
        x, y = pair >> 30, pair & second_mask
        # Forward and backward GCD computations
        fwd = gcd(x, a_val) << 30 | gcd(y, b_val)
        back = gcd(y, a_val) << 30 | gcd(x, b_val)
        if fwd == back:
            count_and_cost[fwd] += 1
        else:
            # Compute fork (middle point) and update costs accordingly
            fork = gcd(fwd >> 30, back >> 30) << 30 | gcd(
                fwd & second_mask, back & second_mask
            )
            count_and_cost[fwd] += 1 + (flip_cost << 20) * flip
            count_and_cost[back] += 1 + (flip_cost << 20) * (1 - flip)
            count_and_cost[fork] -= 1 + (flip_cost << 20)

    # Propagate counts for a_div and b_div
    for p in a_primes:
        for a_div in a_divisors:
            if a_div % p != 0:
                continue
            a_div_div_p = a_div // p
            for b_div in b_divisors:
                count_and_cost[a_div_div_p << 30 | b_div] += count_and_cost[
                    a_div << 30 | b_div
                ]
    for p in b_primes:
        for b_div in b_divisors:
            if b_div % p != 0:
                continue
            b_div_div_p = b_div // p
            for a_div in a_divisors:
                count_and_cost[a_div << 30 | b_div_div_p] += count_and_cost[
                    a_div << 30 | b_div
                ]

    # Accumulate final options with cost and score
    options = {}
    cnt_mask = (1 << 20) - 1
    for pair, cost_cnt in count_and_cost.items():
        if cnt_mask & cost_cnt < len(items):
            continue
        assert cnt_mask & cost_cnt == len(items)
        score = (pair >> 30) + (pair & second_mask)
        cost = (cost_cnt >> 20) + chosen_cost * flip
        if score in options:
            options[score] = min(options[score], cost)
        else:
            options[score] = cost
    return options


options = calc_options()
for k, v in calc_options(True).items():
    if k in options:
        options[k] = min(options[k], v)
    else:
        options[k] = v
options = sorted((v, k) for k, v in options.items())
costs = []
scores = []
for cost, score in options:
    if not costs:
        costs.append(cost)
        scores.append(score)
    if score <= scores[-1]:
        continue
    if cost == costs[-1]:
        scores[-1] = score
    else:
        costs.append(cost)
        scores.append(score)

results = []
for query in d:
    i = bisect_right(costs, query)
    results.append(scores[i - 1])
print(*results)


# https://github.com/VaHiX/CodeForces/