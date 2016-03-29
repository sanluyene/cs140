#include <string>
using namespace std;

class Dnode {
  public:
    string s;
    Dnode *flink;
    Dnode *blink;
};

class Dlist {
  public:
    Dlist();
    ~Dlist();
    int Empty();
    int Size();
    void Push_Front(string s);
    void Push_Back(string s);
    string Pop_Front();
    string Pop_Back();
    Dnode *Begin();
    Dnode *End();
    Dnode *Rbegin();
    Dnode *Rend();
    void Insert_Before(string s, Dnode *n);
    void Insert_After(string s, Dnode *n);
    void Erase(Dnode *n);
  protected:
    Dnode *sentinel;
    int size;
};
