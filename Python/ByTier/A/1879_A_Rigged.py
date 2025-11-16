# Problem: CF 1879 A - Rigged!
# https://codeforces.com/contest/1879/problem/A

"""
Purpose: 
This code solves a problem where Monocarp wants to choose a barbell weight 'w' such that 
his friend Polycarp (the first athlete) wins the competition. 
Each athlete has strength (s) and endurance (e). 
An athlete can lift the barbell 'e' times if s >= w, otherwise 0 times.
The goal is to find a weight 'w' where Polycarp lifts more times than any other athlete.
If impossible, return -1.

Algorithms/Techniques:
- Greedy approach: Check if there exists a weight w such that Polycarp's endurance 
  is strictly greater than all other athletes' endurance, when they can lift the barbell.
- If any other athlete has both strength >= Polycarp's strength and endurance >= Polycarp's endurance,
  then it's impossible for Polycarp to win.
  
Time Complexity: O(n), where n is the number of athletes.
Space Complexity: O(n), for storing athlete data.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return list(s[: len(s) - 1])


def invr():
    return map(int, input().split())


for _ in range(inp()):  # Process each test case
    n = inp()  # Number of athletes
    a = []  # Store athlete data
    for _ in range(n):
        s, e = invr()  # Read strength and endurance
        a.append([s, e])
    
    x, y = a[0][0], a[0][1]  # Polycarp's strength and endurance
    
    f = 1  # Flag to check if a valid w exists
    
    # Check if any other athlete can match or beat Polycarp in both strength and endurance
    for i in range(1, n):
        if a[i][0] >= x and a[i][1] >= y:  # If another athlete is stronger or equal in both stats
            print(-1)
            f = 0
            break
    
    if f == 1:  # If no one can beat Polycarp in all stats
        print(x)  # Return Polycarp's strength as a possible w value


# https://github.com/VaHiX/CodeForces/