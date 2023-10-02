#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

using namespace std;
/*! displays the first function in the barrier being executed */
void task(shared_ptr<Semaphore> mutexSem,shared_ptr<Semaphore> barrierSem, int threadCount){

  cout << "first " << endl;
  //put barrier code here
  cout << "second" << endl;
}




int main(void){
  shared_ptr<Semaphore> mutexSem;
  shared_ptr<Semaphore> barrierSem;
  int threadCount = 5;
  mutexSem=make_shared<Semaphore>(1);
  barrierSem=make_shared<Semaphore>(0);
  /*!< An array of threads*/
  vector<thread> threadArray(threadCount);
  /*!< Pointer to barrier object*/

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=thread(task,mutexSem,barrierSem,threadCount);
  }
  
  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
