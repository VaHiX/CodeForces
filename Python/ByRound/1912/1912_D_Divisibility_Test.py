# Problem: CF 1912 D - Divisibility Test
# https://codeforces.com/contest/1912/problem/D

"""
Code Purpose:
This code solves the problem of finding the smallest group size k for which a divisibility test exists
for a given base b and modulo n. It checks three kinds of divisibility rules:
1. Take the last k digits (Kind 1)
2. Take a sum of groups of k digits (Kind 2)
3. Take an alternating sum of groups of k digits (Kind 3)

The approach uses modular arithmetic to determine when a valid test exists for each k.
For each k, it computes b^k mod n and checks if the result is 0, 1, or n-1:
- If 0: Kind 1 test (last k digits)
- If 1: Kind 2 test (sum of groups)
- If n-1: Kind 3 test (alternating sum)

Time Complexity: O(n), where n is the modulo value.
Space Complexity: O(1), only using a few variables for computation.
"""

def solve() -> None:
    b, n = map(int, input().split())  # Read base b and modulo n
    cur = 1  # Initialize current power of b mod n
    for k in range(1, n + 1):  # Try all possible group sizes from 1 to n
        cur *= b  # Compute b^k mod n incrementally
        cur %= n  # Apply modulo operation
        if cur == 0:  # If b^k ≡ 0 (mod n), kind 1 test exists
            print(1, k)
            return
        elif cur == 1:  # If b^k ≡ 1 (mod n), kind 2 test exists
            print(2, k)
            return
        elif cur == n - 1:  # If b^k ≡ -1 (mod n), kind 3 test exists
            print(3, k)
            return
    print(0)  # No valid test found


def main() -> None:
    for _ in range(int(input())):  # Process all test cases
        solve()


main()


# https://github.com/VaHiX/CodeForces/