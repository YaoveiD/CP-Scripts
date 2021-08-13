#copy it from https://github.com/emilgoldsmith/Codeforces-test-case-parser/blob/master/getTestCases.py
#!/usr/bin/python3

from urllib.request import urlopen
from sys import argv
from html.parser import HTMLParser
import os

# This parse break should be the same in your run file
PARSE_BREAK = "END OF THIS TEST\n"

class problem_parser(HTMLParser):
  def __init__(self):
    HTMLParser.__init__(self)
    self.reading = False
    self.input = []
    self.output = []
    self.buffer = ""

  def handle_starttag(self, tag, attrs):
    if tag == "pre":
      self.reading = True

  def handle_endtag(self, tag):
    if tag == "pre":
      self.reading = False
      if len(self.input) == len(self.output):
        self.input.append(self.buffer)
      else:
        self.output.append(self.buffer)
      self.buffer = ""

  def handle_data(self, data):
    if self.reading:
      self.buffer += data + '\n'

contest_number = argv[1]
if not os.path.exists(contest_number):
  os.mkdir(contest_number)
problem_set = "ABCD"               #cause i can only solve no more then 4 problems
if len(argv) > 2:
  problem_set = argv[2]

for problem_letter in problem_set:
  url = 'http://codeforces.com/contest/' + contest_number + '/problem/' + problem_letter
  problem = urlopen(url)
  if problem.geturl() != url:
    break
  else:
    print("Fetching problem", problem_letter)
    text = problem.read()
    parser = problem_parser()
    parser.feed(text.decode('utf-8'))
    if len(parser.input) != len(parser.output):
      print("Error with problem", problem_letter)
    else:
      sol = open(contest_number + "/" + problem_letter + '.cpp', 'w')
      inp = open(contest_number + "/" + problem_letter + '.in', 'w')
      inp.write(str(len(parser.input)))
      for test_case in parser.input:
        inp.write(test_case)
        inp.write(PARSE_BREAK)
      inp.close()
      out = open(contest_number + "/" + problem_letter + '.out', 'w')
      out.write(str(len(parser.output)))
      for test_case in parser.output:
        out.write(test_case)
        out.write(PARSE_BREAK)
      out.close()
      sol.close()

for problem_letter in problem_set:
  cmd = "subl " + contest_number + "/" + problem_letter + '.cpp'
  os.system(cmd)