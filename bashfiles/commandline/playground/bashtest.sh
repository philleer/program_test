dir_date=$(date +%Y%m%d)
logfile=log_$dir_date.txt

( time(
pwdir=`ls -lhA`
echo $pwdir
if [ $1 = "hello" ]; then
	echo \'hello\'it is!
elif [ $1 = "world" ]; then
	echo \'world\'it is!
else
	echo "Not what we want!"
fi
) | tee $logfile) 2>> $logfile #2>&1 

#================================================ 
# four strings given first
#================================================ 
str1="100"
str2="110"
str3="100"
str4=""

#================================================ 
# judge if the string is null 
#================================================ 
if [ !$str4 ]; then
		echo str4 is null!
fi

#================================================ 
# judge if the two strings are equal
#================================================ 
if [ $str1 == $str3 ]; then
		echo "str1 == str3"
		if [ $str1 != $str2 ]; then
				echo "str1 != str2"
		fi
fi

#================================================ 
# judge if the length of a string is 0
#================================================ 
if [ -z $str4 ]; then
		echo "length of str4 is 0"
		if [ -n $str1 ]; then
				echo "length of str1 is not 0"
		fi
fi

#================================================ 
# logical and/or
#================================================ 
str2="100"
if [[ $str1 = $str3 && $str2 = $str3 ]]; then
		echo "str1 == str2 == str3"
		str2="110"
		if [[ $str1 = $str2 || $str1 = $str3 ]]; then
				echo "str1 == str2 or str1 == str3"
		fi
fi

count=1
while [[ "$count" -le 5 ]]; do
		echo $count
		count=$((count+1))
done

TITLE="System Information Report For $HOSTNAME"
CURRENT_TIME="$(date +"%x %r %z")"
TIMESTAMP="Generated $CURRENT_TIME, by $USER"

function report_uptime {
		echo "<H2>System Uptime</H2>
		<PRE>$(uptime)</PRE>"
		return
}

function report_disk_space {
		echo "<H2>Disk Space Utilization</H2>
		<PRE>$(df -h)</PRE>"
		return
}

function report_home_space {
		echo "<H2>Home Space Utilization</H2>
		<PRE>$(du -h /home/cvnewbee/foldertest)</PRE>"
		return
}
function report_home {
		if [[ "$(id -u)" -eq 0 ]]; then
				echo "<H2>Home Space Utilization (All users)</H2>
				<PRE>$(du -sh /home/*)</PRE>"
		else
				echo "<H2>Home Space Utilization ($USER)</H2>
				<PRE>$(du -sh $HOME)</PRE>"
		fi
		return
}

cat << _EOF_
<HTML>
	<HEAD>
			<TITLE>$TITLE</TITLE>
	</HEAD>
	<BODY>
		<H1>$TITLE</H1>
		<P>$TIMESTAMP</P>
		$(report_uptime)
		$(report_disk_space)
		$(report_home)
	</BODY>
</HTML>
_EOF_

echo "<HTML>
	<HEAD>
		<TITLE>$TITLE</TITLE>
	</HEAD>
	<BODY>
		<H1>$TITLE</H1>
		<P>$TIMESTAMP</P>
		$(report_uptime)
		$(report_disk_space)
		$(report_home_space)
	</BODY>
</HTML>" > ./foo.html 2>&1

google-chrome ./foo.html

