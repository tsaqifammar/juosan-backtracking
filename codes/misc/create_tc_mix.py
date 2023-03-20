import os

def generate_files_mix():
    """
    Generate .mix files with content = .in + .ans
    for test cases
    """
    path = '.'
    files_todo = [f.split('.')[0] for f in os.listdir(path) if f.endswith('.in')]
    for f in files_todo:
        path_in = os.path.join(os.getcwd(), f"{f}.in")
        path_ans = os.path.join(os.getcwd(), f"{f}.ans")
        path_mix = os.path.join(os.getcwd(), f"{f}.mix")
        file_in = open(path_in, "r")
        file_ans = open(path_ans, "r")
        file_mix = open(path_mix, "a")
        content_in = file_in.read()
        content_ans = file_ans.read()

        file_mix.write(content_in)
        file_mix.write(content_ans)
        file_in.close()
        file_ans.close()
        file_mix.close()

generate_files_mix()

