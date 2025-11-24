// Problem: CF 2106 F - Goblin
// https://codeforces.com/contest/2106/problem/F

/*
F. Goblin

Problem Description:
Given a binary string s of length n, we construct an n×n grid g where g[i][j] is the j-th character of the string a_i, which is formed by flipping the i-th character of s. The task is to find the maximum size of a "good set" S: a set of cells in the grid where:
1. All cells have value 0.
2. All cells are connected via adjacent (sharing a side) 0-cells.

Algorithm:
This solution uses a linear scan approach over the input string s to calculate potential connected components of zeros in the grid, considering how flipping each bit affects the structure of the grid.

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (excluding input/output)

Approach:
- For each test case, we process the string s once.
- We keep track of sums related to positions where 0s occur and how they contribute to connected components in the grid.
- The algorithm maintains variables to track current top and bottom sums while iterating through the string.
- Special handling for initial consecutive 1s ensures correct calculation.

The key idea is that this problem can be abstracted into tracking segments of 0s in s, and how these affect possible connected regions in the resulting grid.
*/
import java.io.PrintWriter
import java.io.StreamTokenizer
import kotlin.math.max
fun main() {
    val writer = PrintWriter(System.out.bufferedWriter())
    val builder = StringBuilder()
    repeat(readln().toInt()) {
        val n = readln().toInt()
        val s = readln()
        var idx = 0
        var maxSum = 0L
        var topSum = 0L
        var botSum = 0L
        while (idx < n && s[idx] == '1') {
            idx++
            topSum = 1L
        }
        while (idx < n) {
            if (s[idx] == '0') {
                topSum += idx
                botSum += n - idx - 1
            } else {
                maxSum = maxOf(topSum, maxSum)
                topSum = botSum + 1
                botSum = 0
            }
            idx++
        }
        builder.appendLine(maxOf(topSum, botSum, maxSum))
    }
    writer.print(builder.toString())
    writer.flush()
}


// https://github.com/VaHiX/CodeForces/