# Problem: CF 1585 A - Life of a Flower
# https://codeforces.com/contest/1585/problem/A

"""
A. Life of a Flower
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Petya has got an interesting flower. Petya is a busy person, so he sometimes forgets to water it. You are given n days from Petya's live and you have to determine what happened with his flower in the end.

The flower grows as follows: 
 - If the flower isn't watered for two days in a row, it dies. 
 - If the flower is watered in the i-th day, it grows by 1 centimeter. 
 - If the flower is watered in the i-th and in the (i-1)-th day (i > 1), then it grows by 5 centimeters instead of 1. 
 - If the flower is not watered in the i-th day, it does not grow. 

At the beginning of the 1-st day the flower is 1 centimeter tall. What is its height after n days?

Algorithms/Techniques:
- Linear scan through the array of watering events
- State tracking: current height, previous watering status

Time Complexity: O(n) where n is the number of days
Space Complexity: O(1) - only using a few variables for tracking
"""

for _ in range(int(input())):  # Process multiple test cases
    n = int(input())  # Read number of days
    x = list(map(int, input().split()))  # Read watering status for each day (0 or 1)
    h = 1  # Initial height of the flower is 1 cm
    
    # If the first day is watered, add 1 cm to height
    if x[0] == 1:
        h += 1
    
    # Iterate through the rest of the days starting from index 1
    for i in range(1, n):
        # If current day is watered and previous day was also watered, grow by 5 cm
        if x[i] == 1 and x[i - 1] == 1:
            h += 5
        # If current day is watered but previous was not, grow by 1 cm
        elif x[i] == 1:
            h += 1
        # If current day is not watered and previous day was also not watered, flower dies
        elif x[i] != 1 and x[i - 1] != 1:
            h = -1
            break
    
    print(h)  # Output final height or -1 if flower died


# https://github.com/VaHiX/codeForces/