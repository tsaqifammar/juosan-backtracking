/*

Given a set of solutions S to an instance,
exhaustively find "valid subgrids" (i.e., it doesn't violate the Juosan rules)
that don't exist in any of the solutions in S.

These subgrids might be impossible to exist in a solution, despite their validity.

An example input is the 4x4_sols.txt file, which contains all solutions to the following instance:
4 4
1
-1
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1

Adjust the subgrid size (SMALL_M x SMALL_N) in the settings below.

*/
#include<bits/stdc++.h>
using namespace std;

#define vc vector<char>
#define vvc vector<vc>

int no_of_solutions, m, n;
vector<vvc> S;

// Subgrid settings. Adjust sizes accordingly.
const int SMALL_M = 2, SMALL_N = 3;
const int cell_count = SMALL_M * SMALL_N;
vvc subgrid(SMALL_M, vc(SMALL_N));

// This procudure generates one possible subgrid.
void generateSubgrid(int bitmask) {
  int x = 0, y = 0;
  for (int i = 0; i < cell_count; i++) {
    subgrid[x][y] = (bitmask & (1 << i) ? '|' : '-');
    y++;
    if (y >= SMALL_N) y = 0, x++;
  }
}

// This function validates whether the generated subgrid violates the Juosan rules or not.
bool validateSubgrid() {
  for (int i = 0; i + 2 < SMALL_M; i++)
      for (int j = 0; j < SMALL_N; j++)
          if (subgrid[i][j] == '-' && subgrid[i+1][j] == '-' && subgrid[i+2][j] == '-')
              return false;
  for (int i = 0; i < SMALL_M; i++)
      for (int j = 0; j + 2 < SMALL_N; j++)
          if (subgrid[i][j] == '|' && subgrid[i][j+1] == '|' && subgrid[i][j+2] == '|')
              return false;
  return true;
};

// This function checks if the subgrid exist in any of the solutions
bool checkSubgridDoesExistInASolution() {
  for (int t = 0; t < no_of_solutions; t++) {
    auto& cur = S[t];
    // For each top left corner (i,j), check the subgrid
    for (int i = 0; i + SMALL_M - 1 < m; i++) {
      for (int j = 0; j + SMALL_N - 1 < n; j++) {
        bool subgridExists = true;
        for (int x = 0; x < SMALL_M; x++)
          for (int y = 0; y < SMALL_N; y++)
            if (subgrid[x][y] != cur[i + x][j + y])
              subgridExists = false;
        if (subgridExists) return true;
      }
    }
  }
  return false;
}

int main() {
  cin >> no_of_solutions >> m >> n;

  // Input solutions
  vvc grid(m, vc(n));
  for (int t = 0; t < no_of_solutions; t++) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        cin >> grid[i][j];
    S.push_back(grid);
  }

  // Generate all "valid subgrids" of size SMALL_M x SMALL_N
  // Then check if it does not exist in any of the solutions.
  vector<vvc> invalidSubgrids;
  for (int bitmask = 0; bitmask < (1 << cell_count); bitmask++) {
    generateSubgrid(bitmask);
    if (!validateSubgrid()) continue;
    if (!checkSubgridDoesExistInASolution()) invalidSubgrids.push_back(subgrid);
  }

  // Output the results.
  cout << "Size: " << SMALL_M << " x " << SMALL_N << '\n';
  cout << "Found: " << invalidSubgrids.size() << '\n';
  for (int t = 0; t < invalidSubgrids.size(); t++) {
    cout << "=====\n";
    for (int i = 0; i < SMALL_M; i++)
      for (int j = 0; j < SMALL_N; j++)
        cout << invalidSubgrids[t][i][j] << " \n"[j == SMALL_N - 1];
  }
}