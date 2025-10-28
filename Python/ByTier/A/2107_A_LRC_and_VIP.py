# Problem: CF 2107 A - LRC and VIP
# https://codeforces.com/contest/2107/problem/A

"""
Task: Split an array into two sequences such that their GCDs are different.

Algorithms/Techniques: Greedy approach with special case handling.
Time Complexity: O(n), where n is the size of the input array (due to single pass operations).
Space Complexity: O(n), for storing the input and output arrays.

The solution works as follows:
- If all elements are equal, it's impossible to split into two groups with different GCDs.
- Otherwise, we place the maximum element in group 2, and others in group 1,
  ensuring that gcd of group 1 will be different from gcd of group 2.
"""

for _ in range(int(input())):
    a = int(input())
    b = list(map(int, input().split()))
    dp = [1] * a  # Initialize all elements to group 1
    q = b.index(max(b))  # Find index of maximum element
    dp[q] = 2  # Place maximum element in group 2
    if len(set(b)) == 1:  # If all elements are same, no valid split possible
        print("No")
    else:
        print("Yes")
        print(*dp)  # Output the assignment of groups


# https://github.com/VaHiX/codeForces/