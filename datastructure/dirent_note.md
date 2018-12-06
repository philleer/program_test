
##### NAME
> dirent.h - format of directory entries

##### SYNOPSIS

> \#include < dirent.h >

##### DESCRIPTION

> The internal format of directories is unspecified.
> 
> The < *dirent.h* > header defines the following data type through **typedef**:
> 
> <dl compact=""> <dt>DIR</dt><dd>A type representing a directory stream.</dd></dl>
> 
> It also defines the structure **dirent** which includes the following members:
>     
>     ino_t  d_ino       file serial number
>     char   d_name[]    name of entry
>     
> 
> The type **ino_t** is defined as described in _[<sys/types.h>](systypes.h.html)_.
> 
> The character array **d_name** is of unspecified size, but the number of bytes preceding the terminating null byte will not exceed {NAME_MAX}.
> 
> The following are declared as functions and may also be defined as macros. Function prototypes must be provided for use with an ISO C compiler.
>     
>     int             closedir(DIR *);
>     DIR             *opendir(const char *);
>     struct dirent 	*readdir(DIR *);
>     int            	readdir_r(DIR *, struct dirent *, struct dirent **);
>     void           	rewinddir(DIR *);
>     void            seekdir(DIR *, long int);
>     long int        telldir(DIR *);

---
<p align="center"> <font size="1">UNIX ® is a registered Trademark of The Open Group.</font> </p>
<p align="center"> <font size="1">Copyright © 1997 The Open Group</font> </p>

---
