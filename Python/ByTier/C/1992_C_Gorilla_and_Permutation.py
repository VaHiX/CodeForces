# Problem: CF 1992 C - Gorilla and Permutation
# https://codeforces.com/contest/1992/problem/C

"""
Code Purpose:
This code solves the problem of constructing a permutation of length n that maximizes the difference 
between the sum of function f(i) and the sum of function g(i) over all prefixes of the permutation.

The key idea is to strategically arrange numbers into three groups:
1. Numbers from k to n (inclusive) — these contribute to f(i) but not g(i)
2. Numbers from m+1 to k-1 — these contribute neither to f(i) nor g(i), can be placed anywhere
3. Numbers from 1 to m (inclusive) — these contribute to g(i) but not f(i)

By placing these groups in a specific order, we maximize the difference.

Algorithms/Techniques:
- Greedy arrangement strategy
- Grouping numbers based on their contribution to f(i) and g(i)

Time Complexity:
O(n) - Each test case involves simple loops to generate groups and print the result.

Space Complexity:
O(n) - Space is used to store the three groups and the final permutation.
"""

def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    ptr = 0
    t = int(data[ptr])
    ptr += 1
    for _ in range(t):
        n = int(data[ptr])
        m = int(data[ptr + 1])
        k = int(data[ptr + 2])
        ptr += 3

        # Group A: Numbers from k to n (inclusive), these contribute to f(i) but not g(i)
        group_a = list(range(n, k - 1, -1))

        # Group B: Numbers from m+1 to k-1, these contribute neither to f(i) nor g(i)
        group_b = list(range(m + 1, k))

        # Group C: Numbers from 1 to m (inclusive), these contribute to g(i) but not f(i)
        group_c = list(range(1, m + 1))

        # Concatenate the groups to form the final permutation
        permutation = group_a + group_b + group_c

        print(" ".join(map(str, permutation)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/