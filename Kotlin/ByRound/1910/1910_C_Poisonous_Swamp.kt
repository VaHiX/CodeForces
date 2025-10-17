// Problem: CF 1910 C - Poisonous Swamp
// https://codeforces.com/contest/1910/problem/C

/*
C. Poisonous Swamp

Algorithm: Greedy approach with simulation of frog movements on a 2×n grid.
For each column, we decide which frog (top or bottom) can move to an adjacent cell without violating constraints:
- No two frogs can be in the same cell after the move.
- Frogs cannot jump into invalid cells (out of bounds).
- Frogs cannot swap positions with adjacent frogs.

Time Complexity: O(n) per testcase, where n is the number of columns.
Space Complexity: O(1) excluding input storage.

Approach:
We iterate through columns and decide for each frog whether it can move to a valid adjacent cell.
The maximum number of surviving frogs is determined greedily by trying to maximize the count,
considering that not both frogs in the same column can survive, and that we must avoid position swaps.

 */
fun main() {
    repeat(readInt()) { // Process each testcase
        readInt() // Read n (number of columns), but don't store it since it's not used directly in logic
        val s = readln() + '.' + readln() // Combine both rows with a separator to process together
        println(s.split(".").sumOf { maxOf(0, it.length - 1) }) // Compute number of frogs that can survive using split and sum
    }
}

private fun readInt() = readln().toInt()


// https://github.com/VaHiX/codeForces/