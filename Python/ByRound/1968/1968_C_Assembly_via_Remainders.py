# Problem: CF 1968 C - Assembly via Remainders
# https://codeforces.com/contest/1968/problem/C

"""
Algorithm: Assembly via Remainders
Techniques: Greedy approach with remainder construction

Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(n) for storing the result array

The approach builds the array `a` greedily:
1. Start with `a[0]` as `max(x) + 1` (ensuring it's larger than any remainder)
2. For each subsequent element `a[i]`, set it to `a[i-1] + x[i-1]` to ensure `a[i] % a[i-1] = x[i-1]`
3. This works because we ensure `a[i-1] > x[i-1]` by construction, making the modulo operation straightforward
"""

import sys

input = sys.stdin.read


def main():

    data = input().split()
    index = 0

    t = int(data[index])
    index += 1

    results = []

    for _ in range(t):

        n = int(data[index])
        index += 1

        a = list(map(int, data[index : index + n - 1]))
        index += n - 1

        m = max(a) + 1  # Start with a value larger than any remainder

        result = []

        for i in range(n):
            if i != 0:
                # Ensure a[i] is larger than the previous remainder x[i-1]
                m += a[i - 1]

            result.append(m)

        results.append(" ".join(map(str, result)))

    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/