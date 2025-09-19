# Contest 2030, Problem G1: The Destruction of the Universe (Easy Version)
# URL: https://codeforces.com/contest/2030/problem/G1

MOD = 998244353


def build_c_nk(max_n):
    ar = [1]
    ars = [ar]
    for _ in range(1, max_n + 1):
        ar = [1] + [(ar[j] + ar[j + 1]) % MOD for j in range(len(ar) - 1)] + [1]
        ars.append(ar)

    return ars


def build_end_cumsums(ar):
    # sum(j >= i) ar[j]
    cumsums = [0] * (len(ar) + 1)
    for i in range(len(ar) - 1, -1, -1):
        cumsums[i] = (cumsums[i + 1] + ar[i]) % MOD
    return cumsums


def build_2_to_i(max_n):
    ar = [1]
    for _ in range(1, max_n + 1):
        ar.append((ar[-1] * 2) % MOD)
    return ar


C_NK = build_c_nk(5000 + 1)
CUMSUMS = [build_end_cumsums(ar) for ar in C_NK]
TWO_TO_I = build_2_to_i(5000 + 1)


# print(build_c_nk(5)) # debug
# print([build_end_cumsums(ar) for ar in build_c_nk(5)]) # debug
# print(build_c_nk(5)[4][2]) # debug


def m(a, b):
    return (a * b) % MOD


def get_val(ends_before, starts_after, diff, n, strict=1):
    sum_answer = 0
    for i in range(1, ends_before + 1):
        # starts < ends
        if starts_after < i:
            break
        before_variants = C_NK[ends_before][i]
        # av = sum_j>=i (C_NK[ends_before][j]
        after_variants = CUMSUMS[starts_after][i + strict]

        sum_answer += m(
            i * m(diff, before_variants),
            m(after_variants, TWO_TO_I[n - starts_after - ends_before]),
        )
        sum_answer %= MOD

        # print("->", i, diff, before_variants, after_variants, n - starts_after - ends_before, TWO_TO_I[n - starts_after - ends_before]) # debug
        # print(".", sum_answer, f"{i}vs{ends_before} strict={strict}") # debug
    return sum_answer


def solve(n, lrs):
    actions = []  # (index, not_is_start)
    for l, r in lrs:
        actions.append((l, 0))
        actions.append((r, 1))
    actions.sort()

    sum_answer = 0

    ends_before = 0
    starts_after = len(lrs)
    for (prev_val, prev_not_is_start), (val, not_is_start) in zip(actions, actions[1:]):
        if prev_not_is_start:
            ends_before += 1
        else:
            starts_after -= 1

        # print(f"]*{ends_before} {prev_val}-{val} [*{starts_after}") # debug

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
    # print(solve_simple(n, lrs))

# import random;
# random.seed(1)
# for i in range(20):
#     n = random.randrange(2, 5)
#     lrs = []
#     for _ in range(n):
#         l = random.randrange(1, 6)
#         r = random.randrange(l, 6)
#         l, r = min(l, r), max(l, r)
#         lrs.append((l, r))

#     print(n, lrs)
#     assert solve(n, lrs) == solve_simple(n, lrs)
