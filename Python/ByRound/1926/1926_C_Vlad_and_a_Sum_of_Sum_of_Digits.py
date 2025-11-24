# Problem: CF 1926 C - Vlad and a Sum of Sum of Digits
# https://codeforces.com/contest/1926/problem/C

"""
Problem: Vlad and a Sum of Sum of Digits
Algorithm: Mathematical approach to compute sum of digit sums from 1 to n.
Time Complexity: O(1) per test case (preprocessing and computation is constant)
Space Complexity: O(1) (only storing results for output)

Approach:
- We use a mathematical method based on digit-wise contribution.
- Initially compute the sum of all numbers from 1 to n using formula n*(n+1)/2.
- Then subtract contributions from higher digits by iterating over digit places.
- The core idea is to compute how many times each digit contributes across the range.
"""

num = int(input())
arr = []
for i in range(num):
    n = int(input())
    summ = n * (n + 1) // 2  # Sum of all integers from 1 to n
    n += 1
    for i in range(6):  # Iterate through up to 6-digit numbers (sufficient for given constraints)
        dec = 10 ** (i + 1)  # Current decimal place (10, 100, 1000, ...)
        k = n // dec  # Number of complete cycles in this digit place
        # Subtract the overcounted values due to digit transitions (e.g., 10, 20, ..., 90, 100, ...)
        summ -= 9 * (((2 * (n - dec) - (k - 1) * dec) * k) // 2)
    arr.append(summ)
for x in arr:
    print(x)


# https://github.com/VaHiX/CodeForces/