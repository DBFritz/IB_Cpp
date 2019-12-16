#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <string>

using namespace std;

template<class T, size_t N>
    class Queue {
        public:
            std::condition_variable cv;
            bool ready = false;
            size_t size;
            mutex m;
            queue<T> q;
            Queue():size(N){}
            ~Queue(){}
            void put(const T&);
            void get(T*){}
            void get_element (void);
            bool try_put(const T&);
            void go(void){
                std::unique_lock<std::mutex> lck(m);
                ready = true;
                cv.notify_all();
            }
                /*
        template <class Rep, class Period>
            bool try_put_for(const T&, const duration<Rep,Period> &rel_time);
        template <class Clock, class Duration>
            bool try_put_until(const T&, const time_point<Clock,Duration> &abs_time);
            bool try_get(T*);
        template <class Rep, class Period>
            bool try_get_for(T*, const duration<Rep,Period> &rel_time);
        template <class Clock, class Duration>
            bool try_get_until(T*, const time_point<Clock,Duration> &abs_time);*/
};


template<class T, size_t N> void Queue<T,N>::put(const T &a){
    std::unique_lock<std::mutex> lck(m);
    while (!ready) cv.wait(lck);
    if(try_put(a))
        q.push(a);
    cout << "Element " << a << "putted" << endl;
}

template<class T, size_t N> void Queue<T,N>::get_element(void){
    std::unique_lock<std::mutex> lck(m);
    while (!ready) cv.wait(lck);
    if(!q.empty()){
        cout << "Element " << q.front() << "popped" << endl;
        q.pop(); 
    }
    else
        cout << "Queue Empty!" << endl;
}

template<class T, size_t N> bool Queue<T,N>::try_put(const T& a){
    if (q.size() >= size){
        cout << "Size Full" << endl;
        return false;
        }
    else
        return true;
}

int main ()
{
  Queue<int,5> Q;
  thread threads[11];
  
  for (int i=0; i<5; ++i){
    threads[0]=thread([&]{
        Q.put(i);
    });
  }
  /*
  for (int i=0; i<5; ++i){
    threads[0]=thread([&]{
        Q.get_element();
    });
  }

threads[10]=thread([&]{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Q.go();
});

  for (int i = 0; i< 11; ++i){
      threads[i].join();
  }
*/

  return 0;
}