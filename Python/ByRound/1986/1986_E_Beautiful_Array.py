# Problem: CF 1986 E - Beautiful Array
# https://codeforces.com/contest/1986/problem/E

"""
Algorithm: Greedy with Modular Arithmetic
Approach:
1. Sort the array to group numbers by their remainder when divided by k.
2. For each group of numbers with the same remainder:
   - If the count is odd, we use a greedy approach to minimize operations.
   - If the count is even, we pair elements and calculate cost.
3. If an odd count appears more than once, it's impossible to form a palindrome.
4. Return the total number of operations needed.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing grouped elements
"""

from random import randint

rrr = randint(8888, 88888)


def sol():
    n, k = tuple(map(int, input().split()))
    nums = sorted(map(int, input().split()))  # Sort numbers to group by modulo
    mo = {}
    for i in nums:
        mo.setdefault(i % k, []).append(i)  # Group numbers by remainder
    ods = False  # Flag to check if an odd-sized group has been processed
    ans = 0  # Total operations needed
    for arr in mo.values():
        if len(arr) & 1:  # If group size is odd
            if ods:  # If another odd group exists, impossible to form palindrome
                return print(-1)
            ods = True
            if len(arr) == 1:  # If only one element, no operation needed
                continue
            rd = 0  # Right side difference
            for i in range(1, len(arr), 2):
                rd += arr[i + 1] - arr[i]  # Accumulate differences
            frd = rd  # First candidate for minimum
            ld = 0  # Left side difference
            for i in range(2, len(arr), 2):  # Sliding window to find optimal pairing
                rd -= arr[i] - arr[i - 1]  # Update right side
                ld += arr[i - 1] - arr[i - 2]  # Update left side
                frd = min(frd, ld + rd)  # Track minimum operations
            ans += frd // k  # Add operations needed (in terms of k)
            continue
        # For even-length groups, simply pair adjacent elements
        for i in range(1, len(arr), 2):
            ans += (arr[i] - arr[i - 1]) // k  # Calculate cost
    print(ans)


for _ in range(int(input())):
    sol()


# https://github.com/VaHiX/CodeForces/