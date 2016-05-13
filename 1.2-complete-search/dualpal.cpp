/*
ID: stonegu1
LANG: C++
TASK: dualpal
*/
#include<iostream>
#include<fstream>
using namespace std;
 
bool legal(int num)
{
  int times=0;
  for (int base=2;base<=10;base++)
    {
      int p=0,que[32],x=num;
      x=num;
      while (x)
	{
      que[++p]=x % base;
	  x=x/base; 
	}
      bool ok=1;
      for (int j=1;ok && (j<=p);j++) ok=(ok && que[j]==que[p-j+1]);
      if (ok) times++;
      if (times>1) return true;
    }
  return false;
}
 
int main()
{
  int s,n;
  ifstream fin("dualpal.in");
  ofstream fout("dualpal.out");
  fin>>n>>s;
  for (int i=s+1;n;i++)
      if (legal(i)) 
	{
	  fout<<i<<endl;
	  n--;
	}
  return 0;
}
