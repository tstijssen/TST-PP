#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <array>
#include <list>
#include <functional>
#include <condition_variable>

namespace nbsdx {
	namespace concurrent {

		template <unsigned ThreadCount = 8>
		class ThreadPool {

			std::array<std::thread, ThreadCount> threads;
			std::list<std::function<void(void)>> queue;

			std::atomic_int jobs_left;
			std::atomic_bool bailout;
			std::atomic_bool finished;
			std::condition_variable job_available_var;
			std::condition_variable wait_var;
			std::mutex wait_mutex;
			std::mutex queue_mutex;

			// take next job in queue, notify main previous job is done
			void Task()
			{
				while (!bailout)
				{
					next_job()();
					--jobs_left;
					wait_var.notify_one();
				}
			}

			std::function<void(void)> next_job()
			{
				std::function<void(void)> res;
				std::unique_lock<std::mutex> job_lock(queue_mutex);

				// wait for job
				job_available_var.wait(job_lock, [this]()->bool {return queue.size() || bailout; });

				if (!bailout)
				{
					res = queue.front();
					queue.pop_front();
				}
				else
				{
					res = [] {};
					++jobs_left;
				}
				return res;
			}

		public:
			ThreadPool() :jobs_left(0), bailout(false), finished(false)
			{
				for (unsigned i = 0; i < ThreadCount; ++i)
				{
					threads[i] = std::thread([this] {this->Task(); });
				}
			}

			~ThreadPool()
			{
				JoinAll();
			}

				inline unsigned Size() const
			{
				return ThreadCount;
			}

			inline unsigned JobsRemaining()
			{
				std::lock_guard<std::mutex> guard(queue_mutex);
				return queue.size();
			}

			void AddJob(std::function<void(void)> job)
			{
				std::lock_guard<std::mutex> guard(queue_mutex);
				queue.emplace_back(job);
				++jobs_left;
				job_available_var.notify_one();
			}

			void JoinAll(bool WaitForAll = true) {
				if (!finished) {
					if (WaitForAll) {
						WaitAll();
					}
					// done, wake up any thread that's
					// waiting for a new job
					bailout = true;
					job_available_var.notify_all();
					for (auto &x : threads)
						if (x.joinable())
							x.join();
					finished = true;
				}
			}

			void WaitAll() {
				if (jobs_left > 0) {
					std::unique_lock<std::mutex> lk(wait_mutex);
					wait_var.wait(lk, [this] { return this->jobs_left == 0; });
					lk.unlock();
				}
			}
		};
	}	// namespace concurrent
}	// namespace nbsdx