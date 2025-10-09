// Problem: CF 2151 B - Incremental Path
// https://codeforces.com/contest/2151/problem/B

/*
B. Incremental Path
Algorithms/Techniques: Simulation with two pointers, handling of commands A and B.

Time Complexity: O(n + m) for each test case, where n is the length of string s and m is the number of initial black cells.
Space Complexity: O(m + n) for storing the input and result list.

The problem simulates a process where a person follows a sequence of commands (A or B) on a strip of cells,
and at each step, the final cell visited is colored black.
We maintain a list of current black cells and simulate execution of the commands to track which cells become black.
*/
fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val (n, m) = cin.readLine().split(" ").map { it.toInt() }
        val s = cin.readLine()
        val a = cin.readLine().split(" ").map { it.toInt() }
        val ans = mutableListOf<Int>()
        var i = 0
        var j = 0
        var p = 1 // current cell position
        if (a[j] == 1) {
            ans.add(1)
            j++
        }
        while (i < n) {
            if (s[i] == 'A') {
                p++
                ans.add(p)
                if (j < m && a[j] == p) j++ // if the current position is black, advance the pointer
            } else {
                // B command: jump to the next white cell
                p++
                while (j < m && a[j] == p) {
                    ans.add(a[j])
                    j++
                    p++
                }
                ans.add(p)
                p++
                while (j < m && a[j] == p) {
                    ans.add(a[j])
                    j++
                    p++
                }
            }
            i++
        }
        // Add any remaining black cells that were not processed
        while (j < m) ans.add(a[j++])
        cout.write("${ans.size}\n")
        cout.write("${ans.joinToString(" ")}\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/