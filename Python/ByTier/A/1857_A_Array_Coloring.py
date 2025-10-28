# Problem: CF 1857 A - Array Coloring
# https://codeforces.com/contest/1857/problem/A

"""
Algorithm: Array Coloring
Techniques: Parity check, counting odd numbers

Time Complexity: O(n) where n is the length of the array. We iterate through the array once to count odd numbers.
Space Complexity: O(1) as we only use a constant amount of extra space (the variable 'c' for counting).

The approach is based on the observation that:
- For two subsets to have the same parity in their sums, 
  the total count of odd numbers in the array must be even.
- This is because odd numbers contribute 1 to the parity of the sum,
  and even numbers do not affect the parity.
- If there are an even number of odd numbers, we can split them into two groups
  such that each group's sum has the same parity (both even or both odd).
"""

for _ in range(int(input())):
    n = int(input())
    lst = list(map(int, input().split()))
    c = 0
    for i in lst:
        if i % 2 != 0:  # Check if the number is odd
            c += 1
    print("YES" if c % 2 == 0 else "NO")  # If count of odd numbers is even, possible to split


# https://github.com/VaHiX/CodeForces/