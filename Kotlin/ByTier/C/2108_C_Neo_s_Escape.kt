// Problem: CF 2108 C - Neo's Escape
// https://codeforces.com/contest/2108/problem/C

/*
C. Neo's Escape

Problem Description:
Neo wants to press all buttons in a non-increasing order of weights using clones.
Each clone can be created at any button and moved around, but only one clone per button can exist.
Goal: find minimum number of clones needed.

Algorithm:
1. Sort the buttons by weight in descending order.
2. For each group of buttons with equal weight:
   - Group consecutive indices together.
   - For each segment of consecutive indices, check whether endpoints are already pressed.
   - If not, we can use 1 clone to press them in sequence; otherwise, we need 1 more clone.
   - Mark all positions as pressed.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n)
*/

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val vecB = LongArray(n + 2) { 0L } // Button weights array (1-indexed)
        val Thuy = BooleanArray(n + 2) { false } // Whether button is pressed
        val input = readLine()!!.split(" ").map { it.toLong() }
        for (i in 1..n) {
            vecB[i] = input[i - 1]
        }
        val Res = mutableListOf<Pair<Long, Int>>() // Pair of (weight, index)
        for (i in 1..n) {
            Res.add(Pair(vecB[i], i))
        }
        Res.sortByDescending { it.first } // Sort by weight descending
        var ans = 0L // Result: minimum clones needed
        var oo = 0 // Iterator for sorted list
        while (oo < n) {
            val curVal = Res[oo].first // Current weight being processed
            val group = mutableListOf<Int>() // Indices of buttons with same weight
            while (oo < n && Res[oo].first == curVal) {
                group.add(Res[oo].second)
                oo++
            }
            group.sort() // Sort indices in ascending order
            var best = 0
            val m = group.size
            while (best < m) {
                var l = group[best]
                var r = l
                while (best + 1 < m && group[best + 1] == r + 1) {
                    r = group[++best]
                }
                // If left neighbor and right neighbor are not pressed, we need a clone
                if (!Thuy[l - 1] && !Thuy[r + 1]) {
                    ans++
                }
                best++
            }
            for (pos in group) {
                Thuy[pos] = true // Mark all positions as pressed
            }
        }
        println(ans)
    }
}


// https://github.com/VaHiX/CodeForces/