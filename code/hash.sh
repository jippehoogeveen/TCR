gcc -E -P -w -nostdinc file.cpp | md5sum | awk '{print substr($1, length($1)-5, 6)}'
