// Problem: CF 2167 E - khba Loves to Sleep!
// https://codeforces.com/contest/2167/problem/E

/*
 * Problem: E. khba Loves to Sleep!
 * Purpose: Given n friends at positions a[i] on a line [0, x], and k teleports,
 *          choose k distinct teleport positions in [0, x] to maximize the 
 *          minimum time for any friend to reach the nearest teleport.
 * 
 * Algorithm: Binary search on the answer (minimum distance), 
 *            using a greedy assignment strategy to check feasibility.
 * 
 * Time Complexity: O(n log(max_distance)) where max_distance ~ 1e9
 * Space Complexity: O(n) for sorting friends' positions
 */

fun main() {
    val cin = System.`in`.bufferedReader()
    val cout = System.out.bufferedWriter()
    repeat(cin.readLine().toInt()) {
        val (n, k, x) = cin.readLine().split(" ").map { it.toInt() }
        val a = cin.readLine().split(" ").map { it.toInt() }.sorted() // Sort positions of friends
        
        // Function to check if a minimum distance 'd' is feasible.
        // It determines whether we can place k distinct teleports such that 
        // the maximum distance from any friend to the nearest teleport is at least d.
        fun poss(d: Int): Boolean {
            var kk = k // Number of teleports we can place
            var i = 0 // Index for friends array
            var min = 0 // Start of available interval
            var max = a[0] - d // End of available interval for first friend
            
            // If the interval [min, max] can accommodate teleport(s)
            if (min <= max) kk -= max - min + 1
            while (kk > 0 && i + 1 < n) {
                min = a[i] + d // Start of interval after current friend
                max = a[i + 1] - d // End of interval before next friend
                if (min <= max) kk -= max - min + 1 // Place teleports if valid interval
                i++
            }
            min = a[n - 1] + d // After last friend
            max = x // Up to x
            if (min <= max) kk -= max - min + 1 // Place remaining teleports
            return kk <= 0L // If all were assigned, it's possible
        }

        // Function to assign k teleport positions that achieve the maximum minimum distance
        fun assign(d: Int): List<Int> {
            if (d == 0) return (0..<k).toList() // If d=0, assign first k positions
            val ans = mutableListOf<Int>()
            // First part: place teleports before first friend
            for (v in 0..a[0] - d) {
                ans.add(v)
                if (ans.size == k) return ans
            }
            // Middle part: place between friends
            for (i in 0 until n - 1) {
                for (v in (a[i] + d)..(a[i + 1] - d)) {
                    ans.add(v)
                    if (ans.size == k) return ans
                }
            }
            // Last part: after last friend
            for (v in a[n - 1] + d..x) {
                ans.add(v)
                if (ans.size == k) return ans
            }
            return ans
        }
        
        // Binary search on the answer
        var l = 0
        var r = 1e9.toInt() + 1
        while (l <= r) {
            val mid = l + (r - l) / 2
            if (poss(mid)) l = mid + 1 // If possible to place with distance 'mid', search higher
            else r = mid - 1 // Else search lower
        }
        
        val ans = assign(l - 1) // Assign k teleports for the optimal distance
        cout.write("${ans.joinToString(" ")}\n")
    }
    cout.flush()
}


// https://github.com/VaHiX/CodeForces/