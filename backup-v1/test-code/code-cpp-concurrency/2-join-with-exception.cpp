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