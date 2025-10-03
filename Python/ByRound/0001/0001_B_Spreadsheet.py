# Contest 1, Problem B: Spreadsheet
# URL: https://codeforces.com/contest/1/problem/B

import re
import sys


def f1(col):
    col = int(col)
    res = ""
    while col:
        m = (col - 1) % 26
        col = (col - 1) // 26
        res = chr(65 + m) + res
    return res


def f2(col):
    res = 0
    for d in col:
        res = 26 * res + ord(d) - 64
    return res


for line in sys.stdin.read().split()[1:]:
    if len(re.findall(r"\d+", line)) == 2:
        row, col = re.findall(r"(\d+)", line)
        print(f"{f1(col)}{row}")
    else:
        col, row = re.fullmatch(r"([A-Z]+)(\d+)", line).groups()
        print(f"R{row}C{f2(col)}")
