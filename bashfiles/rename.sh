
#iterate to rename the file in the directory
#well to use substring substitute function

for file in 2a_??.jpg
do
	mv -fv "${file}" "${file/_/_0}"
done
