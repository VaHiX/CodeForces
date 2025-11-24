// Problem: CF 2087 B - Showmatch
// https://codeforces.com/contest/2087/problem/B

/*
B. Showmatch
Algorithms/Techniques: Sorting, Greedy Approach
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array of ratings

In a showmatch for a computer game, 2n esports players are set to participate; the rating of the i-th player is a_i. 
The ratings of all players are distinct. For each player, the most exciting match will be with the player whose rating 
is the closest to theirs. Formally, for the i-th player, the best opponent is another player j such that the absolute 
difference in their ratings |a_i - a_j| is minimized among all ways to choose player j.

The organizers of the showmatch want to pair the participants so that each player is in exactly one pair, and in each pair, 
the players are best opponents for each other. Determine whether such a pairing exists.
*/

fun main() {
    repeat(readln().toInt()) {
        val n = readln().toInt()
        val a = readln().split(" ").map({ it.toInt() }).sorted() // Sort ratings
        var flag = false
        for (i in 0..2 * (n - 1)) {
            if (flag == true) {
                break
            }
            if (i % 2 == 1) {
                // Check if the current pair violates the "closest opponent" rule
                if (kotlin.math.abs(a[i] - a[i - 1]) > kotlin.math.abs(a[i + 1] - a[i])) {
                    flag = true
                }
            }
        }
        // Special check for last element's relationship with its neighbors
        if (
            kotlin.math.abs(a[2 * n - 2] - a[2 * n - 3]) < kotlin.math.abs(a[2 * n - 2] - a[2 * n - 1])
        ) {
            flag = true
        }
        if (flag == true) {
            println("NO")
        } else {
            println("YES")
        }
    }
}


// https://github.com/VaHiX/codeForces/