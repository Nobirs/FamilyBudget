import os

def count_lines_in_file(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        return len(f.readlines())

def count_lines_in_project(directory):
    total_lines = 0
    cpp_files = 0
    h_files = 0

    for root, dirs, files in os.walk(directory):
        for file in files:
            if (file.endswith('.cpp') or file.endswith('.h')) and not file.startswith('moc') and not file.startswith("CMake"):
                file_path = os.path.join(root, file)
                file_lines = count_lines_in_file(file_path)
                total_lines += file_lines
                if file.endswith('.cpp'):
                    cpp_files += 1
                elif file.endswith('.h'):
                    h_files += 1
                print(f'{file:<35}: {file_lines:>10} lines')
    
    print(f'\nTotal lines in .cpp and .h files (excluding moc* files): {total_lines}')
    print(f'Total .cpp files: {cpp_files}')
    print(f'Total .h files: {h_files}')

if __name__ == '__main__':
    project_dir = input("Enter the path to your project directory: ")
    count_lines_in_project(project_dir)
