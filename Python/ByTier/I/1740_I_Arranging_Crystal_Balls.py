# Problem: CF 1740 I - Arranging Crystal Balls
# https://codeforces.com/contest/1740/problem/I

"""
Algorithm: Difference Array + Sliding Window + Dynamic Programming
Time Complexity: O(n * m * log(m))
Space Complexity: O(n + m)

This solution uses the concept of difference arrays to model the operations
on circular statues. It treats each operation as adding/subtracting 1 to a
segment of k consecutive statues. The problem becomes finding minimum operations
to reduce all values to zero.

Key Techniques:
1. Difference array transformation for efficient range updates
2. Cyclic decomposition based on gcd(n, k)
3. Dynamic programming with sliding window optimization
4. Segment-wise optimization for cost calculation
"""

import collections
import math
import sys


def main():

    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    m = int(next(it))
    k = int(next(it))
    INF = 0x3FFFFFFF

    a = [0] * (n + 1)
    b = [0] * (n + 1)

    f_arr = [0] + [INF] * (m - 1)

    for i in range(1, n + 1):
        a[i] = int(next(it))

    for i in range(1, n + 1):
        b[i] = a[i] - a[i - 1]

    if k == n:
        for i in range(2, n + 1):
            if b[i] != 0:
                sys.stdout.write("-1")
                return
        sys.stdout.write(str(min(a[1], m - a[1])))
        return

    b[1] = a[1] - a[n]

    d = math.gcd(n, k)
    l_val = n // d

    g_arr = [INF] * (2 * m)

    for cycle_start in range(1, d + 1):

        cycle_s = [0]
        j = cycle_start
        while True:
            new_val = (cycle_s[-1] + b[j]) % m
            cycle_s.append(new_val)

            if j == 1 or (j + k > n + 1):
                a[1] = (a[1] + (m - new_val)) % m
            j += k
            if j > n:
                j -= n
            if j == cycle_start:
                break

        if cycle_s[l_val] % m != 0:
            sys.stdout.write("-1")
            return

        w = [0] * m
        for t_idx in range(m):
            cost = min(t_idx, m - t_idx)
            for j_idx in range(1, l_val):
                cost += min(cycle_s[j_idx], m - cycle_s[j_idx])
                cycle_s[j_idx] = (cycle_s[j_idx] + 1) % m
            w[t_idx] = cost

        w1_list = []
        if m >= 2:
            w1_list.append({"k": w[1] - w[0], "l": 0, "r": None})
            for j_val in range(2, m):
                diff = w[j_val] - w[j_val - 1]
                if diff != w1_list[-1]["k"]:
                    w1_list[-1]["r"] = j_val - 1
                    w1_list.append({"k": diff, "l": j_val, "r": None})
            w1_list[-1]["r"] = m - 1
        else:
            w1_list.append({"k": 0, "l": 0, "r": 0})

        for idx in range(2 * m):
            g_arr[idx] = INF

        for seg in w1_list:
            seg_k = seg["k"]
            seg_l = seg["l"]
            seg_r = seg["r"]
            dq = collections.deque()

            for cur in range(seg_l, m + seg_r):

                while dq and dq[0] < cur - seg_r:
                    dq.popleft()

                if cur - seg_l < m:
                    while (
                        dq
                        and (f_arr[dq[-1]] + seg_k * ((cur - seg_l) - dq[-1]))
                        >= f_arr[cur - seg_l]
                    ):
                        dq.pop()
                    dq.append(cur - seg_l)

                candidate = f_arr[dq[0]] + w[cur - dq[0]]
                if candidate < g_arr[cur]:
                    g_arr[cur] = candidate

        for j_val in range(m):
            f_arr[j_val] = min(g_arr[j_val], g_arr[j_val + m])

    ans = INF
    for i_val in range(m):
        if ((k * i_val) // d) % m == a[1]:
            ans = min(ans, f_arr[i_val])
    sys.stdout.write(str(ans) if ans != INF else "-1")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/