from bs4 import BeautifulSoup
import requests
import time

def getUrl(tc_num):
	tc_num = str(tc_num).zfill(3)
	return f"https://www.janko.at/Raetsel/Juosan/{tc_num}.a.htm"

def generateTc(text, tc_num):
	""" example text
	begin
	puzzle juosan
	author ihnnpuzzles
	solver JÃ¼rgen Helbig
	source https://puzz.link/p?juosan/6/6/hh44aa0fo3u017253334
	source https://ihnnpuzzles.blogspot.com/2021/04/puzzles-340-349-buckblosters-variety.html
	info 1.5.2021, 03:00 (5) [002]
	unit 30
	size 6       atau    rows 6\ncols 9
	problem
	1 7 - - - 2
	- - - - - -
	5 - - 3 - -
	- - - - - -
	3 - 3 - 4 -
	- - - - - -
	areas
	1 4 4 4 4 8
	1 4 4 4 4 8
	2 2 2 6 6 6
	2 2 2 6 6 6
	3 3 5 5 7 7
	3 3 5 5 7 7
	solution
	h h h h h v
	v h v h h v
	h v h v v h
	h h h v h h
	v h v h v v
	v v h h v v
	"""
	lines = text.split('\n')

	i = 0
	r, c = -1, -1
	for l in lines:
		if l.startswith('size'):
			boardSize = int(l.split()[1])
			r, c = boardSize, boardSize
			break
		elif l.startswith('rows'):
			r = int(l.split()[1])
		elif l.startswith('cols'):
			c = int(l.split()[1])
			break
		i += 1
	i += 2
	problem = []
	for j in range(r): problem.append(lines[i].split()); i += 1
	i += 1
	areas = []
	for j in range(r): areas.append(list(map(int, lines[i].split()))); i += 1
	i += 1
	solution = []
	for j in range(r):
		tmp = lines[i].split()
		solution.append(['|' if tmp[k] == 'v' else '-' for k in range(c)])
		i += 1

	maxRegionNum = max([val for line in areas for val in line])
	N = [-1 for i in range(maxRegionNum)]
	for x in range(r):
		for y in range(c):
			if problem[x][y].isnumeric():
				hint = int(problem[x][y])
				N[areas[x][y] - 1] = hint
	# input
	with open(f'{tc_num}_tc.txt', 'w') as f:
		f.write(f'{r} {c}\n')
		f.write(f'{maxRegionNum}\n')
		f.write(f'{" ".join(map(str, N))}\n')
		for j in range(r):
			f.write(f'{" ".join(map(str, areas[j]))}\n')
	# answer
	with open(f'{tc_num}_sol.txt', 'w') as f:
		for j in range(r):
			f.write(f'{" ".join(solution[j])}\n')

start_tc, end_tc = 1, 70
for i in range(start_tc, end_tc + 1):
	print(f'Generating tc {i}..')
	url = getUrl(i)
	result = requests.get(url)
	doc = BeautifulSoup(result.text, "html.parser")
	infoText = doc.find_all('script')[2].text
	# print(infoText.strip())
	generateTc(infoText.strip(), i)
	time.sleep(0.1)
