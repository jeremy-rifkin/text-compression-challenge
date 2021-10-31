# frequency table generator from a corpa

source = "data/1984.txt"

def make_2d(w, h):
	return [[0 for _ in range(w)] for _ in range(h)]

def char_to_i(c):
	if c == ' ':
		return 26
	else:
		c = ord(c) - ord('a')
		assert c >= 0
		assert c <= 25
		return c

def main():
	# conditional probability tables
	# indices 0-25 are letters, 26 is null
	tables = make_2d(26, 27)
	# read content
	with open(source, "r") as f:
		content = f.read().split(" ")
	#print(content)
	for word in content:
		last = 26
		for c in word:
			i = char_to_i(c)
			tables[last][i] += 1
			last = i
	# output for C++
	print("{")
	for table in tables:
		print("    { ", end="")
		for f in table:
			print("{}, ".format(f / max(table)), end="")
		print("},")
	print("};")

main()
