# Problem: CF 1747 A - Two Groups
# https://codeforces.com/contest/1747/problem/A

# Flowerbox
"""
Problem: Maximum Absolute Difference Between Sums of Two Groups
Algorithms/Techniques: Greedy approach
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(1) additional space (not counting input storage)

The problem asks to split an array into two groups such that 
|sum(s1)| - |sum(s2)| is maximized. The key insight is:
- If all numbers are positive, put them all in s1 to maximize |s1| and minimize |s2|
- If all numbers are negative, put them all in s1 to maximize |s1| and minimize |s2|
- If we have both positive and negative numbers, we want to:
  - Put all positive numbers in one group (to maximize sum)
  - Put all negative numbers in the other group (to maximize absolute value of difference)

However, a simpler approach is:
If we calculate total_sum = sum of all numbers,
The answer is |total_sum| because we can always achieve this by:
- Group 1 gets all elements with same sign as total_sum
- Group 2 gets all elements with opposite sign to total_sum (or vice versa)
But in case of mixed signs, the greedy idea simplifies to: 
we should put everything in one group if it's all positive or all negative.
In general, we just need to calculate absolute value of sum since:
We can always make one group have the full sum and other have 0.
"""

# Code with inline comments
for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip header lines)
    print(abs(sum(map(int, s.split()))))  # Convert string to integers, compute sum, take absolute value


# https://github.com/VaHiX/codeForces/