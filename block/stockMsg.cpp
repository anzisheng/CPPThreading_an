#include <queue>
#include <mutex>
using namespace std;

template<typename MsgType>
class MsgQueue
{
    private:
    queue<MsgType> _queue;
    mutex _mutex;
    condition_variable  _enqCv;
    condition_varibale  _deqCv;
    int _limit;
    public:
    MsgQueue(int limit =3):_limit(limit){}
    void Enqueue(MsgType & msg)
    {
        unique_lock<mutex> lock(_mutex);
        if(_queue.size >= _limit)
        {
            cout << "queue is full, wait ...";
            _enqCv.wait(lock);
        }
        _queue.push(msg);
        _deqCv.nofify_one();
    }
};

MsgType Dequeue()
{
    unique_lock<mutex> lock(_mutex);
    if(_queue.empty())
    {
        std::cout << "queue is empty, wait()..." <<endl;
        _deqCv.wait(lock);
    }
    MsgType msg = _queue.front();
    _queue.pop();
    _enqCV.notify_one();
    return msg;
}

typedef MsgQueue<StockPrice> StockMsgQType;

void StockPriceProcuderThread(StockMsgQType msgQueue)
{
    for (size_t i = 0; i < 10; i++)
    {
        {
        StockPrice stock("APPL", abs(rand() %100));
        msgQueue.Engueue(stock);
        }
        std::cout <<": stoke price ￥" << stock.price <<" is added to the queue" <<std::endl;
        std::this_thread::sleep_for(std::chrono::millseconds(rand()%10));
    }
    StockPrice endStock("APPL", -1);
    msgQueue.Enqueue(endStock);
    std::cout << "Announce market closed" <<std::endl;

}
void DannyReadStock_Sell(StockMsgQType& msgQueue)
{
    while (true)
    {
        /* code */
        StockPrice  stock = msgQueue.Dequeue();
        std::cout << "Danny read stock price: " << stock.price <<std::endl;
        if (stock.price > 90)
        {
            //sell 
            std::cout <<", sell at price:" << stock.price <<std::endl;

        }
        else if(stock.price < 0)
        {
            std::cout << "marked closed" <<std::endl;
            break;
        }
        else if (stock.price > 0 && stock.price > 10)
        {
            cout << "buy it ,at  $" << stock.price << endl;         
        }
        else
        {
            cout << "do nothing" <<endl;
        }
        

        
    }
    

}
void TestSockMsgUpdte(){
    MsgQueue<StockPrice> msgQ;
    thread StockPriceProcuderThread(StockPriceProcuder, std::ref(msgQ));
    thread DannyThread(DannyReadStock_Sell, std::ref(magQ));
    StockPriceProcuderThread.join();
    DannyThread.join();
    
}