#!/usr/bin/python3.4

import glob
import os
import argparse

parser = argparse.ArgumentParser()

parser.add_argument("-r", "--remove_old", action='store_true',
                    help="cleanes old profiler reports")
parser.add_argument("-e", "--executable", type=str,
                    help="executable to profile")
parser.add_argument("-g", "--graph", type=str,
                    help="profiler graph file")
args = parser.parse_args()

if args.remove_old:
	[os.system("rm " + x) for x in glob.glob('callgrind.out.*')]
	[os.system("rm " + x) for x in glob.glob('*.svg')]
	print("Old profiler files cleaned.")

def profile(executable,  graph):
	if executable:
		os.system("valgrind --tool=callgrind ./Lab1_AK2")
		if graph:
			logs = [x for x in glob.glob('callgrind.out.*')]
			os.system("gprof2dot -f callgrind " + logs[0] +" | dot -Tsvg -o "+ graph +".svg")

profile("Lab1_AK2", "output")