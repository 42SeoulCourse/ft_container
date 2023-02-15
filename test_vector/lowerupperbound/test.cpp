// map::lower_bound/upper_bound
#include <iostream>
#include <map>


int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['c']=40;
  mymap['e']=60;
  mymap['g']=80;
  mymap['i']=100;

  itlow=mymap.lower_bound ('a');
  itup=mymap.upper_bound ('a');

//   mymap.erase(itlow,itup);        // erases [itlow,itup)
std::cout << itlow->first << " => " << itlow->second << '\n';
std::cout << itup->first << " => " << itup->second << '\n';

  // print content:
//   for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

  return 0;
}