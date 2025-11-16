# Problem: CF 891 A - Pride
# https://codeforces.com/contest/891/problem/A

"""
Algorithm: Minimum Operations to Make All Elements Equal to 1
Techniques: GCD computation, greedy approach, brute-force search

Time Complexity: O(n^2 * log(max(a)))
Space Complexity: O(1)

The solution works as follows:
1. If there's already a '1' in the array, we can convert the rest of the elements to 1 in (n - count_of_1) steps.
2. Otherwise, we search for the shortest subarray whose GCD is 1. 
   The minimum operations needed is n + (length_of_shortest_gcd_1_subarray - 1).
3. If no such subarray exists, return -1.
"""

import math

n = int(input())
a = list(map(int, input().split()))
ans, cnt = n, a.count(1)  # ans initialized to n, cnt counts occurrences of 1

# Loop through all possible subarrays to find the shortest one with GCD = 1
for i in range(n):
    m = a[i]  # Start with first element of subarray
    for j in range(i + 1, n):
        m = math.gcd(m, a[j])  # Compute GCD incrementally
        if m == 1:
            # Found a subarray with GCD = 1, update minimum operations
            ans = min(ans, j - i - 1)
            break  # No need to extend further since GCD will be 1

# If there's already a 1 present, minimum operations = n - cnt
if cnt > 0:
    print(n - cnt)
# If no subarray with GCD = 1 found, impossible to make all 1s
elif ans == n:
    print(-1)
# Otherwise, use the shortest subarray found
else:
    print(n + ans)


# https://github.com/VaHiX/CodeForces/