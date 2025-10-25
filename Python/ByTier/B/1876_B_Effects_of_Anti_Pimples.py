# Problem: CF 1876 B - Effects of Anti Pimples
# https://codeforces.com/contest/1876/problem/B

"""
Algorithm: 
- For each index i, we compute the maximum value among all elements at positions that are multiples of (i+1), i.e., a[i], a[2*i+1], a[3*i+1], ...
- We then sort these max values.
- For each value in the sorted list, we multiply it by 2^k where k is the number of subsets that include this value in their black indices, and accumulate the result.
Time Complexity: O(n log n)
Space Complexity: O(n)
"""

n = int(input())
a = list(map(int, input().split()))
ans = 0
for i in range(n):
    # Compute maximum value among all multiples of (i+1)
    a[i] = max(a[i :: i + 1])
a.sort()
mn = 1
for x in a:
    # Multiply current value by number of valid subsets (2^k) and add to answer
    ans += x * mn
    ans %= 998244353
    mn *= 2  # Update multiplier for next iteration
    mn %= 998244353
print(ans)


# https://github.com/VaHiX/CodeForces/