linux bash学习
====
##chmod
change mode, 改变文件的权限
[详情可见博客](http://www.cnblogs.com/younes/archive/2009/11/20/1607174.html)

##hello world
demo 如下
```bash
#!/bin/bash
#hello world
a="hello world"
echo $a
```
## if else
格式为
```bash
if [ ... ]; then
	  ...
elif [ ... ]; then
	  ...
else
	  ...
fi
```
demo如下
```bash
#!/bin/bash
#test if else

#-f ----> if is a file
a="if-else.sh"
if [ -f $a ]; then
	echo "$a is a file"
else
	echo "$a is not a file"
fi

#-lt ----> less than -le -> less equal
b=4
if [ $b -lt 5 ]; then
	echo "$b is less than 5"
else
	echo "$b is great or equal than 5"
fi

#-x ----> if is executable
c="if-else.sh"
if [ -x $c ]; then
	echo "$c is executable"
else
	echo "$c is not executable"
fi
```
##参数列表
$#表示包括$0在内的命令行参数的个数。在Shell中，脚本名称本身是$0，剩下的依次是$0、$1、$2…、${10}、${11}，等等。$*表示整个参数列表，不包括$0，也就是说不包括文件名的参数列表。
```bash
#!/bin/bash
#test parameters
echo $#
echo $0
echo $1
echo $*
```