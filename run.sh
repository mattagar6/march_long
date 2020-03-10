for((i=1;i<=5;i++)) do
	echo $i
	time ./g < in$i > out$i
done
