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