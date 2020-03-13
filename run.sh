for((i=0; ;i++)) do
	echo $i
	./gen_f $i > int
	./f < int > out || break
done
