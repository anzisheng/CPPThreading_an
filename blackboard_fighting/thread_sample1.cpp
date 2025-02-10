#include <thread>
#include <iostream>
#include <mutex>
using namespace std;
template<typename T>
class MutexSafe{
    private:
    mutex _mutex; //互斥锁
    T* _resource; //保护的资源
    T* operator ->() {}
    T& operator &() {}
    public:
    MutexSafe(T* resource):_resource(resource){}
    ~MutexSafe(){delete _resource;}
    void lock(){
        return _mutex.lock();
    }
    void unlock(){
        return _mutex.unlock();
    }
    bool trylock(){
        return _mutex.try_lock()
    }

    mutex& Mutex(){
        return _mutex;
    }

    template<class SafeT>  
    T& Acquire(unique_lock<SafeT>& lock)
    {
        return *_resource;
    }
};
typedef MutexSafe<std::string> Safe;
void SafeDannyWrite(Safe &safe){
    unique_lock<Safe> lock(safe);
    
}
void PeterWrite(std::string &blackboard)
{
    blackboard += "My ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += "Name ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += "is ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));  
    blackboard += "Peter \n";    
}
void DannyWrite(std::string &blackboard)
{
    blackboard += "My ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += "Name ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += "is ";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));  
    blackboard += "Danny \n";    
}
void PeterWriteWithMutex(mutex& amutex, std::string &blackboard)
{
    amutex.lock();
    PeterWrite(blackboard);
    amutex.unlock();
}
void DannyWriteWithMutex(mutex& amutex, std::string &blackboard)
{
    amutex.lock();
    DannyWrite(blackboard);
    amutex.unlock();

}

void TestNormalSafeLock(){
    std::string blockboard;
    std::mutex amutex;
    thread DannyThread(DannyWriteWithMutex, std::ref(amutex), std::ref(blockboard));
    //thread PeterThread(PeterWriteWithMutex, std::ref(amutex), std::ref(blockboard));
    DannyThread.join();
    thread PeterThread(PeterWrite, std::ref(blockboard));
    PeterThread.join();
    std::cout << blockboard << std::endl;
}


void DemoResourceeConflict(){
    // std::string blackboard;
    // thread DannyThread(DannyWrite, std::ref(blackboard));
    // thread PeterThread(PeterWrite, std::ref(blackboard));
    // DannyThread.join();
    // PeterThread.join();
    // std::cout << blackboard <<std::endl; 
}
int main(){
    //DemoResourceeConflict();
    TestNormalSafeLock();
    return 0;
}