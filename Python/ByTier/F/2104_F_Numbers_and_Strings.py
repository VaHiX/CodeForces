# Problem: CF 2104 F - Numbers and Strings
# https://codeforces.com/contest/2104/problem/F

"""
F. Numbers and Strings

Purpose:
This code efficiently computes the number of distinct strings S(x) for x in [1, n], where:
- S(x) is formed by concatenating x and (x+1), then sorting digits in non-decreasing order.

Algorithms/Techniques:
- Precompute all possible valid patterns of digit counts that can be formed by concatenating two consecutive numbers
  and sorting the result.
- Use binary search (via bisect_right) to quickly query how many such distinct strings are <= a given value.
- Optimized enumeration and mapping using digit count combinations.

Time Complexity: O(10^9) preprocessing + O(t * log(10^9)) per query
Space Complexity: O(10^9) for storing the list of valid first occurrences

"""
from bisect import bisect_right


def build_first_occ():
    patterns = []

    def gen(cnt, d, rem):
        # Generate all combinations of digit counts (up to 9 digits total)
        if d == 10:
            if rem == 0:
                s = sum(cnt)
                if s == 0:
                    patterns.append((0, cnt.copy()))
                elif cnt[0] != s:
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
        # Try placing 0 to rem digits of type d
        for v in range(rem + 1):
            cnt[d] = v
            gen(cnt, d + 1, rem - v)
        cnt[d] = 0

    cnt = [0] * 10
    # Enumerate all lengths from 0 to 8 (total digit length up to 9)
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
    
    # Iterate through relevant lengths and construct valid S(x) patterns
    for r in range(9):
        mul = pow10[r]
        Mmax = (MAX_LIMIT + 1) // mul

        # Loop over last digit (b+1) of x + 1 (x+1 is a number ending in b+1)
        for b in range(9):
            Amax = (Mmax - (b + 1)) // 10
            if Amax < 0:
                continue

            # Use bisect to find how many patterns match constraints
            up = bisect_right(a_mins, Amax)
            for i in range(up):
                a_min = a_mins[i]
                cnts = a_counts[i]

                # Form x such that (x + 1) ends in b+1 and total length is r
                m = a_min * 10 + (b + 1)
                x = m * mul - 1

                if x < 1 or x > MAX_LIMIT:
                    continue

                C = [2 * cnts[d] for d in range(10)]
                # Handle special case for "0" and "9"
                if not (a_min == 0 and b == 0 and r > 0):
                    C[b] += 1
                C[b + 1] += 1
                
                if r > 0:
                    C[0] += r
                    C[9] += r

                # Convert digit counts to sorted string representation
                s = "".join(str(d) * C[d] for d in range(10))
                
                # Only update if this is better (smaller x) or new pattern
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