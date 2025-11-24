# Problem: CF 2030 G1 - The Destruction of the Universe (Easy Version)
# https://codeforces.com/contest/2030/problem/G1

"""
Algorithm: 
- The problem is to compute the sum of the minimum number of operations required to make all intervals in a subset intersect.
- The key idea is to use a sweeping line technique over the endpoints of intervals.
- For each interval [l, r], we consider both l (start) and r (end) as events.
- As we sweep from left to right, we track how many intervals have ended before current point and how many start after.
- For each gap between consecutive points, we calculate contribution to total score using combinatorics (C(n,k) and powers of 2).
- Use precomputed combinations and cumulative sums for efficiency.

Time Complexity: O(n^2) per test case due to nested loop in get_val function, but optimized with precomputation.
Space Complexity: O(n^2) for precomputing combination numbers and cumulative sums.
"""

MOD = 998244353


def build_c_nk(max_n):
    ar = [1]
    ars = [ar]
    for _ in range(1, max_n + 1):
        ar = [1] + [(ar[j] + ar[j + 1]) % MOD for j in range(len(ar) - 1)] + [1]
        ars.append(ar)
    return ars


def build_end_cumsums(ar):
    cumsums = [0] * (len(ar) + 1)
    for i in range(len(ar) - 1, -1, -1):
        cumsums[i] = (cumsums[i + 1] + ar[i]) % MOD
    return cumsums


def build_2_to_i(max_n):
    ar = [1]
    for _ in range(1, max_n + 1):
        ar.append((ar[-1] * 2) % MOD)
    return ar


C_NK = build_c_nk(5000 + 1)  # Precompute combinations C(n,k)
CUMSUMS = [build_end_cumsums(ar) for ar in C_NK]  # Precompute backward cumulative sums
TWO_TO_I = build_2_to_i(5000 + 1)  # Precompute powers of 2


def m(a, b):
    return (a * b) % MOD  # Modular multiplication


def get_val(ends_before, starts_after, diff, n, strict=1):
    sum_answer = 0
    for i in range(1, ends_before + 1):
        if starts_after < i:
            break
        before_variants = C_NK[ends_before][i]  # Number of ways to choose i items from ends_before
        after_variants = CUMSUMS[starts_after][i + strict]  # Cumulative sum for after
        sum_answer += m(
            i * m(diff, before_variants),
            m(after_variants, TWO_TO_I[n - starts_after - ends_before]),
        )
        sum_answer %= MOD
    return sum_answer


def solve(n, lrs):
    actions = []
    for l, r in lrs:
        actions.append((l, 0))    # Start event (0 means start)
        actions.append((r, 1))    # End event (1 means end)
    actions.sort()
    sum_answer = 0
    ends_before = 0
    starts_after = len(lrs)
    for (prev_val, prev_not_is_start), (val, not_is_start) in zip(actions, actions[1:]):
        if prev_not_is_start:
            ends_before += 1
        else:
            starts_after -= 1
        sum_answer += get_val(ends_before, starts_after, val - prev_val, n, 1)
        sum_answer += get_val(starts_after, ends_before, val - prev_val, n, 0)
        sum_answer %= MOD
    return sum_answer


def get_subsets(ar):
    from itertools import chain, combinations

    def powerset(iterable):
        "powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)"
        s = list(iterable)
        return chain.from_iterable(combinations(s, r) for r in range(len(s) + 1))

    return powerset(ar)


def solve_simple(_, all_lrs):
    res = 0
    for lrs in get_subsets(all_lrs):
        if len(lrs) == 0:
            continue
        all_edges = set()
        for l, r in lrs:
            all_edges.add(l)
            all_edges.add(r)
        vals = []
        for i in range(min(all_edges), max(all_edges) + 1):
            s = 0
            for l, r in lrs:
                if i < l:
                    s += l - i
                elif i > r:
                    s += i - r
            vals.append(s)
        res += min(vals)
    return res


for _ in range(int(input())):
    n = int(input())
    lrs = [list(map(int, input().split())) for _ in range(n)]
    print(solve(n, lrs))


# https://github.com/VaHiX/CodeForces/