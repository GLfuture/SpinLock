#include<atomic>
class Spain_Lock
{
public:
    Spain_Lock():flag(ATOMIC_FLAG_INIT)
    {}
    void lock(){
        while(flag.test_and_set());
    }
    void unlock(){
        flag.clear();
    }
private:
    std::atomic_flag flag;
};