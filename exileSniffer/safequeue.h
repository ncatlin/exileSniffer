#pragma once
#include "cppsemaphore.h"
//i wanted a platform independent, thread safe queue that you could check without waiting on
//couldn't find one so hacked this up

template <class T>
class SafeQueue
{
public:
	SafeQueue() {};
	~SafeQueue() {};

	void addItem(T * item)
	{
		mymutex.lock();
		q.push_back(item);
		sem.notify();
		mymutex.unlock();
	}

	T *waitItem() {
		sem.wait();
		mymutex.lock();
		T *item = q.dequeue();
		mymutex.unlock();
		return item;

	}

	bool empty() { return q.empty(); }

private:
	QQueue<T *> q;
	semaphore sem;
	std::mutex mymutex;
};
