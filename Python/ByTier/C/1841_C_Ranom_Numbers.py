# Problem: CF 1841 C - Ranom Numbers
# https://codeforces.com/contest/1841/problem/C

"""
Algorithm: 
    - For each position in the string, we compute the maximum possible value by trying to 
      change that digit to any other digit (A to E), or leaving it as is.
    - The value of a Ranom number is calculated considering signs:
        - A digit is positive if no greater digit appears to its right.
        - A digit is negative if a greater digit appears to its right.
    - We precompute for each digit (A-E) the first and last occurrence.
    - Then we try changing the first and last positions of each digit to another digit 
      that would lead to a better final result.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) since we use fixed size arrays (5 digits only).
"""

from sys import stdin


def solve(s):
    n = len(s)
    s = list(map(lambda x: ord(x) - ord("A"), s))

    def cal(i, c):
        # Function to calculate value of string with digit at index i changed to c
        nums = s.copy()
        nums[i] = c
        sign = [0] * n
        rightmax = 0
        res = 0
        for i in range(n - 1, -1, -1):
            if nums[i] >= rightmax:
                rightmax = nums[i]
            sign[i] = rightmax
            if nums[i] < sign[i]:
                res -= 10 ** nums[i]
            else:
                res += 10 ** nums[i]
        return res

    # Precompute first and last occurrence of each digit (A-E)
    appear = [[float("inf"), -1] for _ in range(5)]
    for i in range(n):
        fir, las = appear[s[i]]
        appear[s[i]] = [min(i, fir), max(las, i)]
    
    # Initialize result with current value (no change)
    ans = cal(0, s[0])
    
    # Try changing first and last occurrences to see if we get a better value
    for i in range(5):
        for j in range(5):
            if j < i and appear[i][1] >= 0:
                # Try changing last occurrence of digit i to digit j
                ans = max(ans, cal(appear[i][1], j))
            elif j > i and appear[i][0] < n:
                # Try changing first occurrence of digit i to digit j
                ans = max(ans, cal(appear[i][0], j))
    return ans


for _ in range(int(input())):
    s = stdin.readline()[:-1]
    print(solve(s))


# https://github.com/VaHiX/CodeForces/