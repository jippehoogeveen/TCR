gcc -E -P -w -nostdinc file.cpp | awk '{gsub(/^[ \t]+/, ""); print}' | md5sum