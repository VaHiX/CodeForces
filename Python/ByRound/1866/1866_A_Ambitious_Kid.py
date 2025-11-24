# Problem: CF 1866 A - Ambitious Kid
# https://codeforces.com/contest/1866/problem/A

"""
Task: Make the product of all elements in the array equal to 0 with minimum operations.
Each operation allows increasing or decreasing any element by 1.

Algorithm: 
- The product of array elements becomes 0 if and only if at least one element is 0.
- To minimize operations, we need to make at least one element equal to 0.
- The minimum number of operations required is the minimum absolute value in the array,
  because we can change the element with the smallest absolute value to 0 with that many steps.

Time Complexity: O(n), where n is the number of elements in the array.
Space Complexity: O(1), only using a constant amount of extra space.

"""
input()
a = list(map(int, input().split()))
print(abs(min(a, key=abs)))


# https://github.com/VaHiX/CodeForces/