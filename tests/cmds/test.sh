mkdir tmp_path_test1 tmp_path_test2
printf '#include <unistd.h>\nint main(){write(1, \"1\\n\", 2);}' > tmp_path_test1/test1.c
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
printf '#include <unistd.h>\nint main(){write(1, \"2\\n\", 2);}' > tmp_path_test2/test2.c
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
export PATH=tmp_path_test1:tmp_path_test2
a.out
export PATH=tmp_path_test2:tmp_path_test1
a.out
/bin/rm -rf tmp_path_test1 tmp_path_test2
