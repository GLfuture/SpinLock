#ifndef GALAY_SPINLOCK_H
#define GALAY_SPINLOCK_H

#define DELETE_COPY_ASSIGN(className)   className(const className&) = delete;\
                                        className &operator=(const className) = delete;

#include <atomic>
namespace galay
{
    namespace Util
    {
        class SpinLock
        {
        private:
            std::atomic<bool> m_flag = ATOMIC_VAR_INIT(false);

        public:
            SpinLock() = default;
            DELETE_COPY_ASSIGN(SpinLock)

            inline void lock();
            inline void unlock();
        };

        void SpinLock::lock()
        {
            bool expected = false;
            while (!m_flag.compare_exchange_weak(expected, true))
                expected = false;
        }

        void SpinLock::unlock()
        {
            m_flag.store(false);
        }
    }
}

#endif