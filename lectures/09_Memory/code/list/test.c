#include <stdio.h>
#include "list.h"

int 
compare(const void *i, const void *j)
{
  if( *(int *)i < *(int *)j ) return -1;
  if( *(int *)i > *(int *)j ) return  1;
  return 0;
}

int main()
{
  List *l, *list;
  List *mist;
  List *nist;

  nist = cons((void *)1,cons((void *)2,cons((void *)3,NULL)));
  mist = cons((void *)2,cons((void *)4,cons((void *)3,NULL)));
  list = nist;
  ForAllElements( l, list )
    printf( "%d \n", (int)car(l) );
  printf( "member((void *)2,list) = %c \n",
    member((void *)2,list) ? 't' : 'f' );
  printf( "member((void *)5,list) = %c \n",
    member((void *)5,list) ? 't' : 'f' );
  list = delete((void *)1,list);
  list = insert((void *)4,list);
  list = sort(list,compare);
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
  printf( "length(list) = %d \n", length(list) );
  list = reverse(copy(list));
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
  printf( "mist\n" );
  list = mist;
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
  printf( "nist\n" );
  list = nist;
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
  printf( "lunion\n" );
  list = lunion(mist,nist);
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
  printf( "intersection\n" );
  list = intersection(mist,nist);
  ForAllElements( l, list )
    printf( "%d ", (int)car(l) );
  printf( "\n" );
}
