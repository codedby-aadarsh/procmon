# procmon

A lightweight Linux process monitor written in C.

## What it does
Reads /proc/[pid]/status for every running process and displays 
a live-refreshing table showing PID, name, state, and memory usage.

## Build
make

## Run
./procmon

## What I learned
- How Linux exposes process information through the /proc filesystem
- Using opendir/readdir to iterate /proc directories in C
- Handling ENOENT gracefully when a process disappears mid-read
- Debugging with GDB on a real systems program

