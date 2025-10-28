# Problem: CF 1955 B - Progressive Square
# https://codeforces.com/contest/1955/problem/B

"""
Purpose: Determine if a given array of n^2 integers can form a progressive square
         based on specific rules involving parameters c and d.

Algorithms/Techniques:
- Sort the array and use properties of progressive square to verify if it's valid
- Check if the sum of elements from both ends equals a fixed value (s)
- Validate the minimum and maximum values in the sequence match the expected range

Time Complexity: O(n^2 * log(n^2)) due to sorting
Space Complexity: O(n^2) for storing the array of elements

The progressive square follows these rules:
a[i+1][j] = a[i][j] + c
a[i][j+1] = a[i][j] + d

For a valid progressive square, the elements must satisfy:
- Minimum element is a[1][1]
- Maximum element is a[1][1] + (n-1)*(c+d)
- Elements can be paired such that each pair sums to a constant value
- The sequence of sums is symmetric around the middle element if n is odd
"""

def check():
    x2.sort()  # Sort the input array to test for symmetric properties
    mi = x2[0]  # Get the minimum element
    ma = mi + (n - 1) * (c + d)  # Calculate expected maximum based on formula
    if ma != x2[len(x2) - 1]:  # If calculated max doesn't match actual max, invalid
        return False
    l = 0  # Left pointer
    r = len(x2) - 1  # Right pointer
    s = x2[l] + x2[r]  # Sum of outermost elements, which should be consistent
    l += 1  # Move left pointer inward
    r -= 1  # Move right pointer inward
    while l < r:  # While pointers haven't met
        if x2[l] + x2[r] != s:  # If current pair doesn't match sum, invalid
            return False
        l += 1  # Move inward
        r -= 1
    if l == r:  # If pointers meet (odd number of elements)
        if x2[l] != s // 2:  # Middle element must be half of sum
            return False
    return True  # If all checks passed, valid


if __name__ == "__main__":
    for _ in range(int(input())):  # Process each test case
        x1 = list(map(int, input().split()))  # Read n, c, d
        x2 = list(map(int, input().split()))  # Read array of n^2 elements
        n = x1[0]
        c = x1[1]
        d = x1[2]
        if check():  # Check if current array forms a valid progressive square
            print("YES")
        else:
            print("NO")


# https://github.com/VaHiX/CodeForces/