# Problem: CF 1677 A - Tokitsukaze and Strange Inequality
# https://codeforces.com/contest/1677/problem/A

"""
Algorithm: Two-pointer with prefix counting
Techniques: 
- Dynamic programming with counting
- Reverse iteration with suffix processing
- Efficient counting using dp array to track elements greater than current

Time Complexity: O(n^2) where n is the length of the permutation
Space Complexity: O(n) for the dp array

This solution counts valid tuples [a,b,c,d] such that p_a < p_c and p_b > p_d
by iterating from right to left and maintaining a count of elements greater
than the current element to efficiently compute the number of valid combinations.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    dp = [0] * n
    ans = 0
    for i in range(n - 1, -1, -1):  # Iterate from right to left
        cnt = 0
        for j in range(i - 1, -1, -1):  # Iterate from i-1 to 0
            if arr[j] < arr[i]:  # If p_j < p_i, we found valid pairs for c,d
                ans += cnt  # Add number of valid (c,d) pairs we've seen so far
            cnt += dp[j]  # Add to cnt the number of elements > p_j seen so far
            if arr[j] > arr[i]:  # If p_j > p_i, update dp to count this
                dp[j] += 1
    print(ans)


# https://github.com/VaHiX/CodeForces/