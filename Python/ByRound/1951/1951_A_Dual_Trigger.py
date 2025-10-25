# Problem: CF 1951 A - Dual Trigger
# https://codeforces.com/contest/1951/problem/A

"""
Algorithm/Techniques: Greedy, String Manipulation

Time Complexity: O(n), where n is the length of the string s. Each operation involves counting 1s and checking for "11" substring, both of which are linear in the length of the string.
Space Complexity: O(n), due to the storage of the input string s.

The problem is to determine if we can turn on lamps in a specific pattern using a special operation: turning on two non-adjacent lamps at a time. 

Key observations:
1. The operation always turns on exactly 2 lamps.
2. Since we're turning on lamps in pairs, the total number of lamps that need to be on must be even. If it's odd, it's impossible.
3. If exactly 2 lamps are to be on, they must not be adjacent (i.e., "11" should not appear in the string).
4. For any even number of lamps turned on (other than 2), we can always achieve it by choosing non-adjacent pairs.
"""

import sys

input = sys.stdin.readline
_ = int(input())
while _ > 0:
    n = int(input())
    s = input()
    one = s.count("1")  # Count total number of lamps that are on
    if one % 2:  # If odd number of lamps are on, impossible to reach with pair operations
        print("NO")
    else:
        if one == 2:  # Special case: exactly two lamps on
            if "11" in s:  # If they are adjacent, impossible to reach with one operation
                print("NO")
            else:
                print("YES")
        else:
            print("YES")  # For any even number of lamps > 2, it's always possible
    _ -= 1


# https://github.com/VaHiX/CodeForces/