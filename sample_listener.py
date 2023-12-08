# source : https://gist.github.com/ecnerwala/ffc9b8c3f61e87ca043393a135d7794d

#!/usr/bin/python3
"""Download and setup problems from Competitive Companion

Usage:
  download_prob.py --echo
  download_prob.py [<name>... | -n <number> | -b <batches> | --timeout <timeout>] [--dryrun] [--cpp]

Options:
  -h --help     Show this screen.
  --echo        Just echo received responses and exit.
  --dryrun      Don't actually create any problems
  --cpp         Generate cpp files

Download limit options:
  -n COUNT, --number COUNT   Number of problems.
  -b COUNT, --batches COUNT  Number of batches. (Default 1 batch)
  -t TIME, --timeout TIME    Timeout for listening to problems. in seconds
"""

from docopt import docopt

import http.server
import json
from pathlib import Path
import re
import os

# Returns unmarshalled or None
def listen_once(*, timeout=None):
    json_data = None

    class CompetitiveCompanionHandler(http.server.BaseHTTPRequestHandler):
        def do_POST(self):
            nonlocal json_data
            json_data = json.load(self.rfile)

    with http.server.HTTPServer(('127.0.0.1', 10043), CompetitiveCompanionHandler) as server:
        server.timeout = timeout
        server.handle_request()

    if json_data is not None:
        print(f"Got data {json.dumps(json_data)}")
    else:
        print("Got no data")
    return json_data

def listen_many(*, num_items=None, num_batches=None, timeout=None):
    if num_items is not None:
        res = []
        for _ in range(num_items):
            cur = listen_once(timeout=None)
            res.append(cur)
        return res

    if num_batches is not None:
        res = []

        batches = {}
        while len(batches) < num_batches or any(need for need, tot in batches.values()):
            print(f"Waiting for {num_batches - len(batches)} batches:")
            cur = listen_once(timeout=None)
            res.append(cur)

            cur_batch = cur['batch']
            batch_id = cur_batch['id']
            batch_cnt = cur_batch['size']
            if batch_id not in batches:
                batches[batch_id] = [batch_cnt, batch_cnt]
            assert batches[batch_id][0] > 0
            batches[batch_id][0] -= 1

        return res

    res = [listen_once(timeout=None)]
    while True:
        cnd = listen_once(timeout=timeout)
        if cnd is None:
            break
        res.append(cnd)
    return res

NAME_PATTERN = re.compile(r'^(?:Problem )?([A-Z][0-9]*)\b')

def get_prob_name(data):
    if 'url' in data and data['url'].startswith('https://www.codechef.com'):
        return data['url'].rstrip('/').rsplit('/')[-1]

    patternMatch = NAME_PATTERN.search(data['name'])
    if patternMatch is not None:
        return patternMatch.group(1)

    print(f"For data: {json.dumps(data, indent=2)}")
    return input("What name to give? ")

def save_samples(data, prob_dir, prob_name):
    with open(prob_dir / 'problem.json', 'w') as f:
        json.dump(data, f)

    for i, t in enumerate(data['tests'], start=1):
        with open(prob_dir / f'{prob_name}-{i}.in', 'w') as f:
            f.write(t['input'])
        with open(prob_dir / f'{prob_name}-{i}.out', 'w') as f:
            f.write(t['output'])

# Providing name = '.'
def make_prob(cpp, data, name=None):
    if name is None:
        name = get_prob_name(data)

    prob_dir = Path('.')

    if cpp:
        print(f'[CPP MODE] Generating {name}.cpp')
        os.system(f'cp_gen {name}')
        print(f'{name}.cpp generated')

    print("Saving samples...")
    save_samples(data, prob_dir, name)
    print("Samples saved!")

def main():
    arguments = docopt(__doc__)

    if arguments['--echo']:
        while True:
            print(listen_once())
    else:
        dryrun = arguments['--dryrun']
        cpp = arguments['--cpp']
        def run_make_prob(*args, **kwargs):
            nonlocal dryrun
            nonlocal cpp
            if dryrun:
                print(f"make_prob(*args={args}, **kwargs={kwargs})")
                return
            make_prob(cpp, *args, **kwargs)

        if names := arguments['<name>']:
            datas = listen_many(num_items=len(names))
            for data, name in zip(datas, names):
                run_make_prob(data, name)
        elif cnt := arguments['--number']:
            cnt = int(cnt)
            datas = listen_many(num_items=cnt)
            for data in datas:
                run_make_prob(data)
        elif batches := arguments['--batches']:
            batches = int(batches)
            datas = listen_many(num_batches=batches)
            for data in datas:
                run_make_prob(data)
        elif timeout := arguments['--timeout']:
            timeout = float(timeout)
            datas = listen_many(timeout=timeout)
            for data in datas:
                run_make_prob(data)
        else:
            datas = listen_many(num_batches=1)
            for data in datas:
                run_make_prob(data)

if __name__ == '__main__':
    main()

