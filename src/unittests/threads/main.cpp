#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::queue<int> q;
std::condition_variable cv;

void producer() {
  int count = 0;
  while(count < 100) {
    std::unique_lock<std::mutex> lock(m);
    q.push(count++);
    lock.unlock();
    cv.notify_one();
    std::cout << "vomitting: " << count << "\n";
  }
}

void consumer() {
  int count = 0;
  while(count != 99) {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock);
    count = q.front();
    q.pop();
    std::cout << "eating: " << count << "\n";
  }
}

int main(int argc, char* argv) {
  std::cout << "starting\n";
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join();
  t2.join();
  std::cout << "finished\n";
}
