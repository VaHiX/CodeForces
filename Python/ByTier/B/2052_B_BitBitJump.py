# Contest 2052, Problem B: BitBitJump
# URL: https://codeforces.com/contest/2052/problem/B

## 16 blocks of size 3 * 4 * 16 bits
## 0x0000 0xffff 0x000, then 3 groups of 3 of all zeros
## quit gadget (4 blocks)
## win gadget (4 blocks)

# counts only # of 16 bit blocks
GROUP_SIZE = 4 * 4

# bit indices
ZERO = GROUP_SIZE * 16 * 16
ONE = GROUP_SIZE * 17 * 16

QUIT = GROUP_SIZE * 18
WIN = GROUP_SIZE * 19


def get(x, b):
    return (x >> b) & 1


def f(x):
    s = hex(x)[2:]
    while len(s) < 4:
        s = "0" + s
    return s


def main():
    x = int(input())
    data = []
    for i in range(16):
        start = GROUP_SIZE * i
        nextt = GROUP_SIZE * (i + 1) if i != 15 else WIN
        data.extend([0xFFF0 + i, (start + 6) * 16 + 2, start + 4, 0])
        data.extend([0, 0, start + 8, 0])
        data.extend([0, 0, nextt if get(x, i) == 0 else QUIT, 0])
        data.extend([0, 0, nextt if get(x, i) == 1 else QUIT, 0])

    # ZERO/ONE block
    data.extend([0x0000, 0x0000, 0x0000, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])

    data.extend([0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF])
    for _ in range(3):
        data.extend([0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF])

    # quit block
    data.extend([ZERO, 0xFFF0, 0x0FFF, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])

    # win block
    data.extend([ONE, 0xFFF0, 0x0FFF, 0x0000])
    for _ in range(3):
        data.extend([0x0000, 0x0000, 0x0000, 0x0000])

    print(*list(map(f, data)))


if __name__ == "__main__":
    main()
