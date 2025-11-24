# Problem: CF 1730 C - Minimum Notation
# https://codeforces.com/contest/1730/problem/C

"""
Algorithm: Greedy approach to minimize lexicographically
Techniques: 
- Reverse traversal to track minimum digit seen so far
- For each digit, decide whether to keep it or increment it (with max 9)
- Sort the final result to get lexicographically smallest string

Time Complexity: O(n log n) due to sorting operation where n is the length of string
Space Complexity: O(n) for storing the answer list

The key idea is to traverse the string from right to left, keeping track of the minimum digit encountered so far.
For each digit, if it's less than or equal to the current minimum, we keep it as is.
Otherwise, we increment it by 1 (capped at 9) and append to the result.
Finally, sort the result to get the lexicographically smallest arrangement.
"""

for _ in range(int(input())):
    s = input()
    m = s[-1]  # Initialize minimum with last digit
    ans = []
    for i in reversed(s):  # Traverse from right to left
        m = min(i, m)  # Update minimum digit seen so far
        # If current digit is <= minimum, keep it
        # Else increment it by 1 (max 9) and append
        ans.append(i if i <= m else str(min(int(i) + 1, 9)))
    print("".join(sorted(ans)))  # Sort and print final result


# https://github.com/VaHiX/CodeForces/