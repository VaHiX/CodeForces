# Problem: CF 1878 A - How Much Does Daytona Cost?
# https://codeforces.com/contest/1878/problem/A

"""
Problem: Determine if there exists a subsegment where k is the most common element.

Algorithm/Technique: 
- For each test case, we check if k is present in the array.
- If k is present, we check all possible subsegments to see if k can be the most common element.
- However, the simple approach of just checking if k is in the array is sufficient for this problem's constraints,
  since if k is present, we can always form a subsegment where k appears more times than others,
  for example, by taking k alone as a subsegment if k occurs at least once.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1) additional space, not counting input storage.

"""

num = int(input())
ls = []
for i in range(num):
    n, k = map(int, input().split())
    mylist = list(input().split())
    # Check if k is present in the array
    if str(k) in mylist:
        ls.append("YES")
    else:
        ls.append("NO")
for i in range(num):
    print(ls[i])


# https://github.com/VaHiX/CodeForces/