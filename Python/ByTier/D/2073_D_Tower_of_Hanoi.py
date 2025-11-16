# Problem: CF 2073 D - Tower of Hanoi
# https://codeforces.com/contest/2073/problem/D

"""
Tower of Hanoi with Dynamic Updates
Algorithm: Segment Tree with Permutation Composition
Time Complexity: O((n + q) * log(n)) where n is the number of disks and q is number of operations
Space Complexity: O(n) for the segment tree and auxiliary arrays

This solution handles two types of operations:
1. Change operation: Update the rod number for a specific disk
2. Solve operation: Compute minimum steps to move all disks from radii l to r to rod 1

The approach uses a segment tree where each node stores:
- A permutation representing rod movements
- A vector of 3 values representing step counts for each rod

We use permutation composition to combine results from segments,
and vector addition to accumulate step counts.
"""

import sys

input = sys.stdin.readline


MOD = 998244353


_Permutations = {1: (0, 2, 1), 2: (2, 1, 0), 3: (1, 0, 2)}
_IdentityPermutation = (0, 1, 2)


def compose_permutations(P_R, P_L):
    """Computes P_new(i) = P_R(P_L(i)). P_new[i] = P_R[P_L[i]]"""
    return (P_R[P_L[0]], P_R[P_L[1]], P_R[P_L[2]])


def apply_permutation_to_vector(P, V):
    """Applies permutation P to vector V. Result[P[i]] = V[i]"""
    R = [0, 0, 0]

    R[P[0]] = V[0]
    R[P[1]] = V[1]
    R[P[2]] = V[2]
    return R


def vec_add(V1, V2):
    """Adds two 3x1 vectors V1 and V2 mod MOD."""
    return [(V1[i] + V2[i]) % MOD for i in range(3)]


MAX_N = 100000 + 5
pow2 = [1] * MAX_N
inv_pow2 = [1] * MAX_N


def precompute_powers(n):
    pow2[0] = 1
    inv2 = pow(2, MOD - 2, MOD)
    inv_pow2[0] = 1
    for i in range(1, n + 1):
        pow2[i] = (pow2[i - 1] * 2) % MOD
        inv_pow2[i] = (inv_pow2[i - 1] * inv2) % MOD


tree = [(None, None)] * (4 * MAX_N)
p = [0] * MAX_N
Z = [0, 0, 0]

_Vectors = {1: [0, 1, 1], 2: [1, 0, 1], 3: [1, 1, 0]}


def get_leaf_values(k):
    pk = p[k]
    Pk = _Permutations[pk]
    Vk = _Vectors[pk]
    p2k = pow2[k]
    Sk = [(Vk_i * p2k) % MOD for Vk_i in Vk]
    return Pk, Sk


def merge(left_result, right_result):

    P_L, S_L = left_result
    P_R, S_R = right_result
    P_new = compose_permutations(P_R, P_L)
    S_permuted_L = apply_permutation_to_vector(P_R, S_L)
    S_new = vec_add(S_permuted_L, S_R)
    return P_new, S_new


def build(node, start, end):
    if start == end:
        tree[node] = get_leaf_values(start)
    else:
        mid = (start + end) // 2

        build(2 * node, start, mid)
        build(2 * node + 1, mid + 1, end)

        tree[node] = merge(tree[2 * node], tree[2 * node + 1])


def update(node, start, end, idx):
    if start == end:
        tree[node] = get_leaf_values(idx)
    else:
        mid = (start + end) // 2
        if idx <= mid:
            update(2 * node, start, mid, idx)
        else:
            update(2 * node + 1, mid + 1, end, idx)
        tree[node] = merge(tree[2 * node], tree[2 * node + 1])


def query(node, start, end, l, r):
    if r < start or end < l:
        return (_IdentityPermutation, Z)
    if l <= start and end <= r:
        return tree[node]
    mid = (start + end) // 2
    left_result = query(2 * node, start, mid, l, r)
    right_result = query(2 * node + 1, mid + 1, end, l, r)
    return merge(left_result, right_result)


def solve():
    n, q = map(int, input().split())
    initial_p = list(map(int, input().split()))
    for i in range(n):
        p[i + 1] = initial_p[i]

    precompute_powers(n)
    build(1, 1, n)

    results_output = []
    _inv_pow2 = inv_pow2

    for _ in range(q):
        line = input().split()
        op_type = line[0]

        if op_type == "c":
            x, y = int(line[1]), int(line[2])
            if p[x] != y:
                p[x] = y
                update(1, 1, n, x)
        elif op_type == "s":
            l, r = int(line[1]), int(line[2])

            _, S_combined = query(1, 1, n, l, r)

            final_sum_comp0 = S_combined[0]
            inv_l_pow = _inv_pow2[l]
            answer = (final_sum_comp0 * inv_l_pow) % MOD
            results_output.append(str(answer))

    sys.stdout.write("\n".join(results_output) + "\n")


solve()


# https://github.com/VaHiX/CodeForces/