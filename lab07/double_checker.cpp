#include <fcntl.h>
#include <unistd.h>
#include "code_processor.h"
    
void Code_Processor::Double_Check_Internals()
{
  int fd;
  int npn;
  User *u;
  map <string, User *>::iterator uit;
  set <string>::iterator pit;

  npn = 0;
  for (uit = Names.begin(); uit != Names.end(); uit++) {
    u = uit->second;
    for (pit = u->phone_numbers.begin(); pit != u->phone_numbers.end(); pit++) {
      npn++;
      if (Phones.find(*pit) == Phones.end()) {
        cerr << "Error -- phone " << *pit << " from user " << u->username << " is not in Phones.\n";
        exit(1);
      }
      if (Phones[*pit] != u) {
        cerr << "Error -- phone " << *pit << " is not registered to user " << u->username << ".\n";
        exit(1);
      }
    }
  }
  if (npn != Phones.size()) {
    cerr << "Phones.size() does not match the number of user phones.\n";
    exit(1);
  }
  fd = open("/dev/null", O_RDONLY);
  if (fd > 4) {
    cerr << "You have too many files open.\n"; 
    exit(1);
  }
  close(fd);
}
