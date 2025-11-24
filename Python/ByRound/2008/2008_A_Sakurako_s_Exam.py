# Problem: CF 2008 A - Sakurako's Exam
# https://codeforces.com/contest/2008/problem/A

"""
Problem: Sakurako's Exam
Algorithm/Technique: Mathematical analysis of sign assignment to achieve zero sum.

Task:
Given an array of 'a' ones and 'b' twos, determine if it's possible to assign '+' or '-' signs 
to each element such that the total sum equals zero.

Approach:
- Let S1 = sum of all 1s = a * 1 = a
- Let S2 = sum of all 2s = b * 2 = 2*b
- Total sum without signs = S1 + S2 = a + 2*b
- To make total sum zero, we need to split the elements into two groups where one group's sum equals 
  the other group's sum.
- If S = a + 2*b is odd, it's impossible to split into two equal parts → return NO
- If S is even, we need to check if there exists a subset with sum S/2:
    - For this to be possible, we must be able to represent (S/2) using 1s and 2s.
    - Since 2s make it hard to get specific small sums, only when 'a' is even can we pair up 1s.
- Further observation:
    - Even 'a': Any amount of 2s can be used to reach a target sum
    - Odd 'a': We must use an even number of 2s to keep the remaining part even for pairing

Key insight:
- The final result is determined by parity (odd/even) checks.
- If a is odd OR if a=0 and b is odd, then it's impossible.
- If a is even AND b is any value, then it's possible.

Time Complexity: O(1)
Space Complexity: O(1)

Sample Input:
5
0 1
0 3
2 0
2 3
3 1

Sample Output:
NO
NO
YES
YES
NO
"""

for _ in range(int(input())):  # Loop through test cases
    a, b = map(int, input().split())  # Read number of 1s and 2s
    # If 'a' is odd OR 'a' is 0 and 'b' is odd, return "NO"
    print("NO" if a & 1 or not a and b & 1 else "YES")


# https://github.com/VaHiX/codeForces/