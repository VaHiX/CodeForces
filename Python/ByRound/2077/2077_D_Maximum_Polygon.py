# Contest 2077, Problem D: Maximum Polygon
# URL: https://codeforces.com/contest/2077/problem/D

import sys
import threading


def solve():
    data = sys.stdin
    line = data.readline()
    if not line:
        return
    t = int(line.strip())
    out_lines = []
    for _ in range(t):
        # Read n
        while True:
            line = data.readline()
            if not line:
                return
            if line.strip():
                break
        n = int(line.strip())
        a = list(map(int, data.readline().split()))
        # If there are fewer than 3 elements, no polygon subsequence exists
        if n < 3:
            out_lines.append("-1")
            continue
        max_a = max(a)
        # p is based on the maximum possible size of a sequence with no valid polygon subsequence
        p = max_a.bit_length() + 2
        # Candidate values: top p+1 distinct values of a, in descending order
        vals = list(set(a))
        vals.sort(reverse=True)
        cand_vals = vals[: p + 1]
        best_seq = None

        for x in cand_vals:
            # We need at least 3 elements <= x
            count_le = 0
            for val in a:
                if val <= x:
                    count_le += 1
                    if count_le >= 3:
                        break
            if count_le < 3:
                continue

            # Compute suffix sums of values <= x
            suff = [0] * (n + 1)
            for i in range(n - 1, -1, -1):
                ai = a[i]
                if ai <= x:
                    suff[i] = suff[i + 1] + ai
                else:
                    suff[i] = suff[i + 1]

            s_cur = []
            sumS = 0
            # Greedy construction of lexicographically largest subsequence with max = x
            for i in range(n):
                ai = a[i]
                if ai > x:
                    continue
                while s_cur and ai > s_cur[-1]:
                    old_val = s_cur[-1]
                    # Potential maximum sum if we remove old_val and add ai and all suffix values <= x after i
                    potential = (sumS - old_val) + ai + suff[i + 1]
                    if potential > 2 * x:
                        s_cur.pop()
                        sumS -= old_val
                    else:
                        break
                s_cur.append(ai)
                sumS += ai

            # Check if this subsequence can form a polygon
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
