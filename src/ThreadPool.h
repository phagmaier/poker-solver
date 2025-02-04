#pragma once
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <atomic>
#include "Node.h"


//Doesn't stop running until counter == total
class ThreadPool{
private:
  std::atomic<unsigned int> counter;
  bool stop=false;
  std::queue<std::function<void()>> tasks;
  std::vector<std::thread> threads;
  std::mutex mtx;
  std::condition_variable cv;
  void enqueue(Node *node);
  void enqueue_children(Node *node);
public:
  explicit ThreadPool();
  void enqueue_all(std::vector<Node> &heads); //pushes back all nodes and memebr func to execute
  //will eventually need a reset function
  //void reset();
};
