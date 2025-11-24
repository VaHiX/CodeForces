# Problem: CF 2161 E - Left is Always Right
# https://codeforces.com/contest/2161/problem/E

"""
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n * k) 
Space Complexity: O(n)

This solution uses dynamic programming to count valid assignments of '?' characters to 0 or 1
such that every substring of length k has the first character occurring more than the others.
It precomputes factorials and their modular inverses for combination calculations.
"""

import sys

input = sys.stdin.readline

mod = 998244353

# Precompute factorials and their modular inverses
FACT = [1]
for i in range(1, 5 * 10**5 + 1):
    FACT.append(FACT[-1] * i % mod)

FACT_INV = [pow(FACT[-1], mod - 2, mod)]
for i in range(5 * 10**5, 0, -1):
    FACT_INV.append(FACT_INV[-1] * i % mod)

FACT_INV.reverse()


def Combi(a, b):
    # Calculate combination C(a, b) mod mod
    if 0 <= b <= a:
        return FACT[a] * FACT_INV[b] % mod * FACT_INV[a - b] % mod
    else:
        return 0


t = int(input())
for tests in range(t):
    n, k = map(int, input().split())
    S = input().strip()

    # Track positions of first and last occurrences of 0 and 1
    last0 = -1
    last1 = -1
    first0 = -1
    first1 = -1

    for i in range(len(S)):
        if S[i] == "0":
            if first0 == -1:
                first0 = i
            last0 = i
        if S[i] == "1":
            if first1 == -1:
                first1 = i
            last1 = i

    ANS = 0

    # Initialize array X to track determined 0, 1, and 2 values
    X = [-1] * len(S)
    for i in range(n):
        if S[i] == "0":
            X[i] = 0
        if S[i] == "1":
            X[i] = 1

    # Propagate constraints backward through the string
    for i in range(n - 1, -1, -1):
        if i - (k - 1) >= 0:
            if X[i] == 1:
                if X[i - (k - 1)] == -1:
                    X[i - (k - 1)] = 1
                elif X[i - (k - 1)] == 0:
                    X[i - (k - 1)] = 2
            if X[i] == 0:
                if X[i - (k - 1)] == -1:
                    X[i - (k - 1)] = 0
                elif X[i - (k - 1)] == 1:
                    X[i - (k - 1)] = 2
            if X[i] == 2:
                X[i - (k - 1)] = 2

    # Identify position of last 2 value
    last2 = -1
    for i in range(n):
        if X[i] == 2:
            last2 = i

    # Preprocess counts from the end
    COUNT0 = [0] * (n + 1)
    COUNT1 = [0] * (n + 1)
    COUNTq = [0] * (n + 1)

    for i in range(n - 1, -1, -1):
        COUNT0[i] = COUNT0[i + 1]
        COUNT1[i] = COUNT1[i + 1]
        COUNTq[i] = COUNTq[i + 1]

        if S[i] == "0":
            COUNT0[i] += 1
        elif S[i] == "1":
            COUNT1[i] += 1
        else:
            COUNTq[i] += 1

    # Precompute cumulative counts of 0s and 1s
    COUNTX0 = [0] * (n + 1)
    COUNTX1 = [0] * (n + 1)

    for i in range(n - 1, -1, -1):
        COUNTX0[i] = COUNTX0[i + 1]
        COUNTX1[i] = COUNTX1[i + 1]

        if X[i] == 0:
            COUNTX0[i] += 1
        elif X[i] == 1:
            COUNTX1[i] += 1

    # Adjust for case when there's no 0 or 1
    if first0 == -1:
        first0 = n - 1
    if first1 == -1:
        first1 = n - 1

    # Process valid starting positions for 0s and 1s
    for i in range(1, n):
        # Stop condition
        if i > first0:
            break
        if i == n - k + 1:
            # Final position constraint for 0s
            zero = COUNT0[i]
            one = COUNT1[i]
            q = COUNTq[i]

            MIN = (k - 1) // 2
            rest = MIN - zero

            # Add combinatorial results
            if rest >= 0:
                for j in range(rest + 1):
                    ANS += Combi(q, j)
                    ANS %= mod

            break
        if S[i] == "1":
            continue
        if i > first0:
            break
        if i > n - k:

            # Handle boundary case for 0s
            zero = COUNT0[i + 1] + 1
            one = COUNT1[i + 1]
            q = COUNTq[i + 1]

            if q == 0:
                if zero <= (k - 1) // 2:
                    ANS += 1
            else:
                if zero <= (k - 1) // 2:
                    for j in range(min(q, (k - 1) // 2 - zero) + 1):
                        ANS += Combi(q, j)
                        ANS %= mod
        else:
            # General case handling for 0s
            if S[i] == "1":
                continue
            if X[i] == 1:
                continue
            if last2 >= i:
                continue
            zero = 1 + COUNTX0[i + 1] - COUNTX0[i + k - 1]
            one = COUNTX1[i + 1] - COUNTX1[i + k - 1]
            q = k - 1 - zero - one

            if zero <= (k - 1) // 2 and one <= (k - 1) // 2:
                ANS += Combi(q, (k - 1) // 2 - zero)
                ANS %= mod

    for i in range(1, n):
        # Stop condition
        if i > first1:
            break
        if i == n - k + 1:
            # Final position constraint for 1s
            zero = COUNT0[i]
            one = COUNT1[i]
            q = COUNTq[i]

            MIN = (k - 1) // 2

            rest = MIN - one

            # Add combinatorial results
            if rest >= 0:
                for j in range(rest + 1):
                    ANS += Combi(q, j)
                    ANS %= mod

            break

        if i > first1:
            break
        if S[i] == "0":
            continue
        if i > n - k:

            # Handle boundary case for 1s
            zero = COUNT0[i + 1]
            one = COUNT1[i + 1] + 1
            q = COUNTq[i + 1]

            if q == 0:
                if one <= (k - 1) // 2:
                    ANS += 1
            else:
                if one <= (k - 1) // 2:
                    for j in range(min(q, (k - 1) // 2 - one) + 1):
                        ANS += Combi(q, j)
                        ANS %= mod
            break
        else:
            # General case handling for 1s
            if S[i] == "0":
                continue
            if X[i] == 0:
                continue
            if last2 >= i:
                continue
            zero = COUNTX0[i + 1] - COUNTX0[i + k - 1]
            one = 1 + COUNTX1[i + 1] - COUNTX1[i + k - 1]
            q = k - 1 - zero - one

            if zero <= (k - 1) // 2 and one <= (k - 1) // 2:
                ANS += Combi(q, (k - 1) // 2 - zero)
                ANS %= mod

    print(ANS % mod)


# https://github.com/VaHiX/CodeForces/