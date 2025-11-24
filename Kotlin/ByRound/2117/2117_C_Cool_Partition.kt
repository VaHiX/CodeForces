// Problem: CF 2117 C - Cool Partition
// https://codeforces.com/contest/2117/problem/C

/*
C. Cool Partition
Algorithms/Techniques: Two-pointer technique, preprocessing for last occurrence of elements

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Purpose: 
This code finds the maximum number of segments that form a "cool partition" of an array.
A cool partition means that every element in a segment must also appear in the next segment.
The approach uses preprocessing to find the last occurrence of each element and then uses
a greedy two-pointer method to determine the maximal number of such segments.
*/

fun solve() {
    val n = readLine()!!.toInt()
    val a = readLine()!!.split(" ").map { it.toInt() }
    val gg = n + 1 // Sentinel value larger than any valid index
    val mo = IntArray(n) { gg } // Stores the last occurrence of each element
    val res = mutableMapOf<Int, Int>() // Maps element to its last seen index
    
    // Preprocessing step: fill 'mo' array with last occurrence indices
    for (i in n - 1 downTo 0) {
        mo[i] = res.getOrDefault(a[i], gg) // Get last occurrence of a[i]
        res[a[i]] = i // Update the most recent index for a[i]
    }
    
    var pos = 0 // Start pointer for current segment
    var ans = 0 // Count of segments
    
    while (pos < n) {
        var end = pos // End pointer of current segment
        while (true) {
            var nn = -1
            // Find the furthest last occurrence among elements in [pos, end]
            for (i in pos..end) {
                if (mo[i] > nn) nn = mo[i]
            }
            ans++ // Increment segment count
            
            if (nn >= n) break // No more elements to extend the segment
            pos = end + 1 // Move start to next segment
            end = nn // Extend end to the furthest last occurrence
        }
        break // Only one partition needed per array (as stated by problem setup)
    }
    
    println(ans)
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) { solve() }
}


// https://github.com/VaHiX/CodeForces/