# Problem: CF 2169 B - Drifting Away
# https://codeforces.com/contest/2169/problem/B

"""
Algorithm: Simulation with pattern recognition
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a few variables for counting and checking

Approach:
- The key insight is to detect infinite loops by looking for certain patterns:
  - "><" means a rightward current at position i and a leftward current at position i+1, 
    causing a back-and-forth motion.
  - "**" means two consecutive no-current cells, which can allow for infinite movement 
    if the path allows it.
  - "*<" or ">*" suggests a no-current cell adjacent to a current direction, 
    potentially enabling infinite looping.

- If any of these patterns are found, Monocarp can drift infinitely → return -1.

- Otherwise, traverse the string to simulate movement:
  1. Count number of '<' (leftward) and '>' (rightward) currents.
  2. If all cells have currents: return the maximum of left or right currents.
  3. If there are no-current cells '*', then one additional step can be taken to reach a 
     shore, so add 1 to the max of currents.

Sample Input-Output:
Input:
4
*****
< << >
>*<
*
Output:
-1
3
-1
1
"""

for _ in range(int(input())):
    s = input()
    n = len(s)

    # Check for patterns that lead to infinite drift
    if "><" in s or "**" in s:
        print(-1)
    elif "*<" in s or ">*" in s:
        print(-1)
    else:
        # Count left and right currents
        l = s.count("<")
        r = s.count(">")
        if l + r == n:
            # All cells have currents, simulate max drift time
            print(max(l, r))
        else:
            # Some cells are '*', simulate extended path
            print(max(l, r) + 1)


# https://github.com/VaHiX/CodeForces/