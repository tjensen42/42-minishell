echo 1 || echo 2 | echo 3

echo 1 | (echo 2 || echo 3 && echo 4) || echo 5 | echo 6

# Pipe redirected echo
echo 2 > tmp1 && echo 1 | grep 1

echo "1\"2"

("ec"ho 1) | grep 1

< test.txt && ls
