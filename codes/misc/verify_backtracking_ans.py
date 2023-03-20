import os

def get_test_cases():
  MAX_CELLS = 300
  path = '.'
  test_cases = [f.split('.')[0] for f in os.listdir(path) if f.endswith('.in')]
  tc_todo = []
  for f in test_cases:
    dim = f.split('_')[0]
    m, n = map(int, dim.split('x'))
    if m*n <= MAX_CELLS:
      tc_todo.append(f)
  return tc_todo

def verify_backtracking_ans():
  """
  Verifies backtracking algorithm by comparing
  its output to .ans
  """
  test_cases = get_test_cases()

  for f in test_cases:
    print(f"{f} ===============")
    os.system(f"solver_backtrack_output_sol < {f}.in > tmp")
    path_tmp = os.path.join(os.getcwd(), "tmp")
    path_ans = os.path.join(os.getcwd(), f"{f}.ans")
    file_tmp = open(path_tmp, "r")
    file_ans = open(path_ans, "r")
    content_tmp = file_tmp.read()
    content_ans = file_ans.read()
    print("same: ", content_tmp == content_ans)
    file_tmp.close()
    file_ans.close()
  
verify_backtracking_ans()
