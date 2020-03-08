for((i=1;i<=100;i++)) do
	echo $i
	./gen_$1 $i > int
	./$1 < int > out1
	./brute_$1 < int > out2
	diff -w out1 out2 || break
done 
