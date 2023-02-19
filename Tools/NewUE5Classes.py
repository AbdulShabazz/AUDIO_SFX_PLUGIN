from string import Template
import re

def generate_header_file(line):
	# Parse class name and description from line
	class_name, description = line.split(":")
	class_name = re.sub(" ","",class_name)

	# Generate file name and header content
	file_name = "{class_name}.h".format(class_name=class_name)
	header_content = Template('''#pragma once;

class F$class_name
{
/** $description */
public:
	F$class_name ()
	{
		
	};
};''').safe_substitute(class_name=class_name + "Class", description=description)

	# Write header content to file
	with open(file_name, "w") as header_file:
		header_file.write(header_content)

def main():
	# Read lines from input file
	with open("Classes.txt", "r") as input_file:
		lines = input_file.readlines()

	# Generate header files for each line
	for line in lines:
		if re.match("^\w", line): 
			generate_header_file(line)

if __name__ == "__main__":
	main()
