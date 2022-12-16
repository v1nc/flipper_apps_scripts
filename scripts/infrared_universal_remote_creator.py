#!/usr/bin/env python3
# flipper universal remote creation script
# author: v1nc
# create or expand infrared universal remotes
# 1. clone https://github.com/logickworkshop/Flipper-IRDB
# 2. copy existing universal remote file into the current directory (e.g 'projectors.ir')
# 3. run script
# 4 copy new file (e.g. 'projectors.ir') on flipper sd card into 'infrared' directory

from pathlib import Path

def map_name(name):
	if name in name_map:
		return name_map[name]
	return name

# name of the infrared directory, for which a universal remote should be created
universal_type = "Projectors"

# name of the command names that should be included in the universal remote
name_list = ["up", "down", "left", "right", "menu", "ok", "source"]

# map names on other names, that also should be included
name_map = {"input" : "source", "enter": "ok"}

# path to the infrared remotes directory
pathlist = Path(f'Flipper/Infrared/IRDB/{universal_type}').rglob('*.ir')
cmds = []



# loop over all infrared files in the specified directory
for path in pathlist:
	print(path)
	with open(path) as f:
		current_cmd = []
		# loop over all lines, extract commands and add them to the list
		for line in f.readlines():
			if len(current_cmd) == 0:
				if "name:" in line:
					name = line.strip().split(": ")
					if len(name) > 1:
						name = map_name(name[1].lower())
						if name in name_list:
							current_cmd.append(f'name: {name.upper()}')
			else:
				if line.strip() == "#":
					current_cmd.append(line.strip())
					cmds.append(current_cmd)
					current_cmd = []
				else:
					current_cmd.append(line.strip())
	
# write all commands to the existing unverisal remote file
with open(f'{universal_type.lower()}.ir', 'a') as f:
	for cmd in cmds:
		for line in cmd:
			f.write(line+'\n')