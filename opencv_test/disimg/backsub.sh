
for file in /media/cvnewbee/Seagate/downloads/datasets/image_13a/*
do
	filename=`basename ${file}`
	echo $file
	echo $filename
	../build/disimg $file "result"_${filename}
done
