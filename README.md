# get_next_line
## Description
Calling get_next_line in a loop will then allow you to read the text available on the file descriptor one line at a time until the end of it.
## Usage
You must compile with the flag -D BUFFER_SIZE=xx which will be used as the buffer size for the read calls in get_next_line.
```
git clone https://github.com/ktakada42/get_next_line.git
gcc -D BUFFER_SIZE=xx get_next_line(_bonus).c get_next_line_utils(_bonus).c
```
