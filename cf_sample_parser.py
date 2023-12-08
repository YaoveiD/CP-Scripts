#!/usr/bin/env python3
from bs4 import BeautifulSoup
import requests
import sys
import time

if len(sys.argv) < 2:
  print("Need contest number")
  sys.exit(0)

number = sys.argv[1]
print('getting problems')
# TODO: Cannot use
r = requests.get("http://codeforces.com/contest/" + number + "/problems")
print('got problems')
s = r.text
soup = BeautifulSoup(s, "html.parser")
probs = soup.findAll("div", {"class": "problemindexholder"})

for prob in probs:
  index = prob["problemindex"]
  print("Problem", index)
  samples = prob.find("div", {"class": "sample-test"})
  io = list(zip(samples.findAll("div", {"class": "input"}),
          samples.findAll("div", {"class": "output"})))

  for i in range(len(io)):
    inp, oup = io[i]
    test_cases = inp.find("pre").findAll("div")
    ins = ""
    outs = oup.find("pre").text.strip()

    # Single test case
    if not test_cases:
      ins = inp.find("pre").text
    else:
      for test in test_cases:
        ins += test.text.strip() + '\n'

    print("Input:")
    print(ins.strip())
    print("Output:")
    print(outs)

    with open("%s-%d.in" % (index, i+1), "w") as f:
      print(ins.strip(), file=f)
    with open("%s-%d.out" % (index, i+1), "w") as f:
      print(outs, file=f)

  print("\nProblem", index, len(io), "samples saved.\n")
  time.sleep(1)

