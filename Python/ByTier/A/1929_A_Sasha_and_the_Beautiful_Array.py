# Problem: CF 1929 A - Sasha and the Beautiful Array
# https://codeforces.com/contest/1929/problem/A

"""
Problem: Sasha and the Beautiful Array
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(n) per test case, due to storing the array elements

The beauty of the array is defined as the sum of (a[i] - a[i-1]) for all i from 2 to n.
To maximize this sum, we want to maximize the differences between consecutive elements.
The optimal arrangement is to place the largest and smallest elements at the ends,
which maximizes the total difference. Hence, the maximum beauty = max_element - min_element.
"""

def takeintinput():
    arr = input().split()
    arr = [int(i) for i in arr]
    return arr


def solve():
    takeintinput()[0]  # Read n, but we don't use it
    arr = takeintinput()  # Read the array elements
    maxi = 0
    mini = arr[0]
    for i in arr:
        maxi = max(maxi, i)  # Track maximum element
        mini = min(mini, i)  # Track minimum element
    print(maxi - mini)  # Print the maximum beauty


for i in range(int(input())):  # Process each test case
    solve()


# https://github.com/VaHiX/CodeForces/