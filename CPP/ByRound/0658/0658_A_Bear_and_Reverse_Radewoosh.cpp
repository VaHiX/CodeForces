// Problem: CF 658 A - Bear and Reverse Radewoosh
// https://codeforces.com/contest/658/problem/A

/*
 * Problem: Bear and Reverse Radewoosh
 * 
 * Algorithm/Techniques: Simulation
 * 
 * Time Complexity: O(n), where n is the number of problems.
 * Space Complexity: O(n), due to storing scores and minutes arrays.
 * 
 * Description:
 * Two contestants, Limak and Radewoosh, solve problems in different orders.
 * Limak solves problems in ascending order of difficulty,
 * while Radewoosh solves them in descending order.
 * Each problem has an initial score and time to solve.
 * Points decrease over time based on a constant 'c'.
 * The contestant with more total points wins.
 */

#include <iostream>
#include <vector>

// Function to calculate actual points for a problem at a given time
long actualPoints(long points, long time, long c) {
  return (points >= (c * time)) ? (points - c * time) : 0;
}

int main() {
  long n, c;
  std::cin >> n >> c;
  std::vector<long> scores(n);
  std::vector<long> minutes(n);
  
  // Read scores
  for (int p = 0; p < n; p++) {
    std::cin >> scores[p];
  }
  
  // Read minutes
  for (int p = 0; p < n; p++) {
    std::cin >> minutes[p];
  }
  
  long limak(0), rad(0);          // Total points for Limak and Radewoosh
  long limakTime(0), radTime(0);  // Total time taken by each contestant
  
  // Simulate both contestants solving problems
  for (int p = 0; p < n; p++) {
    limakTime += minutes[p];                    // Add time for Limak's current problem
    radTime += minutes[n - 1 - p];              // Add time for Radewoosh's current problem
    
    limak += actualPoints(scores[p], limakTime, c);           // Add points for Limak
    rad += actualPoints(scores[n - 1 - p], radTime, c);       // Add points for Radewoosh
  }
  
  // Determine and print the winner
  if (limak > rad) {
    std::cout << "Limak" << std::endl;
  } else if (limak < rad) {
    std::cout << "Radewoosh" << std::endl;
  } else {
    std::cout << "Tie" << std::endl;
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/