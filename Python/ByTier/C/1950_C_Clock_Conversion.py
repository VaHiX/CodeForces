# Problem: CF 1950 C - Clock Conversion
# https://codeforces.com/contest/1950/problem/C

"""
Convert 24-hour format time to 12-hour format.

Algorithms/Techniques:
- Parse the input string to extract hours and minutes.
- Determine the period (AM/PM) based on the hour value.
- Adjust the hour for 12-hour format:
  - Hours 00 become 12 (AM)
  - Hours 13-23 are reduced by 12
  - Hours 01-12 remain unchanged (except 00 which becomes 12)
- Format the result with leading zeros using f-string formatting.

Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1), as we use a constant amount of extra space per test case.
"""

def convert_time(time_str):
    hours, minutes = map(int, time_str.split(":"))  # Split and convert to integers
    period = "AM" if hours < 12 else "PM"  # Determine AM/PM based on hour
    if hours == 0:
        hours = 12  # Midnight case: 00 becomes 12
    elif hours > 12:
        hours -= 12  # Convert 13-23 to 1-11
    return f"{hours:02d}:{minutes:02d} {period}"  # Format with leading zeros


t = int(input())
for _ in range(t):
    time_str = input()
    print(convert_time(time_str))


# https://github.com/VaHiX/CodeForces/