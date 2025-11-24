# Problem: CF 1980 B - Choosing Cubes
# https://codeforces.com/contest/1980/problem/B

"""
Algorithm/Techniques: Sorting, Greedy, Comparison
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

This solution determines whether a specific cube (the favorite one) will definitely be removed,
definitely not be removed, or might be either depending on the sorting order.
The key idea is to sort the array in non-increasing order and compare the value of the favorite cube 
with the k-th largest value. If the favorite cube's value is less than the k-th largest,
it's definitely removed. If it's greater, it's definitely not removed. If equal, we need to check 
if there are other cubes with the same value at position k to determine if it might or must be removed.
"""

import sys


def main():
    test = int(sys.stdin.readline())
    while test > 0:

        n, f, k = map(int, sys.stdin.readline().split())

        arr = list(map(int, sys.stdin.readline().split()))

        fav = arr[f - 1]  # Get value of favorite cube (1-indexed)

        arr.sort(reverse=True)  # Sort in non-increasing order

        if fav < arr[k - 1]:  # If favorite cube value is less than k-th largest
            print("NO")  # It will definitely be removed

        elif fav == arr[k - 1]:  # If favorite cube value equals k-th largest
            if n > k and arr[k] == arr[k - 1]:  # If there are more elements and next one is same
                print("MAYBE")  # May or may not be removed
            else:
                print("YES")  # It will definitely be removed

        else:  # If favorite cube value is greater than k-th largest
            print("YES")  # It will definitely not be removed

        test -= 1


main()


# https://github.com/VaHiX/CodeForces/