# Problem: CF 875 A - Classroom Watch
# https://codeforces.com/contest/875/problem/A

"""
Task: Find all positive integers x such that x + sum_of_digits(x) = n.
Algorithm: 
    - For a given n, we iterate through possible values of x from n-1 down to max(0, n-81).
    - The upper bound of 81 comes from the fact that the maximum sum of digits for a number 
      less than n is 9 * number_of_digits, which is at most 9 * 10 = 90 for numbers up to 10^9.
    - For each candidate x, compute x + sum_of_digits(x) and check if it equals n.
    - Store valid x values in reverse order and then print them in ascending order.

Time Complexity: O(d * k), where d is the number of digits in n (~10 for n up to 10^9), and k is the number of valid x values (at most 81).
Space Complexity: O(k), where k is the number of valid x values stored.

Note: A more efficient approach could be to iterate from n-1 down to n-81 and check directly, as the sum of digits increases slowly with x.

Input:
    n - integer (1 <= n <= 10^9)
Output:
    k - number of valid x values
    k lines with valid x values in ascending order
"""

n = int(input())
# Generate candidates x from n-1 down to max(0, n-81)
# For each candidate x, check if x + sum_of_digits(x) == n
a = [n - i for i in range(min(81, n), 0, -1) if sum(map(int, str(n - i))) + n - i == n]
print(len(a))
if a:
    print(*a)


# https://github.com/VaHiX/CodeForces/