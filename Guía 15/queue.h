#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

template<class T, size_t N>
class Queue 
{
	private:

		T v[N];
		mutex cbMutex;
		condition_variable cvput;
		condition_variable cvget;
		int head;
		int tail;

	public:
		
	Queue()
	{
		head = 0;
		tail = 0;
	}
	
	~Queue()
	{
	}
	
	void push(const T &newT)
	{
		unique_lock<mutex> lock(cbMutex);
		while( (head+1)%N ==tail)
		{
		  cout<<"Chequeando el wait push"<<endl;
		  cvput.wait(lock);
		}
		v[head] = newT;
		head = (head+1)%N;
		lock.unlock();
		cvget.notify_one();
		cout<<"Notifying push"<<endl;
	}

	// 	return pop()       // esta mal el return y deberia recibir un punterop a T como esta abajo
	T & pop()     // <<<<<<<<<<<<  esto estaba mail, decia
	{
		T getT;
		unique_lock<mutex>lock(cbMutex);
		cout<<"Chequeando el queue 1"<<endl;
		while(tail == head)
		{
			cout<<"Chequeando el wait get"<<endl;
			cvget.wait(lock);
		}
		cout<<"Cuantos elementos: "<<(head+N-tail)%N<<endl;
		cout<<"Pop: "<<v[tail]<<endl;
		getT = v[tail];
		tail = (tail+1)%N;
		lock.unlock();
		cvput.notify_one();
		return getT;
	}
};
