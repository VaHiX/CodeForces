# Problem: CF 1986 G1 - Permutation Problem (Simple Version)
# https://codeforces.com/contest/1986/problem/G1

"""
Algorithm/Technique:
- Precompute divisors for all numbers up to 10^5 using a sieve-like method.
- For each element in the permutation, compute reduced values a[i] = p[i]/gcd(p[i], i) and b[i] = i/gcd(p[i], i).
- Use a frequency map to count occurrences of b[i] values for each divisor of a[i].
- For each element, check how many previous elements satisfy the divisibility condition based on divisor relationships.

Time Complexity: O(n * sqrt(n)) where n is up to 10^5
Space Complexity: O(n) for storing divisors list and frequency maps
"""

import math
import sys

MAX_VAL = 100000
# Precompute all divisors for numbers 1 to MAX_VAL
divisors_list = [[] for _ in range(MAX_VAL + 1)]
for i in range(1, MAX_VAL + 1):
    for j in range(i, MAX_VAL + 1, i):
        divisors_list[j].append(i)


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        p = list(map(int, data[index : index + n]))
        index += n
        # Arrays to store reduced values for each element
        a = [0] * n
        b = [0] * n
        for i in range(n):
            idx = i + 1
            g = math.gcd(p[i], idx)
            a[i] = p[i] // g
            b[i] = idx // g
        # Frequency map to track occurrences of b values for each divisor
        freq_map = {}
        ans = 0
        for i in range(n):
            a_val = a[i]
            b_val = b[i]
            # Check all divisors of a[i] to find matching previous elements
            divs = divisors_list[a_val]
            for d in divs:
                if d in freq_map:
                    d_dict = freq_map[d]
                    if b_val in d_dict:
                        ans += d_dict[b_val]
            # Update frequency map with current element's values
            d0 = b_val
            if d0 not in freq_map:
                freq_map[d0] = {}
            d0_dict = freq_map[d0]
            for k in divs:
                d0_dict[k] = d0_dict.get(k, 0) + 1
        results.append(str(ans))
    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/