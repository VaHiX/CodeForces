# Problem: CF 1883 F - You Are So Beautiful
# https://codeforces.com/contest/1883/problem/F

"""
Problem: Count subarrays where the subsequence formed by the subarray appears exactly once in the original array.

Approach:
- For each unique element in the array, track how many times it has appeared so far.
- Assign a "weight" to each element based on its occurrence count.
- The total number of valid subarrays is the sum of weights for all unique elements.

Time Complexity: O(n), where n is the length of the array. Each element is processed once.
Space Complexity: O(n), for the dictionary storing the counts of elements.
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    d = {}
    for i in range(n):
        if d.get(a[i]):
            d[a[i]] = len(d)  # Reassign weight to existing element
        else:
            d[a[i]] = len(d) + 1  # Assign new weight to new element
    ans = 0
    for k in d:
        ans += d[k]
    print(ans)


# https://github.com/VaHiX/CodeForces/