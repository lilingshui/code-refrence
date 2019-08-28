#include <assert.h>
#include "lock.h"

namespace lilingshui
{
    CMutex::CMutex()
    {
        pthread_mutex_init(&m_mutex, NULL);
        assert(0 == pthread_mutexattr_init(&m_attr));
        pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
        assert(0 == pthread_mutex_init(&m_mutex, &m_attr));
    }

    CMutex::~CMutex()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    void CMutex::Lock() const
    {
        pthread_mutex_lock(&m_mutex);
    }

    void CMutex::Unlock() const
    {
        pthread_mutex_unlock(&m_mutex);
    }

    CAutoLock::CAutoLock(const ILock& m) : m_lock(m)
    {
        m_lock.Lock();
    }

    CAutoLock::~CAutoLock()
    {
        m_lock.Unlock();
    }
}