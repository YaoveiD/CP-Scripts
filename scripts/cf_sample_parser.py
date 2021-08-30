#copy it from https://github.com/emilgoldsmith/Codeforces-test-case-parser/blob/master/getTestCases.py and modified by me
#!/usr/bin/python3

from urllib.request import urlopen
from bs4 import BeautifulSoup
from html.parser import HTMLParser
from sys import argv
import requests
import os

class COLOR:
  RED = '\033[31m'
  GREEN = '\033[32m'
  ORANGE = '\033[33m'
  BULE = '\033[34m'
  END =  '\033[0m'

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

contest_url = 'https://codeforces.com/contest/' + contest_number

problem_set = []
if len(argv) > 2:
  problem_set = argv[2:]
else:
  #parse problems' id
  html = requests.get(contest_url)
  soup = BeautifulSoup(html.content, 'html.parser')
  for p in soup.findAll('td', attrs={'class':"id"}): 
    for s in p.find('a').stripped_strings:
        problem_set.append(s)
  problem_set = problem_set[:4]               #cause i can only solve no more then 4 problems

print("problems :", problem_set)

#parse problems' smaples
for problem_letter in problem_set:
  url = contest_url + '/problem/' + problem_letter
  problem = urlopen(url)
  if problem.geturl() != url:
    break
  else:
    print(COLOR.GREEN + "Fetching problem" + COLOR.GREEN, problem_letter)
    
    text = problem.read()
    parser = problem_parser()
    parser.feed(text.decode('utf-8'))
    
    if len(parser.input) != len(parser.output):
      print(COLOR.RED + "Error with problem" + COLOR.RED, problem_letter)
    else:
      sol = open(contest_number + "/" + problem_letter + '.cpp', 'a')

      test_number = 1
      for test_case in parser.input:
        inp = open(contest_number + "/" + problem_letter + '-{}.in'.format(test_number), 'w')
        inp.write(test_case.strip() + '\n')
        inp.close()
        test_number += 1
      
      test_number = 1
      for test_case in parser.output:
        out = open(contest_number + "/" + problem_letter + '-{}.out'.format(test_number), 'w')
        out.write(test_case.strip() + '\n')
        out.close()
        test_number += 1
      sol.close()

for problem_letter in problem_set:
  cmd = "subl " + contest_number + "/" + problem_letter + '.cpp'
  os.system(cmd)