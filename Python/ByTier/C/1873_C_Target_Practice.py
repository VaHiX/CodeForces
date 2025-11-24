# Problem: CF 1873 C - Target Practice
# https://codeforces.com/contest/1873/problem/C

"""
Target Practice Problem

Algorithms/Techniques:
- Iterative scanning of 10x10 grid
- For each row, determine ring value based on column index
- Each ring has a fixed point value (1 to 5)
- Time complexity: O(1) per test case (fixed 100 characters), Space complexity: O(1)

Time complexity: O(1) per test case
Space complexity: O(1)
"""

def readl1():
    points = 0
    line1 = input()
    for square in line1:  # Iterate through each character in the line
        if square == "X":  # If there's an arrow
            points += 1  # Outermost ring gives 1 point
    return points


def readl2():
    points = 0
    line2 = input()
    for i, square in enumerate(line2):  # Enumerate to get both index and value
        if square == "X":  # If there's an arrow
            if i in [0, 9]:  # First or last column -> outermost ring
                points += 1
            else:  # Middle columns -> second ring
                points += 2
    return points


def readl3():
    points = 0
    line3 = input()
    for i, square in enumerate(line3):
        if square == "X":  # If there's an arrow
            if i in [0, 9]:  # First or last column -> outermost ring
                points += 1
            elif i in [1, 8]:  # Second or ninth column -> second ring
                points += 2
            else:  # Middle columns -> third ring
                points += 3
    return points


def readl4():
    points = 0
    line4 = input()
    for i, square in enumerate(line4):
        if square == "X":  # If there's an arrow
            if i in [0, 9]:  # First or last column -> outermost ring
                points += 1
            elif i in [1, 8]:  # Second or ninth column -> second ring
                points += 2
            elif i in [2, 7]:  # Third or eighth column -> third ring
                points += 3
            else:  # Middle columns -> fourth ring
                points += 4
    return points


def readl5():
    points = 0
    line5 = input()
    for i, square in enumerate(line5):
        if square == "X":  # If there's an arrow
            if i in [0, 9]:  # First or last column -> outermost ring
                points += 1
            elif i in [1, 8]:  # Second or ninth column -> second ring
                points += 2
            elif i in [2, 7]:  # Third or eighth column -> third ring
                points += 3
            elif i in [3, 6]:  # Fourth or seventh column -> fourth ring
                points += 4
            else:  # Middle columns -> center ring
                points += 5
    return points


tests = int(input())
for test in range(tests):
    points = 0
    points += readl1()  # Process first row
    points += readl2()  # Process second row
    points += readl3()  # Process third row
    points += readl4()  # Process fourth row
    points += readl5()  # Process fifth row
    points += readl5()  # Process sixth row (mirror of fifth)
    points += readl4()  # Process seventh row (mirror of fourth)
    points += readl3()  # Process eighth row (mirror of third)
    points += readl2()  # Process ninth row (mirror of second)
    points += readl1()  # Process tenth row (mirror of first)
    print(points)


# https://github.com/VaHiX/CodeForces/