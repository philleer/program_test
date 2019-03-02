date_string1=`date`
date_str1=${date_string1// /}
year1=${date_str1#*CST}
name=$0
filename=${name%.*}
echo ${filename}
#logn="log_"${filename}_${year1}$1".txt"

(
var=http://www.aaa.com/123.html
vartmp="http://www.aaa.com/123.html"
var1=${var#*//}
var2=${var:0-8:3}
date_string=`date`
date_str=${date_string// /}
year=${date_str#*CST} ) | tee $logn

# (time (../hello/build/hello) | tee log_time.txt) 2>> log_time.txt

# (time (
# START_TIME=$(date +%s.%N)
# ../hello/build/hello
# END_TIME=$(date +%s.%N)
# ELAPSED_TIME=$(echo "$END_TIME-$START_TIME" | bc)
# 
# echo "Totally" $ELAPSED_TIME "s took." 
# echo -e "\n"
# ) | tee $LOG) 2>> $LOG

