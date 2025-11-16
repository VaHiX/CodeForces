# Problem: CF 1787 F - Inverse Transformation
# https://codeforces.com/contest/1787/problem/F

"""
Code Purpose:
This code solves the problem of finding the initial permutation `a` such that the sum of `1/f(i)` is minimized, 
where `f(i)` is the minimal positive integer `m` such that applying the transformation `σ` (where `σ(x) = a_x`) `m` times 
returns to `x`. The transformation continues for `k` days, and we are given the permutation on the `k`-th day.

Key Algorithms/Techniques:
1. Cycle Detection in Permutations: Identifies cycles in the permutation to understand the transformation behavior.
2. Modular Exponentiation: Used to compute the effect of applying the transformation `k` times.
3. Grouping of Cycles: Groups cycles of even lengths to handle them together, and odd lengths separately.

Time Complexity: O(n log n) per test case due to cycle detection and grouping.
Space Complexity: O(n) for storing the permutation, cycles, and auxiliary data structures.

"""

import sys


def input_general():
    return sys.stdin.readline().rstrip("\r\n")


def input_num():
    return int(sys.stdin.readline().rstrip("\r\n"))


def input_multi(x=int):
    return map(x, sys.stdin.readline().rstrip("\r\n").split())


def input_list(x=int):
    return list(input_multi(x))


def power(p, x, e):
    # Modular exponentiation to calculate (x^e) % p
    base = x
    answer = 1
    while e:
        if e & 1:
            answer = (answer * base) % p

        base = (base * base) % p
        e >>= 1

    return answer


def main():
    # Precompute powers of 2 up to 2^19
    pre = {2**i: i for i in range(20)}
    n, k = input_multi()
    arr = input_list()
    arr = [x - 1 for x in arr]  # Convert to 0-based indexing
    count = {}
    cycle = []

    seen = [0] * n
    for x in arr:
        if seen[x] == 0:
            loop = [x]
            l = 1
            ptr = arr[x]
            seen[x] = 1

            while ptr != x:
                l += 1
                seen[ptr] = 1
                loop.append(ptr)
                ptr = arr[ptr]

            cycle.append(loop)
            if l not in count:
                count[l] = [loop]
            else:
                count[l].append(loop)

    # Check for even-length cycles and validate k
    for l in count.keys():
        if l % 2 == 0:
            if k >= 20 or len(count[l]) % (2**k) != 0:
                print("NO")
                return

    answer = [0] * n
    batch = 2 ** (min(k, 20))

    for l, loops in count.items():
        avail = len(loops)
        idx = 0

        while avail:
            size = min(avail & (-avail), batch)
            avail -= size
            goal = loops[idx : idx + size]
            idx += size

            if l % 2 == 0:
                # For even-length cycles, assign based on cyclic shifts in place
                group = []
                for i in range(l):
                    for j in range(size):
                        group.append(goal[j][i])

                for i, j in zip(group, group[1:] + [group[0]]):
                    answer[i] = j + 1

            else:
                # For odd-length cycles, use modular exponentiation for transformation
                inv_l = (l + 1) // 2
                mix_days = pre[size]
                hop = power(l, inv_l, k - mix_days)

                new = [[g[(hop * i) % l] for i in range(l)] for g in goal]
                group = []
                for i in range(l):
                    for j in range(size):
                        group.append(new[j][i])

                for i, j in zip(group, group[1:] + [group[0]]):
                    answer[i] = j + 1

    print("YES")
    print(" ".join([str(x) for x in answer]))


if __name__ == "__main__":
    cases = input_num()

    for _ in range(cases):
        main()


# https://github.com/VaHiX/CodeForces/