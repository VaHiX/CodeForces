# Problem: CF 1991 D - Prime XOR Coloring
# https://codeforces.com/contest/1991/problem/D

"""
Algorithm: Prime XOR Coloring
Techniques: Precomputed coloring patterns, mathematical properties of XOR and primes

Time Complexity: O(1) per test case, O(t) overall where t is number of test cases
Space Complexity: O(1) as we use precomputed patterns of fixed size

The problem involves constructing a graph where vertices u and v are connected if u⊕v is prime.
The task is to find the chromatic number of this graph and provide a valid coloring.

Key observations:
- For small n (n < 6), the chromatic number can be determined directly.
- For larger n, it's observed that the chromatic number is at most 4.
- The pattern is precomputed and reused for efficiency.

The solution uses:
1. A precomputed pattern for small n values (1 2 2 3 3)
2. A precomputed pattern for larger n values (1 2 3 4 repeated)
3. For n < 6, we output the minimum number of colors (which is (n + 2) // 2) and the pattern
4. For n >= 6, we output 4 colors and the precomputed pattern
"""

xre = "1 2 2 3 3 "  # Precomputed pattern for small n
pre = memoryview(b"1 2 3 4 " * 50005)  # Precomputed pattern for large n


def solve():
    n = int(input())
    if n < 6:
        # For small n, determine the minimum number of colors needed
        # and print the precomputed pattern
        print((n + 2) // 2)
        print(xre[: n * 2])
    else:
        # For larger n, we know the chromatic number is 4
        # Print the precomputed pattern for 4 colors
        print(4)
        print(pre[: n * 2].tobytes().decode())


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/