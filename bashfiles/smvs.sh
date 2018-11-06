#!/bin/sh

date_string=`date`
date_str=${date_string// /}
year=${date_str#*ST}
mon=${date_str:3:3}
day=${date_str:6:1}

# echo $year
# echo $mon
# echo $day

if [ "${mon}" = "Jan" ]; then
	mon="1"
elif [ "${mon}" = "" ]; then
	mon="2"
elif [ "${mon}" = "" ]; then
	mon="3"
elif [ "${mon}" = "" ]; then
	mon="4"
elif [ "${mon}" = "" ]; then
	mon="5"
elif [ "${mon}" = "" ]; then
	mon="6"
elif [ "${mon}" = "" ]; then
	mon="7"
elif [ "${mon}" = "" ]; then
	mon="8"
elif [ "${mon}" = "" ]; then
	mon="9"
elif [ "${mon}" = "" ]; then
	mon="10"
elif [ "${mon}" = "Nov" ]; then
	mon="11"
elif [ "${mon}" = "Dec" ]; then
	mon="12"
fi

dir_date=${year}${mon}${day}

img_dir=/media/cvnewbee/Seagate/Downloads/datasets/der_hass-20140923
tmp_dir=$(basename $img_dir)
scene_dir=${tmp_dir:0:8}

newname=${scene_dir}-${dir_date}_$1
 
# if [ -f ./$newname ]; then
# 	echo The file already exists!!
# else
#  	mkdir $newname
# fi

time(
~/foldertest/mve/apps/makescene/makescene -i $img_dir $newname &&
~/foldertest/mve/apps/sfmrecon/sfmrecon $newname &&
~/foldertest/smvs/app/smvsrecon -S2 $newname &&
~/foldertest/mve/apps/fssrecon/fssrecon $newname/smvs-S2.ply $newname/smvs-surface.ply &&
~/foldertest/mve/apps/meshclean/meshclean $newname/smvs-surface.ply $newname/smvs-clean.ply
)

