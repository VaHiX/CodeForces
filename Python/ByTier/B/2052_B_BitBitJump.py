# Problem: CF 2052 B - BitBitJump
# https://codeforces.com/contest/2052/problem/B

# BitBitJump x-comparator generator
# Algorithms/Techniques: Bit manipulation, simulation of BBJ instruction set
# Time Complexity: O(1) - Fixed size input (16 bits) and output (2^12 words)
# Space Complexity: O(1) - Fixed memory usage for all operations

GROUP_SIZE = 4 * 4
ZERO = GROUP_SIZE * 16 * 16
ONE = GROUP_SIZE * 17 * 16
QUIT = GROUP_SIZE * 18
WIN = GROUP_SIZE * 19


def get(x, b):
    # Extract the b-th bit from x (0 or 1)
    return (x >> b) & 1


def f(x):
    # Convert integer to 4-digit hex string
    s = hex(x)[2:]
    while len(s) < 4:
        s = "0" + s
    return s


def main():
    x = int(input())
    data = []
    # Loop through each bit of the input (16 bits total)
    for i in range(16):
        start = GROUP_SIZE * i
        nextt = GROUP_SIZE * (i + 1) if i != 15 else WIN
        # Instruction 1: Set up memory to copy bit at position 6 into current instruction's bit 2
        data.extend([0xFFF0 + i, (start + 6) * 16 + 2, start + 4, 0])
        # Instruction 2: Same setup as above but for another location
        data.extend([0, 0, start + 8, 0])
        # Instruction 3: Copy bit from input word based on bit value (0 or 1)
        data.extend([0, 0, nextt if get(x, i) == 0 else QUIT, 0])
        # Instruction 4: Same as above, but reversed path for checking current bit
        data.extend([0, 0, nextt if get(x, i) == 1 else QUIT, 0])
    # Padding for program size to align with memory layout requirements
    data.extend([0x0000, 0x0000, 0x0000, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])
    # Termination block: set final state
    data.extend([0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF])
    for _ in range(3):
        data.extend([0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF])
    # Preparing zero-comparator instruction pattern (copy 0 from word 0 to IO-word)
    data.extend([ZERO, 0xFFF0, 0x0FFF, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])
    # Preparing one-comparator instruction pattern (copy 1 from word 0 to IO-word)
    data.extend([ONE, 0xFFF0, 0x0FFF, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])
    print(*list(map(f, data)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/