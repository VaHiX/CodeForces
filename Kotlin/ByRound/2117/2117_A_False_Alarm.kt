// Problem: CF 2117 A - False Alarm
// https://codeforces.com/contest/2117/problem/A

/*
 * Problem: A. False Alarm
 * Purpose: Determine if Yousef can pass through all doors in a hallway given that he has a special button 
 *          that opens all closed doors for x seconds.
 * 
 * Algorithm:
 * 1. For each test case, find the first and last closed door (state = 1).
 * 2. Calculate the minimum time needed to traverse from first to last closed door.
 *    - If there's only one closed door, time needed is 1 second.
 *    - Otherwise, time needed is the distance between first and last closed doors plus 1.
 * 3. Check if x (button duration) is greater than or equal to the required time.
 *    - If yes, print "YES"
 *    - Else, print "NO"
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing door states
 */
fun main() {
    solve()
}
private fun solve() {
    repeat(readInt()) {
        val (n, x) = readInts() // Read number of doors and button duration
        val doorsState = readInts() // Read the state of each door (0 = open, 1 = closed)
        val firstClosedDoor = doorsState.indexOfFirst { it == 1 } // Find index of first closed door
        val lastClosedDoor = doorsState.indexOfLast { it == 1 } // Find index of last closed door
        val timeNeeded = if (firstClosedDoor == lastClosedDoor) {
            1 // Only one closed door, so only 1 second needed to pass through it
        } else {
            (lastClosedDoor - firstClosedDoor) + 1 // Distance between first and last closed door, plus passage time
        }
        if (x >= timeNeeded) { // If button duration is sufficient
            println("YES")
        } else {
            println("NO")
        }
    }
}
private fun readLn() = readLine()!! 
private fun readInt() = readLn().toInt() 
private fun readLong() = readLn().toLong() 
private fun readStrings() = readLn().split(" ") 
private fun readInts() = readStrings().map { it.toInt() } 
private fun readLongs() = readStrings().map { it.toLong() } 


// https://github.com/VaHiX/CodeForces/