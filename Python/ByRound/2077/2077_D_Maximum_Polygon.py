# Problem: CF 2077 D - Maximum Polygon
# https://codeforces.com/contest/2077/problem/D

"""
D. Maximum Polygon

Purpose:
This code finds the lexicographically largest subsequence from an array that can form a valid polygon.
A valid polygon requires at least 3 sides and satisfies the polygon inequality: 
2 * max(side_lengths) < sum(side_lengths). The algorithm uses a greedy approach combined with 
prefix/suffix computations to efficiently check candidates.

Algorithms/Techniques:
- Greedy selection with candidate pruning
- Prefix/Suffix arrays for efficient sum computation
- Bit manipulation to estimate maximum possible bit length
- Custom ordering logic for lexicographically largest result

Time Complexity:
O(n * log(max_a)) where n is the size of the array and max_a is the maximum element.
The nested loops, although seemingly O(n^2), are optimized to run efficiently with early breaks
and candidate pruning based on bit length.

Space Complexity:
O(n) due to storing arrays for prefix/suffix sums and subsequences.

"""

import sys


def solve():
    data = sys.stdin
    line = data.readline()
    if not line:
        return
    t = int(line.strip())
    out_lines = []
    for _ in range(t):
        while True:
            line = data.readline()
            if not line:
                return
            if line.strip():
                break
        n = int(line.strip())
        a = list(map(int, data.readline().split()))
        if n < 3:
            out_lines.append("-1")
            continue
        max_a = max(a)
        p = max_a.bit_length() + 2  # estimate upper bound for candidate values
        vals = list(set(a))
        vals.sort(reverse=True)
        cand_vals = vals[: p + 1]  # consider only top candidates based on bit length
        best_seq = None
        for x in cand_vals:
            count_le = 0
            for val in a:
                if val <= x:
                    count_le += 1
                    if count_le >= 3:  # skip if fewer than 3 <= x elements to avoid trivial cases
                        break
            if count_le < 3:
                continue
            suff = [0] * (n + 1)
            for i in range(n - 1, -1, -1):
                ai = a[i]
                if ai <= x:
                    suff[i] = suff[i + 1] + ai
                else:
                    suff[i] = suff[i + 1]
            s_cur = []
            sumS = 0
            for i in range(n):
                ai = a[i]
                if ai > x:
                    continue
                # Maintain a stack-like structure ensuring increasing order and valid polygon property
                while s_cur and ai > s_cur[-1]:
                    old_val = s_cur[-1]
                    potential = (sumS - old_val) + ai + suff[i + 1]
                    if potential > 2 * x:  # invalid triangle inequality, remove from stack
                        s_cur.pop()
                        sumS -= old_val
                    else:
                        break
                s_cur.append(ai)
                sumS += ai
            # Check if this subsequence is valid polygon and better lexicographically
            if len(s_cur) >= 3 and sumS > 2 * x:
                if best_seq is None or s_cur > best_seq:
                    best_seq = s_cur.copy()
        if best_seq is None:
            out_lines.append("-1")
        else:
            out_lines.append(str(len(best_seq)))
            out_lines.append(" ".join(map(str, best_seq)))
    sys.stdout.write("\n".join(out_lines))


def main():
    solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/