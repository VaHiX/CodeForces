# Contest 838, Problem A: Binary Blocks
# URL: https://codeforces.com/contest/838/problem/A

# ./filter_code_tmp/838/A/case_1/openai/gpt-oss-20b/without_hint_filtered_code.py_20250813-2115
import sys
from array import array


def solve() -> None:
    """Read input, compute the minimal number of toggles,
    and output the answer."""
    rd = sys.stdin.readline
    n, m = map(int, rd().split())

    # Build prefix sums of the original n × m image
    # S[i][j] -> number of 1's in rows 0..i-1, cols 0..j-1
    S = [array("I", [0]) * (m + 1) for _ in range(n + 1)]
    for i in range(n):
        line = rd().strip()
        curr = S[i + 1]
        prev = S[i]
        j0 = 0  # curr[0] is already 0
        for ch in line:
            # value of the current cell
            v = 1 if ch == "1" else 0
            curr[j0 + 1] = v + prev[j0 + 1] + curr[j0] - prev[j0]
            j0 += 1

    best = None
    max_k = min(n, m)

    for k in range(2, max_k + 1):
        # padded dimensions
        N = ((n + k - 1) // k) * k
        M = ((m + k - 1) // k) * k
        block_sz = k * k

        cost = 0
        i = 0
        while i < N:
            r1 = i
            r2 = i + k - 1
            if r2 >= n:
                r2 = n - 1
            j = 0
            while j < M:
                c1 = j
                c2 = j + k - 1
                if c2 >= m:
                    c2 = m - 1

                if r1 <= r2 and c1 <= c2:
                    ones = S[r2 + 1][c2 + 1] - S[r1][c2 + 1] - S[r2 + 1][c1] + S[r1][c1]
                    # cheapest way to uniform this block
                    if ones <= block_sz - ones:
                        cost += ones
                    else:
                        cost += block_sz - ones
                # else: block lies completely outside the original image
                #        all cells are padded zeros → cost 0

                j += k
            i += k

        if best is None or cost < best:
            best = cost

    print(best)


if __name__ == "__main__":
    solve()
