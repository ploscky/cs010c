#include <iostream>
#include "Jug.h"

using namespace std;


int main() {
   string solution1;
   Jug head1(3 /*Ca*/, 5 /*Cb*/, 4 /*N*/, 1 /*cfA*/, 2 /*cfB*/, 3 /*ceA*/, 4 /*ceB*/, 5 /*cpAB*/, 6 /*cpBA*/);
   if (head1.solve(solution1) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution1 << endl << endl;

   string solution2;
   Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);         
   if(head2.solve(solution2) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution2 << endl;
   return 0;
}