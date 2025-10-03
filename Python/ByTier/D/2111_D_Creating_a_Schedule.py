# Problem: CF 2111 D - Creating a Schedule
# https://codeforces.com/contest/2111/problem/D

# ==============================================================================
# Problem: Creating a Schedule
# Algorithm: Greedy arrangement of classroom indices to maximize floor movements
# Time Complexity: O(m log m + n * m) per test case due to sorting and assignment
# Space Complexity: O(m) for storing classrooms and output list
# ==============================================================================

[
    (
        lambda n, m, rooms: print(  # Function takes groups count 'n', rooms count 'm', and sorted room indices
            "\n".join(  # Join all group schedules with newlines
                [
                    (  # For each pair of rooms, assign them to two classes (in both orders)
                        f"{rooms[i]} {rooms[m - i - 1]} " * 3  # First class = room i, second = room m-i-1, repeat 3 times
                        + "\n"
                        + f"{rooms[m - i - 1]} {rooms[i]} " * 3  # Reverse order for next 3 classes
                    )
                    for i in range(n // 2)  # Iterate through half group count to form pairs
                ]
            )
            + (  # If odd number of groups, assign one room in middle
                f"\n{rooms[n // 2]} {rooms[m - (n // 2) - 1]} " * 3  # Middle pair classes
                if n % 2  # Only add extra line if n is odd
                else ""
            )
        )
    )(*map(int, input().split()), sorted(list(map(int, input().split()))))  # Parse and sort room indices
    for _ in range(int(input()))  # Run the procedure for each test case
]


# https://github.com/VaHiX/codeForces/