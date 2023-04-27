import sys
from pysat.solvers import Glucose3
from typing import List

# Utility functions
def maxLit(m: List[List[int]]):
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
solver = Glucose3(use_timer=True)

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

def atLeastK(lits: List[int], bound: int, top_id: int) -> List[List[int]]:
  # Implements the sequential counter encoding of EqualsK constraint
  def s(i: int, p: int) -> int:
    # A bijective function to map s(i,p) to a unique integer.
    # The variable `top_id` is used as an offset.
    assert(0 <= i <= len(lits) and 0 <= p <= bound)
    return i*(bound + 1) + p + (top_id + 1)
  
  def gen_form(a: int, b: int, c: int, d: int):
    # Returns the CNF clauses of "a <-> (b V (c ^ d))"
    return [[-a, b, c], [-a, b, d], [a, -b], [a, -c, -d]]
  
  formula = [[s(len(lits), bound)], [s(0,0)]]
  formula += [[s(i,0)] for i in range(1, len(lits)+1)] 
  formula += [[-s(0,p)] for p in range(1, bound+1)]
  for i in range(1, len(lits)+1):
    for p in range(1, bound+1):
      formula += gen_form(s(i,p), s(i-1,p), s(i-1,p-1), lits[i-1])
  return formula

def equalsK(lits: List[int], bound: int, top_id: int) -> List[List[int]]:
  at_least_formula = atLeastK(lits, bound, top_id)
  new_top_id = maxLit(at_least_formula)
  at_most_formula = atLeastK([-v for v in lits], len(lits)-bound, new_top_id)
  return at_least_formula + at_most_formula

prev_top = J(m - 1, n - 1)

for i in range(r):
  if N[i] != -1:
    t = prev_top + 1
    dashEqual = equalsK(
      lits=region_cells[i],
      bound=N[i],
      top_id=t
    )
    dashEqualWithT = distribute(t, dashEqual)
    solver.append_formula(
      formula=dashEqualWithT,
      no_return=False
    )

    barEqual = equalsK(
      lits=region_cells[i],
      bound=len(region_cells[i])-N[i],
      top_id=maxLit(dashEqualWithT)
    )
    barEqualWithNegT = distribute(-t, barEqual)
    solver.append_formula(
      formula=barEqualWithNegT,
      no_return=False
    )

    prev_top = maxLit(barEqualWithNegT)

# Running the SAT solver
sat = solver.solve()

if sat:
  print("Found a solution:")
  solution = solver.get_model()
  for i in range(m):
    for j in range(n):
      print("-" if J(i,j) in solution else "|", end=" ")
      if j == n - 1: print()
else:
  print("No solution")
  print(solver.get_core())

print(f"Time taken: {solver.time()*1000:.3f} ms")
