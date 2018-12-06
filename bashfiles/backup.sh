#===========================================================================================
# Bash script to backup /home directory.
# Linux doesn't restrict root access to anything, so you can just throw every single file
# on a partition in a TAR file!
#
#===========================================================================================

exdir="--exclude=/cdrom/* \
	   --exclude=/dev/* \
	   --exclude=/lost+found/* \
	   --exclude=/media/* \
	   --exclude=/mnt/* \
	   --exclude=/proc/* \
	   --exclude=/sys/* \
	   --exclude=/tmp/* \
	   --exclude=/run/* \
	   --exclude=/var/log/* \
	   --exclude=/var/cache/apt/archives \
	   --exclude=/usr/src/linux-headers* \
	   --exclude=/home/cvnewbee/.cache \
	   --exclude=/home/cvnewbee/.cache/* \
	   --exclude=/home/cvnewbee/.config/google-chrome \
	   --exclude=/home/cvnewbee/.local/share/Trash \
	   --exclude=/home/cvnewbee/.bash_* \
	   --exclude=/home/cvnewbee/.thunderbird \
	   --exclude=/home/cvnewbee/.xsession-* \
	   --exclude=/home/cvnewbee/foldertest/* \
	   --exclude=/home/lost+found/* \
	   --exclude=/media/cvnewbee/Seagate \
	   --exclude-caches \
	   --exclude-caches-all \
	   --exclude-caches-under"


# options for command tar
# c - create a new backup archive 
# v - verbose mode, print what it's doing to the screen
# p - preserve the permissions of the files put in the archive for restoration later
# z - compress the backup file with 'gzip' to make it smaller
# j - compress the backup file with 'bzip2', remember to change filename to "backup.tar.bz2"
# f <filename> - specifies where to store the backup "backup.tar.gz" is the filename here

backfile=backup_$(date +%Y%m%d).tar.bz2 
if [ $1 == " " ]; then
		echo "Input error: No backup folder given!"
		printf "\n"
		echo "The right format should be as 'sudo tar cvpjfP backupfile exdir folder'"
		exit 0
else
	echo $exdir
	echo Start to back up /home directory...
	time( sudo tar cvpjfP $backfile $exdir $1 )
	echo Done!
	exit 1
fi

# Error assmbles
# tar: Removing leading '/' from member names
# tar: Removing leading '/' from hard link targets
# Solution to the first two issues: 
# 	add -P option which means --absolute-names: don't strip leading '/'s from file names
# tar: /home/cvnewbee/.dbus: Cannot open: Permission denied.
# Solution:
# 	sudo command lines
# tar: /home/cvnewbee/.gnupg/S.gpg-agent: Socket ignored
# tar: /home/cvnewbee/.local/share/ubuntu-amazon-default/ubuntu-amazon-default/SingletonSocket: socket ignored
# Solution:
# 	...
# tar: Exiting with failure status due to previous errors.

# time consumed around:
# real 30m43.208s
# user 23m48.362s
# sys  0m28.960s

