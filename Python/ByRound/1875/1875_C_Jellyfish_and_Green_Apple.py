# Problem: CF 1875 C - Jellyfish and Green Apple
# https://codeforces.com/contest/1875/problem/C

"""
Algorithm: Jellyfish and Green Apple
Purpose: Determine the minimum number of knife operations to divide n apple pieces equally among m people.
Techniques: 
- Mathematical analysis using GCD and binary representation
- Bit manipulation to check for powers of two
- Counting set bits to calculate operations

Time Complexity: O(t) where t is the number of test cases. Each test case involves constant time operations.
Space Complexity: O(1) excluding the space for input/output storage.

The core idea is to:
1. Simplify the problem by computing GCD(n, m) to get P' and Q'
2. Check if Q' is a power of 2 (necessary condition for equal division)
3. If yes, calculate the minimal operations needed using bit manipulation and counting set bits
"""

import math
import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        m = int(data[index + 1])
        index += 2
        g = math.gcd(n, m)
        P_prime = n // g
        Q_prime = m // g
        if Q_prime == 1:
            results.append("0")
            continue
        # Check if Q_prime is a power of 2 (i.e., only one bit is set)
        if Q_prime & (Q_prime - 1) == 0 and Q_prime != 0:
            # Calculate the number of operations needed
            base = Q_prime
            q = P_prime // base
            r = P_prime % base
            pc = bin(r).count("1")  # Count of set bits in r
            c_min = q + pc  # Minimum number of fragments per person
            total_fragments = m * c_min  # Total number of pieces after all operations
            k = total_fragments - n  # Number of operations needed (each op increases count by 1)
            results.append(str(k))
        else:
            results.append("-1")
    for res in results:
        print(res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/