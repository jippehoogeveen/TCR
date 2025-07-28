# Last 6 chars of hash should match; var names matter
gcc -E -P -w -nostdinc file.cpp  | tr -d '[:space:]' | md5sum