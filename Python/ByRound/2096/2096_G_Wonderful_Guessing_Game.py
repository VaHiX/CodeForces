# Problem: CF 2096 G - Wonderful Guessing Game
# https://codeforces.com/contest/2096/problem/G

"""
Algorithm: 
This solution uses a binary encoding strategy with base-3 representation to solve the adaptive guessing game.
The key idea is to:
1. Use base-3 digits (0, 1, 2) to encode each number from 1 to n
2. For each query, split the numbers into three categories:
   - 0: Not in the current query array (represented as 0 in digit)
   - 1: In the first half of query array (represented as 1 in digit) 
   - 2: In the second half of query array (represented as 2 in digit)
3. Since one query is ignored, we ensure we can recover the number even after one ignored query

Time Complexity: O(log_3(n) * n) per test case where we generate base-3 codes and do decoding
Space Complexity: O(log_3(n) * n) to store the base-3 representations and pair mappings
"""

import sys


def build_pairs(q):
    """return list of (c, partner(c)) for all words of length q
    with digit sum % 3 == 0, c < partner(c).  also caches the result."""
    total = 3**q

    sum_mod = [0] * total
    for i in range(1, total):
        sum_mod[i] = (sum_mod[i // 3] + (i % 3)) % 3

    pairs = []
    for c in range(total):
        if sum_mod[c] != 0:
            continue
        if c == 0:
            continue

        p = 0
        tmp = c
        power = 1
        for _ in range(q):
            d = tmp % 3
            if d == 1:
                d = 2
            elif d == 2:
                d = 1
            p += d * power
            tmp //= 3
            power *= 3
        if c < p:
            pairs.append((c, p))
    return pairs


def decode_word(x, q):
    """return list of q digits (0,1,2) of the base‑3 representation of x."""
    digits = [0] * q
    for i in range(q):
        digits[i] = x % 3
        x //= 3
    return digits


def solve():
    input_data = sys.stdin.readline
    t_line = input_data()
    while t_line.strip() == "":
        t_line = input_data()
    t = int(t_line)

    pair_cache = {}

    out = sys.stdout
    for _ in range(t):

        line = input_data()
        while line.strip() == "":
            line = input_data()
        n = int(line)

        q = 1
        while 3 ** (q - 1) < n:
            q += 1

        if q not in pair_cache:
            pair_cache[q] = build_pairs(q)
        pairs = pair_cache[q]

        if n % 2 == 0:
            need = n // 2
            use_zero = False
        else:
            need = (n - 1) // 2
            use_zero = True

        code = []
        if use_zero:
            code.append(0)
        for i in range(need):
            c, p = pairs[i]
            code.append(c)
            code.append(p)

        digits = [decode_word(w, q) for w in code]

        print(q)
        out.flush()

        for pos in range(q):
            left = []
            right = []
            for idx, d in enumerate(digits):
                val = d[pos]
                if val == 1:
                    left.append(idx + 1)
                elif val == 2:
                    right.append(idx + 1)
            arr = left + right
            print(len(arr), *arr)
            out.flush()

        s = input_data().strip()

        answer = None
        for idx, d in enumerate(digits):
            ok = True
            for i, ch in enumerate(s):
                if ch == "?":
                    continue
                digit = d[i]
                if ch == "L" and digit != 1:
                    ok = False
                    break
                if ch == "R" and digit != 2:
                    ok = False
                    break
                if ch == "N" and digit != 0:
                    ok = False
                    break
            if ok:
                answer = idx + 1
                break

        if answer is None:
            answer = 1
        print(answer)
        out.flush()


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/