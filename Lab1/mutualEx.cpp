#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

static const int num_threads = 100;
int sharedVariable=0;


/*!  An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/

/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){
  for(int i = 0; i < numUpdates; i++){
    
    // Wait for the semaphore to become available
    firstSem->Wait();
    
    // UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
    
    // Signal that the critical section is done
    firstSem->Signal();
  }
}

int main(void){
  vector<thread> vt(num_threads);

  shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
				    
  /**< Launch the threads  */
  
  for(thread& t: vt){
    t=thread(updateTask,aSemaphore,1000);
  }
  
  cout << "Launched from the main\n";
  
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  cout << sharedVariable << endl;
  return 0;
}
