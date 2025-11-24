# Problem: CF 2166 A - Same Difference
# https://codeforces.com/contest/2166/problem/A

"""
Algorithm: Greedy
The problem asks us to make all characters in a string the same with minimum operations,
where each operation allows changing a character to the next character in the alphabet.

Key Insight:
To minimize operations, we should convert all characters to the last character of the string.
This is because converting characters to a later character in the alphabet requires fewer operations
than converting to an earlier one, assuming we want to minimize total steps.

Approach:
- Count how many characters are already equal to the last character of the string.
- The number of operations needed is the total length minus this count,
  since we convert all other characters to match the last character.

Time Complexity: O(n), where n is the length of the string. We iterate through the string once to count.
Space Complexity: O(1), constant extra space used.

Techniques: Greedy, String manipulation
"""
for _ in range(int(input())):
    n = int(input())
    s = input()
    print(n - s.count(s[-1]))  # Count of characters equal to the last character


# https://github.com/VaHiX/CodeForces/