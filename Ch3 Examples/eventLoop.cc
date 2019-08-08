#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

class EventLoop {
 public:
  EventLoop() { stopWork_ = false; }

  // Push a new task onto the end of the queue
  void addTask(std::function<void()> task) { tasks_.push_back(task); }

  void run() {
    // Reset the stopWork_ flag so that the worker doesn't immediately stop
    stopWork_ = false;
    // Only start a new worker thread if it isn't already running
    if (!worker_.joinable())
      worker_ = std::thread(&EventLoop::processList, this);
  }

  // Stop executing tasks
  void stop() { stopWork_ = true; }

  // Clear the queue
  void clearAll() {
    // Make sure that the thread isn't running before we modify the queue
    stop();
    tasks_.clear();
  }

  // Wait for the worker thread to exit before letting the class destroy itself
  ~EventLoop() {
    if (worker_.joinable()) worker_.join();
  }

 private:
  // Function to be run by the worker thread
  void processList() {
    // Loop while there are elements in the vector and we aren't supposed to
    // stop
    while (tasks_.size() != 0 && !stopWork_) {
      // Call the first task in the vector
      tasks_[0]();
      // Erase the first task in the vector (.begin() points to the first
      // element of the vector)
      tasks_.erase(tasks_.begin());
    }
  }


  // Task queue to be processed by the worker thread
  std::vector<std::function<void()>> tasks_;
  // Worker thread
  std::thread worker_;
  // Communicates to the worker thread that it should stop working when set to
  // true
  bool stopWork_;
};

int main() {
  EventLoop el;

  // Add 5 elements to the queue
  for (int i = 0; i < 5; i++) {
    el.addTask([i]() { std::cout << i << std::endl; });
  }
  // Clear the elements we just added
  el.clearAll();

  // Add 5 more elements to the queue
  for (int i = 5; i < 10; i++) {
    el.addTask([i]() { std::cout << i << std::endl; });
  }

  // Run the event loop
  el.run();

  // Wait for a bit before stopping the event loop
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(100ms);
  el.stop();

  return 0;
}