find . -type f \( -name "*.cpp" -o -name "*.cc" \) | while read file; do
    hash=$(gcc -E -P -w -nostdinc "$file" 2>/dev/null  | tr -d '[:space:]' | md5sum | awk '{print substr($1, length($1)-5, 6)}')
    echo "$hash" > "${file}.hash"
done
