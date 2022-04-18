# scripts

add `export PATH=$PATH:~/scripts/` in your ~/.bashrc

usage:

1.stress test:

  run command `stress test expected generator [number_of_tests]`
  
  for example:
  `stress A Aslow Agen 100`

2.generate contest:

  run command `cf_gen contest_id [problem_letter ...]`
  
 for example:
  `cf_gen 1557`
  `cf_gen 1557 A B C`

3.run sample:

  run command `runcase name`

for example:
  `runcase A`

4 and 5 source : https://gist.github.com/ecnerwala/ffc9b8c3f61e87ca043393a135d7794d

4. listen_contest:
  
  just run `listen_contest [<name>... | -n <number> | -b <batches> | --timeout <timeout>] [--dryrun] [--cpp]` in a contest dir
  
5. listen_problem:
  
  just run `listen_smaple [name] [--cpp]` in a contest dir
  
6.
  
  various.. I don't even remember.
