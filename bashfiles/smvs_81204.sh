dir_date=$(date +%Y%m%d%H%M)
img_dir=$(basename $1)
scene_dir=${img_dir%-*}
newname=${scene_dir}-${dir_date}
logfile=log_${newname}.txt
touch $logfile

mvepath=/home/cvnewbee/foldertest/mve/apps
smvspath=/home/cvnewbee/foldertest/smvs/app
temple_neigh_path=/media/cvnewbee/Seagate/smvstest/temple_neighbors
temple_alpha_path=/media/cvnewbee/Seagate/smvstest/temple_alpha
temple_lighting_path=/media/cvnewbee/Seagate/smvstest/temple_lighting
if [ -d /media/cvnewbee/Seagate/smvstest/fountain ]; then
		echo Directory already exists!
else
		mkdir /media/cvnewbee/Seagate/smvstest/fountain
fi
fountain_dir=/media/cvnewbee/Seagate/smvstest/fountain
temple_dir=$fountain_dir

(
time(
$mvepath/makescene/makescene -i $1 $temple_dir/$newname &&
$mvepath/sfmrecon/sfmrecon $temple_dir/$newname &&
$smvspath/smvsrecon -S $2 $3 $4 --threads=2 $temple_dir/$newname &&
if [ $2 = "--neighbors=2" ]; then
	neigh=n2
elif [ $2 = "--neighbors=3" ]; then
	neigh=n3
elif [ $2 = "--neighbors=4" ]; then
	neigh=n4
elif [ $2 = "--neighbors=5" ]; then
	neigh=n5
elif [ $2 = "--neighbors=7" ]; then
	neigh=n7
elif [ $2 = "--neighbors=8" ]; then
	neigh=n8
elif [ $2 = "--neighbors=9" ]; then
	neigh=n9
else
	neigh=n6
fi &&

if [ $3 = "--alpha=2" ]; then
	alp=a2
elif [ $3 = "--alpha=4" ]; then
	alp=a4
elif [ $3 = "--alpha=6" ]; then
	alp=a6
elif [ $3 = "--alpha=8" ]; then
	alp=a8
elif [ $3 = "--alpha=10" ]; then
	alp=a10
else
	alp=a1
fi &&

if [ $4 = "--regularize-lighting=20" ]; then
	light=l2
elif [ $4 = "--regularize-lighting=40" ]; then
	light=l4
elif [ $4 = "--regularize-lighting=60" ]; then
	light=l6
elif [ $4 = "--regularize-lighting=80" ]; then
	light=l8
elif [ $4 = "--regularize-lighting=100" ]; then
	light=lf
else
	light=l0
fi &&

if [ -f $temple_dir/$newname/smvs-B.ply ]; then
	scale=B
	mv $temple_dir/$newname/smvs-B.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
elif [ -f $temple_dir/$newname/smvs-B1.ply ]; then
	scale=B1
	mv $temple_dir/$newname/smvs-B1.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
elif [ -f $temple_dir/$newname/smvs-B2.ply ]; then
	scale=B2
	mv $temple_dir/$newname/smvs-B2.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
elif [ -f $temple_dir/$newname/smvs-S0.ply ]; then
	scale=S0
	mv $temple_dir/$newname/smvs-S0.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
elif [ -f $temple_dir/$newname/smvs-S1.ply ]; then
	scale=S1
	mv $temple_dir/$newname/smvs-S1.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
elif [ -f $temple_dir/$newname/smvs-S2.ply ]; then
	scale=S2
	mv $temple_dir/$newname/smvs-S2.ply $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply -fv
fi &&

$mvepath/fssrecon/fssrecon $temple_dir/$newname/smvs-${scale}-${neigh}-${alp}-${light}.ply $temple_dir/$newname/smvs-surface-${scale}-${neigh}-${alp}-${light}.ply &&
$mvepath/meshclean/meshclean -p10 $temple_dir/$newname/smvs-surface-${scale}-${neigh}-${alp}-${light}.ply $temple_dir/$newname/smvs-clean-${scale}-${neigh}-${alp}-${light}.ply
) | tee $logfile ) 2>> $logfile

mv $logfile $temple_dir/$newname/ -fv
rm -rfv $temple_dir/$newname/views
rm -rfv $temple_dir/$newname/prebundle* $temple_dir/$newname/synth*
echo Finished!...


# date_string=`date`
# # replacement of string
# date_str=${date_string// /}
# # truncate the string until ST
# year=${date_str#*ST}
# # truncate the string from the 3rd position and last for 3 characters
# mon=${date_str:3:3}
# day=${date_str:6:1}

