利用opencv自带的grabCut进行前景提取，也即是背景扣除(background subtraction)

处理单张图像时，要输入的参数有: 
path/to/disimg path/to/task_image result_filename
第一个是要执行的程序，在本文件夹下的build子文件夹下
第二个是待处理图像的路径和文件名
第三个是处理结果要保存成的文件

注意：后两个参数如果设计到不同的图像格式，需要在源文件disimg.cc里再设置一下，然后到build文件夹下进行make之后再执行

处理批量图像时，要输入的参数有：
bash backsub.sh
需要注意的是根据文件夹所在的位置进行bash脚本里图片路径的更改，处理时结果保存到当前文件夹，可以在bash里开头或结尾添加一行语句以查看当前路径
pwd
文件名的保存主要还是脚本文件里字符串函数的应用，去头，去尾，替代子字符串等操作。

<<reference>>
http://www.360doc.com/content/16/0812/15/28378250_582723862.shtml
