# Problem: CF 2070 C - Limited Repainting
# https://codeforces.com/contest/2070/problem/C

"""
C. Limited Repainting

Algorithm: Binary Search on Answer + Greedy Validation
Time Complexity: O(n * log(max_a)) where max_a is up to 10^9
Space Complexity: O(n)

Approach:
- Use binary search on the answer (penalty value).
- For each candidate penalty, validate whether it's possible to achieve that penalty using at most k operations.
- To validate:
  - We iterate from left to right and simulate painting segments.
  - When we encounter a cell whose penalty exceeds our current threshold, we greedily paint a segment ending there.
  - Count how many such operations are needed.
- The key idea is to determine if there exists a valid way to color the strip with at most k segments such that no cell has penalty greater than the current threshold.

Input:
- t: number of test cases
- For each test case:
  - n: length of strip
  - k: max operations allowed
  - s: desired colors (R/B)
  - a: penalties per cell

Output:
- Minimum achievable penalty
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    s = input()
    a = [int(x) for x in input().split()]
    l = 0
    r = 10**9
    ans = 0
    while r >= l:
        m = (l + r) >> 1  # Binary search mid-point
        last = "R"  # Last color seen, initialized to R
        cnt = 0     # Number of operations used
        for i in range(n):
            if a[i] > m:  # If this cell's penalty exceeds threshold
                if s[i] == "B" and last != "B":  # If desired is blue but previous segment wasn't blue
                    cnt += 1  # Need to start new segment
                last = s[i]  # Update last seen color
        if cnt <= k:  # If operations used are within limit
            ans = m     # This threshold is valid
            r = m - 1   # Try smaller penalty
        else:
            l = m + 1   # Need to increase penalty
    print(ans)


# https://github.com/VaHiX/codeForces/