#include <thread>
#include <iostream>

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


void DemoResourceeConflict(){
    std::string blackboard;
    thread DannyThread(DannyWrite, std::ref(blackboard));
    thread PeterThread(PeterWrite, std::ref(blackboard));
    DannyThread.join();
    PeterThread.join();
    std::cout << blackboard <<std::endl; 
}
int main(){
    DemoResourceeConflict();
    return 0;
}