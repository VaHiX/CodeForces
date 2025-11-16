# Problem: CF 1774 H - Maximum Permutation
# https://codeforces.com/contest/1774/problem/H

"""
Algorithm: Maximum Permutation
Approach: 
1. The goal is to maximize the minimum sum of all contiguous subarrays of length k.
2. This is achieved by carefully arranging numbers to minimize the smallest such sum.
3. The algorithm uses a specific sequence construction technique based on modular arithmetic and grouping.

Time Complexity: O(n) for each test case, as we construct the permutation in linear time.
Space Complexity: O(n) for storing the permutation array.

Techniques Used:
- Modular arithmetic
- Careful arrangement of elements to optimize the minimum subarray sum
- Preprocessing based on division and remainder of n/k
"""

import sys


def read():
    """
    Reads input character by character and constructs an integer.
    Handles negative numbers and skips non-digit characters.
    """
    s = 0
    w = 1
    ch = sys.stdin.read(1)

    while ch < "0" or ch > "9":
        if ch == "-":
            w = -1
        ch = sys.stdin.read(1)

    while "0" <= ch <= "9":
        s = (s << 1) + (s << 3) + (ord(ch) - 48)
        ch = sys.stdin.read(1)
    return s * w


def f(x, y, k):
    """
    Helper function to calculate the index in the sequence.
    """
    return (x - 1) * k + y


def get(n, k, seq):
    """
    Generates the sequence based on the given logic.
    """
    if not (k & 1):
        for i in range(1, (n // 2) + 1):
            seq[(i << 1) - 1] = i
            seq[i << 1] = n + 1 - i
        return

    m = n // k
    cur = 3 * m

    for i in range(4, k + 1):
        if i & 1:
            for j in range(m, 0, -1):
                seq[f(j, i, k)] = cur + 1
                cur += 1
        else:
            for j in range(1, m + 1):
                seq[f(j, i, k)] = cur + 1
                cur += 1

    for i in range(1, (m + 1) // 2 + 1):
        seq[f(i, 1, k)] = (i << 1) - 1
        seq[f(i, 2, k)] = ((3 * m + 3) // 2) - i
        seq[f(i, 3, k)] = 3 * m - i + 1

    for i in range((m + 3) // 2, m + 1):
        delta = i - ((m + 3) // 2)
        seq[f(i, 1, k)] = ((3 * m + 3) // 2) + delta
        seq[f(i, 2, k)] = (m << 1) + 1 + delta
        seq[f(i, 3, k)] = m - (m & 1) - (delta << 1)


def print_result(n, k, ans):
    """
    Calculates the result and prints it in the required format.
    """
    res = 0
    sum_val = 0

    for i in range(1, k + 1):
        sum_val += ans[i]
    res = sum_val

    for i in range(k + 1, n + 1):
        sum_val += ans[i] - ans[i - k]
        res = min(res, sum_val)

    print(res)
    for i in range(1, n + 1):
        print(ans[i], end=" ")
    print()


def main():
    """
    Main function to handle multiple test cases.
    """
    t = read()
    while t > 0:
        t -= 1
        n = read()
        k = read()
        seq = [0] * (n + 1)
        ans = [0] * (n + 1)

        if n % k == 0:

            get(n, k, seq)
            for i in range(1, n + 1):
                ans[i] = seq[i]
            print_result(n, k, ans)
            continue

        q = n // k
        r = n % k

        if r == 1:

            cur = 0
            delta = (q << 1) + 1
            for i in range(1, n + 1, k):
                ans[i] = cur + 1
                cur += 1
            for i in range(n - k + 1, 1, -k):
                ans[i] = cur + 1
                cur += 1
            get(q * (k - 2), k - 2, seq)
            cur = 0
            for i in range(3, n + 1, k):
                for j in range(i, i + k - 2):
                    ans[j] = seq[cur + 1] + delta
                    cur += 1
            print_result(n, k, ans)
            continue

        if k - r == 1:

            if q == 1:
                cur = 0
                ans[k] = n
                get(n - 1, k - 1, seq)
                for i in range(1, k):
                    ans[i] = seq[cur + 1]
                    cur += 1
                for i in range(k + 1, n + 1):
                    ans[i] = seq[cur + 1]
                    cur += 1
                print_result(n, k, ans)
                continue

            cur = n + 1
            delta = q + 1
            for i in range(k, n + 1, k):
                ans[i] = cur - 1
                cur -= 1
            cur = 0
            for i in range(1, n + 1, k):
                ans[i] = cur + 1
                cur += 1
            get((q + 1) * (r - 1), r - 1, seq)
            cur = 0
            for i in range(2, n + 1, k):
                for j in range(i, i + r - 1):
                    ans[j] = seq[cur + 1] + delta
                    cur += 1
            print_result(n, k, ans)
            continue

        cur = 0
        delta = (q + 1) * r
        get((q + 1) * r, r, seq)
        for i in range(1, n + 1, k):
            for j in range(i, i + r):
                ans[j] = seq[cur + 1]
                cur += 1
        get(q * (k - r), k - r, seq)
        cur = 0
        for i in range(r + 1, n + 1, k):
            for j in range(i, i + (k - r)):
                ans[j] = seq[cur + 1] + delta
                cur += 1
        print_result(n, k, ans)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/