for k in {0..100..25}
do
	for j in {2..10..4}
	do
		for i in {1..9..2}
		do
			bash smvs.sh /media/cvnewbee/Seagate/downloads/datasets/fountain_dense/urd \
					--neighbors=$i \
					--alpha=$j \
					--regularize-lighting=$k
		done
	done
done

echo $i*$j*$k reconstruction has been done!

