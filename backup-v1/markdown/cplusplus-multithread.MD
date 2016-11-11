c++ concurrency in action
====
##g++ compile
g\+\+ -std=c++11 launch-thread.cpp -o launch-thread -lpthread

##basic thread management
###lanch a thread
we can lanch a thread by passing a parameter which can be function, lamda expression and function call operator
```cpp
#include<iostream>
#include<thread>

void helloWorld(){
	std::cout<<"hello world from function"<<std::endl;
}

class hello{
	public:
		void operator()(){
			std::cout<<"hello world from function call operator"<<std::endl;
		}
};

int main(){
	std::thread testFunction(helloWorld);

	std::thread testLamda([]{
		std::cout<<"hello world from lamda"<<std::endl;
	});

	hello x;
	std::thread testCall(x);

	testFunction.join();
	testLamda.join();
	testCall.join();
		
	return 0;
}
```
###wait all let it run

using join(), local thread will wait until thread to finished.
using detach(), thread will continue run even if local thread is destroyed

###Waiting in exceptional circumstances

thread_guard will be destroyed before thread, so join() will be called in destructor
```cpp
#include<iostream>
#include<thread>

class thread_guard{
	std::thread &t;
	public:
		thread_guard(std::thread &t_):t(t_){
		}
		~thread_guard(){
			if(t.joinable()){
				t.join();
			}
		}
};

int main(){
	std::thread t([](){
		std::cout<<"hello"<<std::endl;
	});
	thread_guard g(t);

	return 0;
}
```

###passing argument
argument is passed by pass a copy into internal storage. If pass a reference, we should use std::ref.
```cpp
#include<iostream>
#include<thread>
void func(int &x){
	x++;
	x++;
}
int main(){
	int x=10;
	std::thread t(func,std::ref(x));
	t.join();
	std::cout<<x<<std::endl;
	return 0;
}
```
##thread management
###hardware_concurrency
This function returns an indication of the number of threads that can truly run concurrently for a given execution of a program. On a multicore system it might be the number of CPU cores, for example.
demo show as follow:
```cpp
#include <iostream>
#include <thread>
int main(){
	std::cout<<std::thread::hardware_concurrency()<<std::endl;
	return 0;
}
```
###thread id
the identifier for a thread can be obtained from its associated std::thread object by calling the get_id() member function;the identifier for the current thread can be obtained by calling std::this_thread::get_id().
demo show as follow:
```cpp
#include <iostream>
#include <thread>
int main(){
	std::cout<<std::this_thread::get_id()<<std::endl;
	std::thread a([]{
		std::cout<<"hello world"<<std::endl;
	});
	std::cout<<a.get_id()<<std::endl;
	a.join();
	return 0;
}
```

##sharing data between threads
###race condition
几个线程的操作同时修改某个对象产生的问题。
解决这个问题有三种方法：当某个线程在修改时，不允许其他线程介入；lock-free programming（复杂）;transaction(c++不支持)