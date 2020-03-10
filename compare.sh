for((i=1;i<=100;i++)) do
	echo $i
	./gen_g $i > int
	./g < int > out1
	./g_2 < int > out2
	diff -w out1 out2 || break
done 
