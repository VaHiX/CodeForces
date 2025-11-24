# Problem: CF 2030 A - A Gift From Orangutan
# https://codeforces.com/contest/2030/problem/A

"""
Problem: Maximum Score from Array Shuffle

Purpose:
  Given an array 'a' of length n, we construct two arrays 'b' and 'c' where:
    - b[i] = min(a[0], ..., a[i])
    - c[i] = max(a[0], ..., a[i])
  The score is the sum of (c[i] - b[i]) for all i.
  We can shuffle the array 'a' to maximize this score.

Approach:
  To maximize the score, we should try to make the difference (c[i] - b[i]) as large as possible.
  For any prefix, c[i] - b[i] represents how much larger the maximum is compared to the minimum so far.
  The optimal strategy is to place the largest elements early in the array to maximize the differences.

  Observation:
    If we sort the array and then rearrange the elements such that the largest element comes first,
    followed by the second largest, etc., we can ensure that at each step, c[i] = max of current prefix
    while b[i] = min of current prefix.
  
Algorithm:
  In the optimal arrangement:
    - First element is the maximum
    - Second element is the minimum (to minimize b[1])
    - Third element is next maximum or second minimum, etc.
    
  However, a simpler greedy idea works:
    The total score will always be (n - 1) * (max(a) - min(a)), since we want to maximize
    difference at each step by placing the greatest and smallest elements at strategic positions.

Time Complexity: O(n)
Space Complexity: O(1)

"""

for t in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    # The maximum possible score is (n - 1) * (max(a) - min(a))
    print((n - 1) * (max(a) - min(a)))


# https://github.com/VaHiX/codeForces/