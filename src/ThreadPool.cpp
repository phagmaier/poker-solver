#include "ThreadPool.h"

ThreadPool::ThreadPool(){
  unsigned int num_threads = std::thread::hardware_concurrency();
  for (int i=0;i<num_threads;++i){
    threads.emplace_back([this] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(mtx);

          cv.wait(lock, [this] {
            return !tasks.empty() || stop;
          });

          if (stop && tasks.empty()) {
            return;
          }
          task = std::move(tasks.front());
          tasks.pop();
      }

      task();
      }
    });
  }

}


//you will probably also need seperate enque functions for 
//specific things since you will want to have multiple functions
//and multiple things you want also doing this recursive shit may be wrong
//cause 1. you don't want to have to iterate through everything 
//once and then start seems stupid if anything you'r enque should 
//get all terminal nodes first and then add the non recursives
//cause for some things you actually want the terminal nodes first
//also what you could do is store all terminal nodes in a static 
//vector in Node and then keep calling parents
void ThreadPool::enqueue(Node *node){
  {
    std::unique_lock<std::mutex>lock(mtx);
    tasks.emplace(std::move([&node](){
      node->print_node();
    }));
  }
}

//Might not need this
//Because when you enque 
//for a node 
void ThreadPool::enqueue_children(Node *node){
  enqueue(node);
  for (Node *child : node->children){
    enqueue_children(child);
  }
}


void ThreadPool::enqueue_all(std::vector<Node>&heads){
  for (Node &head : heads){
    for(Node *child : head.children){
      enqueue_children(child);
    }
  }
}
