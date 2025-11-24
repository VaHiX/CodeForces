# Problem: CF 1928 B - Equalize
# https://codeforces.com/contest/1928/problem/B

"""
Algorithm: Sliding Window on Sorted Unique Elements
Purpose: To find the maximum number of elements that can become equal after adding a permutation.
Time Complexity: O(n log n) due to sorting; sliding window is O(n)
Space Complexity: O(n) for storing unique elements

The approach:
1. Convert input array into a set to get unique values
2. Sort the unique values
3. Use a sliding window technique:
   - For each element, ensure that the difference between current and leftmost element in window is less than n
   - This ensures that we can add a permutation (values 1 to n) to make all elements in window equal
   - Track maximum size of such valid window

Example:
For array [7, 1, 4, 1], unique elements are [1, 4, 7]
Sorted: [1, 4, 7]
Window analysis:
- i=0, val=1, pnt=0. diff = 1-1 = 0 < 4 => window size = 1-0+1 = 1
- i=1, val=4, pnt=0. diff = 4-1 = 3 < 4 => window size = 2-0+1 = 2  
- i=2, val=7, pnt=0. diff = 7-1 = 6 >= 4 => increment pnt=1
  Now diff = 7-4 = 3 < 4 => window size = 2-1+1 = 2
Maximum window size = 2
"""

def solve():
    n = int(input())
    a = set(map(int, input().split()))
    a = sorted(a)
    ans = pnt = 0
    for i, val in enumerate(a):
        while val - a[pnt] >= n:
            pnt += 1
        ans = max(ans, i - pnt + 1)
    print(ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/