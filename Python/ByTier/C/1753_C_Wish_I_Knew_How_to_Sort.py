# Problem: CF 1753 C - Wish I Knew How to Sort
# https://codeforces.com/contest/1753/problem/C

"""
Purpose: Solve the problem of finding the expected number of swaps to sort a binary array.
Approach:
- The problem models a Markov chain where we repeatedly pick two indices and swap if needed.
- We compute the expected number of steps until the array is sorted.
- For a binary array, the expected number of operations depends on the number of inversions and how they reduce over time.

Algorithms:
- Mathematical expectation calculation using linearity of expectation.
- Modular arithmetic for large numbers.
- Preprocessing to determine counts of 1s and their positions.

Time Complexity: O(n) per test case, dominated by the summation over inversion counts.
Space Complexity: O(1), only using a few variables for computation.

Note: This solution assumes that the array is already sorted if no swaps are needed.
"""

for _ in range(int(input())):
    n = int(input())
    a = [int(i) for i in input().split()]
    k = sum(a)  # Count of 1s in the array
    st = sum(a[-k:])  # Sum of last k elements, effectively used to compute inversion count
    ans = (
        sum(n * (n - 1) // 2 * pow(k - i, -2, 998244353) for i in range(st, k))
        % 998244353
    )
    print(ans)


# https://github.com/VaHiX/CodeForces/