# Problem: CF 1799 D2 - Hot Start Up (hard version)
# https://codeforces.com/contest/1799/problem/D2

"""
Purpose: Solve the Hot Start Up problem where we have two CPUs and k programs,
         each with cold and hot run times. We need to find minimum time to execute
         a sequence of programs in order.

Algorithms/Techniques:
- Greedy approach with dynamic programming
- Two-pointer simulation with state tracking
- Optimization of CPU switching costs

Time Complexity: O(n + k) per test case, where n is the length of program sequence and k is number of programs
Space Complexity: O(k) for storing displacement array and other variables
"""

from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    n, k = [int(x) for x in stdin.readline().split()]
    a = [int(x) - 1 for x in stdin.readline().split()]  # Convert to 0-indexed
    cold = [int(x) for x in stdin.readline().split()]
    hot = [int(x) for x in stdin.readline().split()]

    # Initialize the first CPU with first program
    first = a[0]
    second = -1  # This will represent second CPU's current program
    answer = cold[first]  # Time to run first program
    pointer = 1  # Pointer to move through the program sequence
    
    # Assign second CPU to a different program if possible
    while pointer < n:
        if a[pointer] == first:
            # If same program as first CPU, use hot time
            answer += hot[first]
            pointer += 1
        else:
            # Assign second CPU to different program
            second = a[pointer]
            answer += cold[second]  # Cold time for starting program on second CPU
            pointer += 1
            break

    # If second CPU wasn't assigned, just output the time for first CPU
    if second == -1:
        stdout.write(str(answer) + "\n")
    else:
        # Common sum tracks cumulative cost of running second CPU's program on it
        common_sum = 0
        # Displacement array to keep track of optimal time when switching to different CPU
        displacement = [10**15] * k
        displacement[first] = answer  # Base case for first CPU
        global_min = answer  # Global minimum time so far

        # Process remaining programs
        for i in range(pointer, n):
            if a[i] == second:
                # If we're running the same program on second CPU
                common_sum += hot[second]  # Add hot time
                global_min += hot[second]  # Update global minimum
            else:
                # Switch to a different program
                temp = common_sum + displacement[a[i]] + hot[a[i]]
                # Update common_sum and global_min after adding cold time
                common_sum += cold[a[i]]
                global_min += cold[a[i]]
                # Update the displacement for second CPU's previous program
                displacement[second] = min(global_min, temp) - common_sum
                global_min = min(global_min, temp)
                # Reset displacement and update second CPU's new program
                displacement[a[i]] = 10**15
                second = a[i]

        stdout.write(str(global_min) + "\n")


# https://github.com/VaHiX/CodeForces/