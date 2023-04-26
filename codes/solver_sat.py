import sys
import time
from pysat.solvers import Glucose3
from pysat.card import CardEnc
from typing import List

# Utility functions
def maxAbs2DList(m: List[List[int]]):
  return max([max([abs(v) for v in clause]) for clause in m])
def distribute(v: int, formula: List[List[int]]):
  return [clause + [v] for clause in formula]

# Process input
with open(sys.argv[1], 'r') if len(sys.argv) > 1 else sys.stdin as f:
  m, n = map(int, f.readline().strip().split())
  r = int(f.readline())

  N = list(map(int, f.readline().strip().split()))
  R = []
  for _ in range(m):
    R.append(list(map(int, f.readline().strip().split())))

# Initialize solver
solver = Glucose3()

def J(i: int, j: int) -> int:
  return i*n + j + 1

# Configure rule three vertically consecutive
for i in range(m - 2):
  for j in range(n):
    solver.add_clause([-J(i,j), -J(i+1,j), -J(i+2,j)])

# Configure rule three horizontally consecutive
for i in range(m):
  for j in range(n - 2):
    solver.add_clause([J(i,j), J(i,j+1), J(i,j+2)])

# Configure territory rules
region_cells = {region: [] for region in range(r)}
for i in range(m):
  for j in range(n):
    region_cells[R[i][j] - 1].append(J(i,j))

prev_top = J(m - 1, n - 1)

for i in range(r):
  if N[i] != -1:
    t = prev_top + 1
    dashEqual = CardEnc.equals(
      lits=region_cells[i],
      bound=N[i],
      top_id=t
    )
    dashEqualWithT = distribute(t, dashEqual.clauses)
    solver.append_formula(
      formula=dashEqualWithT,
      no_return=False
    )

    barEqual = CardEnc.equals(
      lits=region_cells[i],
      bound=len(region_cells[i])-N[i],
      top_id=maxAbs2DList(dashEqualWithT)
    )
    barEqualWithNegT = distribute(-t, barEqual.clauses)
    solver.append_formula(
      formula=barEqualWithNegT,
      no_return=False
    )

    prev_top = maxAbs2DList(barEqualWithNegT)

# Running the SAT solver
start_time = time.time()
sat = solver.solve()
time_taken = time.time() - start_time

if sat:
  print("Found a solution:")
  solution = solver.get_model()
  for i in range(m):
    for j in range(n):
      print("-" if J(i,j) in solution else "|", end=" ")
      if j == n - 1: print()
else:
  print("No solution")

print(f"Time taken: {time_taken*1000:.3f} ms")
