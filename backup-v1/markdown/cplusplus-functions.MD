函数用法
========

## function call operator

在class中加入operator()使类具有函数的特征

```cpp
#include<iostream>
class mul{
	public:
		mul(int x){
			multiplier=x;
		}
		int operator()(int x) const {
			return x*multiplier;
		}
	private:
		int multiplier;
};
int main(){
	mul test(10);
	std::cout<<test(2)<<std::endl;
}
```

##lamda expression
\[传入的变量列表](函数参数){函数体}(调用);
在\[ ]中声明需要使用的调用体的域中的本地变量，全局变量不需要声明。[=]表示所有的变量以赋值的形式传入，[&]表示所有的变量以引用的形式传入，[=,&j]表示除j外都以赋值传入，[i,&j]，表示i以赋值传入，j以引用传入
第一个()为参数列表
{}中是函数体
第二个()表示调用

```cpp
#include<iostream>
int main(){
	int x=1;
	double y=1.2;
	bool z=false;
	[x,&y](int i){std::cout<<i+x+y<<std::endl;}(1);
	return 0;
}
```

## accumulate
累加, demo 如下所示，可使用vector的迭代器

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main(){
    int can[]={1,2,3,4};
    int r=std::accumulate(can,can+4,0);
    std::cout<<r<<std::endl;
    return 0;
}
```
##distance
返回迭代器之间的距离，demo如下:
```cpp
#include <iostream>
#include <vector>
int main(){
	char a[]={1,2,3,4,5};
	std::vector< int> b={1,2,3,4,5};
	std::cout<<std::distance(a,a+4)<<std::endl;
	std::cout<<std::distance(b.begin(), b.end())<<std::endl;
	return 0;
}
```

##advance
增加迭代器变量值，在list中应使用这个
```cpp
#include <iostream>
#include <vector>
int main(){
	std::vector<int> v={1,2,3,4,5};
	auto b= v.begin();
	std::advance(b,2);
	std::cout<<v[b-v.begin()]<<std::endl;
	return 0;
}
```

##hash
对对象进行hash
```cpp
#include <iostream>
#include <string>
int main(){
	std::hash<std::string> test;
	std::cout<<test("hello")<<std::endl;
	return 0;
}
```
##find
在容器中查找元素

##move
将object转移给其他的变量，leaves the source object with a NULL pointer
```cpp
#include<iostream>

int main(){
	std::string a="abs";
	std::cout<<a<<std::endl;
	std::string b=std::move(a);
	std::cout<<a<<std::endl<<b<<std::endl;
	return 0;
}
```

##函数传入参数，是否会拷贝副本的问题
当调用函数时，在函数的scope中，一般使用的是参数的副本，即在执行函数体之前参数的copy版本会被传入，然而当参数是一个新建的对象而没用变量指向它时，它会直接传入调用的函数中去，而不会传入它的副本，以下代码可以验证这个问题。

```cpp
#include<iostream>

class c{
	int a;
	public:
		c(int x):a(x){}
		c(const c &x){
			a=x.a;
			std::cout<<"copy constructor called"<<std::endl;
		}
};

void func(c x){
	std::cout<<"func called"<<std::endl;
}
int main(){
	c t(10);
	std::cout<<"object with name:"<<std::endl;
	func(t);
	std::cout<<"object without name:"<<std::endl;
	func(c(20));
	return 0;
}
```

##std::mem_fn
将类的成员保存在一个变量中之后调用，"Its functional call takes as first argument an object of type T (or a reference or a pointer to it) and, as additional arguments, the arguments taken by pm (if any). The effect of such a call with fn as first argument are the same as calling fn.*pm (or (*fn).*pm if fn is a pointer), forwarding any additional arguments."

```cpp
#include <iostream>     // std::cout
#include <functional>   // std::mem_fn

struct int_holder {
	 int value;
	 int triple() {return value*3;}
};

int main () {
	 int_holder five {5};

	 // call member directly:
	 std::cout << five.triple() << '\n';

	 // same as above using a mem_fn:
	 auto triple = std::mem_fn (&int_holder::triple);
	 std::cout << triple(five) << '\n';

	 return 0;
}
```
