# Problem: CF 1931 B - Make Equal
# https://codeforces.com/contest/1931/problem/B

"""
Algorithm: Greedy
Approach:
- Calculate the target average amount of water each container should have.
- Iterate through the containers from left to right, keeping track of the cumulative difference from the average.
- If at any point the cumulative difference becomes negative, it means we cannot fulfill the required distribution, hence return "NO".
- If we complete the iteration without the cumulative difference going negative, return "YES".

Time Complexity: O(n) where n is the number of containers.
Space Complexity: O(1) as we only use a constant amount of extra space.
"""

import sys
from os import path


def input():
    return sys.stdin.readline().strip()


def solve(length, array):
    # If there's only one container, it's always possible to make it equal
    if len(array) < 2:
        return print("YES")
    
    # Check if total water can be equally distributed
    total_num = sum(array)
    if total_num % length != 0:
        return print("NO")
    
    # Calculate the average amount of water each container should have
    average_value = int(total_num / length)
    
    # Keep track of the cumulative excess or deficit of water
    avg_value_in_hand = 0
    
    # Traverse the array from left to right
    for current_value in array:
        # Calculate the difference between current and average
        c_eval = current_value - average_value
        # Accumulate the difference
        avg_value_in_hand += c_eval
        # If we have a deficit (negative value) at any point, it's impossible to distribute
        if avg_value_in_hand < 0:
            return print("NO")
    
    # If we never went negative, it's possible to make all containers equal
    return print("YES")


def main():
    testcases = int(input())
    for _ in range(testcases):
        n = int(input())
        array = list(map(int, input().split()))
        solve(n, array)


if __name__ == "__main__":
    if path.exists("input.txt"):
        sys.stdin = open("input.txt")
        sys.stdout = open("output.txt", "w")
    main()


# https://github.com/VaHiX/CodeForces/