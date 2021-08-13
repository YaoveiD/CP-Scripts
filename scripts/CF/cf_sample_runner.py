#also from https://github.com/emilgoldsmith/Codeforces-test-case-parser/blob/master/run.py
from sys import argv
from subprocess import run, PIPE
from time import time
from os import path
import os

os.system('')

# This parse break should be the same in your get test cases file
PARSE_BREAK = "END OF THIS TEST\n"

class COLOR:
  RED = '\033[31m'
  GREEN = '\033[32m'
  ORANGE = '\033[33m'
  BULE = '\033[34m'
  END =  '\033[0m'

#remember to cd into the contest folder
problem_letter = argv[1].upper()
complie = len(argv) > 2 and argv[2] == '-c'

inp = open(problem_letter.upper() + '.in', 'r')
out = open(problem_letter.upper() + '.out', 'r')
passed_cases, num_cases = 0, int(inp.readline())


if int(out.readline()) != num_cases:
  print("Error: Number of test cases in input and answer files are different")
  exit()

#complie
runfile_name = "./" + problem_letter
if not path.exists(runfile_name) or complie:
  print("Compling {}.cpp......".format(problem_letter))
  run(["g++", "-Wall", "-O2", problem_letter + ".cpp", "-std=c++17", "-o", problem_letter, "-DLOCAL"])

for i in range(1, num_cases + 1):
  case_input = ""
  line = inp.readline()
  while line != PARSE_BREAK:
    line = '' if line == '\n' else line
    case_input += line
    line = inp.readline()

  #run
  #start_time = time()
  output = run([runfile_name],
    input=case_input.encode('utf-8'), stdout=PIPE).stdout.decode('utf-8')
  #time_taken = time()-start_time

  output = ''.join(output.split('\r'))
  case_output = ""
  line = out.readline()
  while line != PARSE_BREAK:
    line = '' if line == '\n' else line
    case_output += line
    line = out.readline()

  print(COLOR.ORANGE + "Case #{}".format(i) + COLOR.END)
  print(COLOR.BULE + "Input:" + COLOR.END)
  print(case_input)
  print(COLOR.BULE + "Output:" + COLOR.END)
  print(output)
  print(COLOR.BULE + "Expected:" + COLOR.END)
  print(case_output)

  if output != case_output:
    print(COLOR.RED + 'Wrong answer on test case {}'.format(i) + COLOR.END)
    break
  else:
    passed_cases += 1
if passed_cases == num_cases: 
  print(COLOR.GREEN + "{} / {} passed".format(passed_cases, num_cases) + COLOR.END)
else:
  print(COLOR.RED + "{} / {} passed".format(passed_cases, num_cases) + COLOR.END)
#print("Time taken: {}".format(time_taken))
inp.close()
out.close()