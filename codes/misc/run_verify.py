import os

def run_verify():
  """
  Run verifier against all test cases
  """
  path = '.'
  files_todo = [f.split('.')[0] for f in os.listdir(path) if f.endswith('.in')]

  for f in files_todo:
    print(f"{f} ===============")
    for _ in range(3):
      os.system(f"verifier < {f}.mix")
  
run_verify()
