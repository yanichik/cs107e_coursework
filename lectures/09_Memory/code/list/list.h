#ifndef LIST_H
#define LIST_H

#ifndef NULL
#define NULL 0
#endif

#define Nil(l) ((l)==NULL)

typedef struct list {

  void *car;
  struct list *cdr;

} List;

#define cdr(l)    (l)->cdr
#define cddr(l)   (l)->cdr->cdr
#define cdddr(l)  (l)->cdr->cdr->cdr
#define cddddr(l) (l)->cdr->cdr->cdr->cdr

#define car(l)    (l)->car
#define cadr(l)    (l)->cdr->car
#define caddr(l)   (l)->cdr->cdr->car
#define cadddr(l)  (l)->cdr->cdr->cdr->car
#define caddddr(l) (l)->cdr->cdr->cdr->cdr->car

List *cons(void *car, List *cdr);
int   length(List *list);
List *concat(List *list1, List *list2);
List *reverse(List *list);
List *member(void *element, List *list);
List *insert(void *element, List *list);
List *delete(void *element, List *list);
List *intersection(List *list1, List *list2);
List *lunion(List *list1, List *list2);
List *sort(List *list, int (*compare)(const void *, const void *));
List *copy(List *list);
void freelist(List *list, int (*freecar)(void *));

#define ForAllElements( lp, l ) for( lp=l; lp; lp=(lp)->cdr )

# endif
