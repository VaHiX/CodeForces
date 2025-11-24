# Problem: CF 1611 F - ATM and Students
# https://codeforces.com/contest/1611/problem/F

"""
Problem: ATM and Students
Purpose: Find the longest contiguous subsequence of students that can be served 
         starting with an initial amount 's' in the ATM, such that the balance 
         never goes negative at any point during the process.

Algorithms/Techniques: Sliding Window Technique
- We use a two-pointer (sliding window) approach to find the maximum valid 
  contiguous subarray where all operations (withdrawals/deposits) keep the 
  balance non-negative.

Time Complexity: O(n) - Each element is visited at most twice (once by right pointer, 
                 once by left pointer).
Space Complexity: O(1) - Only a few variables are used, regardless of input size.

Input:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of students) and s (initial amount in ATM)
  - Line 2: n integers representing a_i (transactions)

Output:
- For each test case:
  - If possible: print the 1-based indices of first and last student in the subsequence
  - If impossible: print -1
"""

for _ in range(int(input())):
    n, s = map(int, input().split())
    a = list(map(int, input().split()))
    l = mx = x = 0
    ans = [-1]

    for r in range(n):
        x += a[r]  # Add current student's transaction to running sum
        # Shrink window from left while the total balance becomes negative
        while l <= r and x + s < 0:
            x -= a[l]
            l += 1
        # Update maximum length and corresponding indices if current window is larger
        if r - l + 1 > mx:
            mx = r - l + 1
            ans = [l + 1, r + 1]

    print(*ans)


# https://github.com/VaHiX/CodeForces/