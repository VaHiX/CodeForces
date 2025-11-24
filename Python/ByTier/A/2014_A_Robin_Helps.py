# Problem: CF 2014 A - Robin Helps
# https://codeforces.com/contest/2014/problem/A

"""
Task: Robin Helps

Algorithm/Technique: Greedy approach with simulation
Time Complexity: O(n) per test case, where n is the number of people
Space Complexity: O(1) additional space (excluding input storage)

Robin Hood traverses people from left to right:
- If a person has >= k gold, Robin takes all of it (accumulates in 'z')
- If a person has 0 gold and Robin has some gold ('z' > 0), Robin gives 1 gold
- Count how many people received gold from Robin

This greedy simulation ensures that Robin takes the maximum available gold 
and gives gold to as many people as possible when he has any.
"""

for t in range(int(input())):  # Process each test case
    n, k = map(int, input().split())  # Read number of people and threshold
    a = list(map(int, input().split()))  # Read gold amounts for each person
    z = 0  # Accumulated gold Robin has
    c = 0  # Count of people who received gold from Robin
    for i in a:  # For each person in order
        if i >= k:  # If person has enough gold to be taken by Robin
            z += i  # Robin takes all gold from this person
        elif i == 0 and z > 0:  # If person has no gold and Robin has some
            z -= 1  # Robin gives 1 gold
            c += 1  # Increment count of people helped
    print(c)  # Output total people helped in this test case


# https://github.com/VaHiX/codeForces/