# Problem: CF 2104 F - Numbers and Strings
# https://codeforces.com/contest/2104/problem/F

"""
F. Numbers and Strings

This problem involves computing for each integer x from 1 to n, the string S(x) which:
1. Combines x and (x+1) in decimal form without separators or leading zeros.
2. Sorts all digits in non-decreasing order.

The key insight is to precompute all possible sorted digit strings that can be formed by
the process for numbers up to 10^9 - 2.

Approach:
- Generate all valid combinations of digits (as counts) that can form sorted concatenated strings.
- For each such pattern, compute the minimal number that generates it.
- Use binary search (via bisect_right) for fast querying.

Time Complexity: O(10^9) precomputation, O(log(10^9)) per query
Space Complexity: O(10^9) to store all possible patterns
"""

from bisect import bisect_right


def build_first_occ():
    patterns = []

    def gen(cnt, d, rem):
        if d == 10:
            if rem == 0:
                s = sum(cnt)
                if s == 0:
                    # Special case: 0
                    patterns.append((0, cnt.copy()))
                elif cnt[0] != s:
                    # Find first non-zero digit to build minimum number
                    for x_d in range(1, 10):
                        if cnt[x_d]:
                            cnt[x_d] -= 1
                            lead = x_d
                            break
                    zeros = cnt[0]
                    tail = "".join(str(i) * cnt[i] for i in range(1, 10))
                    a_min = int(str(lead) + "0" * zeros + tail)
                    cnt[lead] += 1
                    patterns.append((a_min, cnt.copy()))
            return
        # Try placing different digit counts at current position
        for v in range(rem + 1):
            cnt[d] = v
            gen(cnt, d + 1, rem - v)
        cnt[d] = 0

    cnt = [0] * 10
    for length in range(9):
        gen(cnt, 0, length)
    patterns.sort(key=lambda x: x[0])
    a_mins = [p[0] for p in patterns]
    a_counts = [p[1] for p in patterns]
    MAX_LIMIT = 10**9 - 2
    mapping = {}
    pow10 = [1] * 10
    for i in range(1, 10):
        pow10[i] = pow10[i - 1] * 10
    # Try all possible multipliers and offsets to generate patterns
    for r in range(9):
        mul = pow10[r]
        Mmax = (MAX_LIMIT + 1) // mul
        # Try different last digits b (from 0 to 8, since we are adding 1)
        for b in range(9):
            Amax = (Mmax - (b + 1)) // 10
            if Amax < 0:
                continue
            up = bisect_right(a_mins, Amax)
            # Iterate over valid a_min values to generate mappings
            for i in range(up):
                a_min = a_mins[i]
                cnts = a_counts[i]
                m = a_min * 10 + (b + 1)  # Construct m = a_min * 10 + last_digit
                x = m * mul - 1  # Construct final number
                if x < 1 or x > MAX_LIMIT:
                    continue
                C = [2 * cnts[d] for d in range(10)]
                if not (a_min == 0 and b == 0 and r > 0):
                    C[b] += 1
                C[b + 1] += 1
                if r > 0:
                    C[0] += r
                    C[9] += r
                s = "".join(str(d) * C[d] for d in range(10))
                if s not in mapping or x < mapping[s]:
                    mapping[s] = x
    return sorted(mapping.values())


first_occ = build_first_occ()
if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        n = int(input())
        print(bisect_right(first_occ, n))


# https://github.com/VaHiX/CodeForces/