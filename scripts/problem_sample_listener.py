# source : https://gist.github.com/ecnerwala/ffc9b8c3f61e87ca043393a135d7794d

#!/usr/bin/env python3
"""Download and setup problems from Competitive Companion

Usage:
  download_prob.py --echo
  download_prob.py [<name>... | -n <number> | -b <batches> | --timeout <timeout>] [--dryrun]

Options:
  -h --help     Show this screen.
  --echo        Just echo received responses and exit.
  --dryrun      Don't actually create any problems

Download limit options:
  -n COUNT, --number COUNT   Number of problems.
  -b COUNT, --batches COUNT  Number of batches. (Default 1 batch)
  -t TIME, --timeout TIME    Timeout for listening to problems. in seconds
"""

from docopt import docopt

import sys
import http.server
import json
from pathlib import Path
import subprocess
import re

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

    if json_data is None:
        print("Got no data")
    else:
        print("Listen Done!")
    return json_data


NAME_PATTERN = re.compile(r'^(?:Problem )?([A-Z][0-9]*)\b')

def get_prob_name(data):
    if 'USACO' in data['group']:
        if 'fileName' in data['input']:
            names = [data['input']['fileName'].rstrip('.in'), data['output']['fileName'].rstrip('.out')]
            if len(set(names)) == 1:
                return names[0]

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
def make_prob(data, name=None):
    if name is None:
        name = get_prob_name(data)

    prob_dir = Path('.')

    print("Saving samples...")
    save_samples(data, prob_dir, name)

    print("Saving samples Done!")

def main():
    arguments = docopt(__doc__)

    dryrun = arguments['--dryrun']
    def run_make_prob(*args, **kwargs):
        nonlocal dryrun
        if dryrun:
            print("[dryrun mode]")
            print(f"make_prob(*args={args}, **kwargs={kwargs})")
            return
        make_prob(*args, **kwargs)

    #kind of wired, I just want to listen onece
    if names := arguments['<name>']:
        print(names)
        data = listen_once()
        run_make_prob(data)

if __name__ == '__main__':
    main()