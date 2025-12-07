input_file = input("filename: ")  # your HTML file
output_file = input("output: ")       # output file with client.println() lines

with open(input_file, "r", encoding="utf-8") as f:
    lines = f.readlines()

with open(output_file, "w", encoding="utf-8") as f_out:
    for line in lines:
        line = line.rstrip()           # remove newline
        line = line.replace(' ', '')   # remove all spaces
        line_escaped = line.replace('"', '\\"')  # escape double quotes
        f_out.write(f'client.println("{line_escaped}");\n')
