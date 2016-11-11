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