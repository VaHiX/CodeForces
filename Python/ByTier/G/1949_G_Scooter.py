# Problem: CF 1949 G - Scooter
# https://codeforces.com/contest/1949/problem/G

"""
Algorithm: Greedy approach to assign professors to classes.
Time Complexity: O(n) where n is the number of buildings.
Space Complexity: O(n) for storing the mapping of class and professor combinations.

This solution uses a greedy method to process buildings in order to ensure all 
classes have a corresponding expert professor. It maintains a state of who is on 
the scooter (s) and assigns professors to classes by driving to the appropriate 
buildings, picking up or dropping off professors as needed. 
The algorithm prioritizes matching existing professors to needed classes, and 
if not possible, finds professors in buildings with no class and moves them 
to classes that require experts.

The approach handles:
- Case when a professor's expertise matches a class's subject.
- Case when a professor needs to be moved from a building with no class to one that does.
- Ensures all operations are valid and follow the given constraints.
"""

n = int(input())
c = input().strip()
p = input().strip()
assert len(c) == len(p) == n
# Dictionary to store buildings based on class and professor combination
d = {ci + pi: [] for ci in "-CM" for pi in "-CM"}
for i, (ci, pi) in enumerate(zip(c, p)):
    d[ci + pi].append((i + 1, pi))
s = "-"   # State of scooter (who is on it): "-", "C", or "M"
cmds = [] # List to store commands


def drive(dx):
    # Performs a DRIVE operation and updates the state of the scooter
    i, p = dx.pop()
    cmds.append(f"DRIVE {i}")
    if s != "-":
        cmds.append(f"DROPOFF")
    if p != "-":
        cmds.append(f"PICKUP")
    return p


while True:
    # If scooter has a computer science professor, look for a CS class or building with no class
    if s == "C":
        dx = d["CM"] or d["C-"]
        if dx:
            s = drive(dx)
            continue
    # If scooter has a math professor, look for a Math class or building with no class
    if s == "M":
        dx = d["MC"] or d["M-"]
        if dx:
            s = drive(dx)
            continue
    # Look for a case where we can pick up a professor from a building with no class to place in a class
    dx = d["CM"] or d["C-"]
    if dx and d["-C"]:
        s = drive(d["-C"])  # First move a CS professor from a building with no class
        s = drive(dx)       # Then move that professor to a CS class
        continue
    # Similar logic for a math professor
    dx = d["MC"] or d["M-"]
    if dx and d["-M"]:
        s = drive(d["-M"])  # First move a Math professor from a building with no class
        s = drive(dx)       # Then move that professor to a Math class
        continue
    break  # No more valid operations possible

print(len(cmds))
for cmd in cmds:
    print(cmd)


# https://github.com/VaHiX/CodeForces/