# Problem: CF 1499 B - Binary Removals
# https://codeforces.com/contest/1499/problem/B

"""
Algorithm: Binary Removals

The problem asks whether we can remove some non-adjacent characters from a binary string 
such that the remaining string is sorted (i.e., all 0's come before all 1's).

Key insight:
- If the string is already sorted (all 0's followed by all 1's), then we can simply return YES.
- Otherwise, we look for a pattern:
    - Find the first occurrence of "00" in "00" + s (this represents a case where there are two
      consecutive 0's).
    - Find the first occurrence of "11" in s + "11" (this represents a case where there are two
      consecutive 1's).
    - If there are no "00" in "00" + s, or no "11" in s + "11", then we can always rearrange 
      the string to be sorted by removing appropriate characters.
    
Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(n) due to string concatenation operations.
"""

for _ in range(int(input())):
    s = input()
    # Check if there exists a valid sequence of removals to make string sorted
    # If first "00" in "00" + s comes before first "11" in s + "11", then it's possible
    if f"00{s }".rfind("00") < f"{s }11".find("11") + 2:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/