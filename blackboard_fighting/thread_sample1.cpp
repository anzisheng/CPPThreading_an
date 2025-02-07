#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

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
    thread PeterThread(PeterWriteWithMutex, std::ref(amutex), std::ref(blockboard));
    DannyThread.join();
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