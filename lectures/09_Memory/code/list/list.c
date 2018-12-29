/*
**	Basic list procesing primitives 
**
**	Author: Pat Hanrahan, University of Wisconsin, 1982
**
**  Updated to c99
*/
#include <stdlib.h>
#include "block.h"
#include "list.h"

static List *listhead = NULL; // for block allocater

List *member( void *element, List *list )
{
    List *l;

    ForAllElements( l, list )
        if( l->car == element )
            return l;

    return NULL;
}

List *intersection( List *list1, List *list2 )
{
    List *l;
    List *result;

    if( list1 == NULL ) return list2;
    if( list2 == NULL ) return list1;

    result = NULL;
    ForAllElements( l, list1 )
        if( member( car(l), list2 ) ) 
            result = cons( car(l), result );
    return result;
}

List *lunion( List *list1, List *list2 )
{
    List *l;
    List *result;

    if( list1 == NULL ) return list2;
    if( list2 == NULL ) return list1;

    result = copy(list2);
    ForAllElements( l, list1 )
        result = insert( car(l), result );
    return result;
}

List *concat( List *list1, List *list2 )
{
    List *l;

    if( list1 == NULL ) return list2;
    if( list2 == NULL ) return list1;

    for( l=list1; cdr(l); l=cdr(l) ) 
        ;
    cdr(l) = list2;
    return list1;
}

List *insert( void *element, List *list )
{
    if( !member( element, list ) )
        list = cons( element, list );
    return list;
}

List *delete( void *element, List *list )
{
    if( car(list) == element )
        return cdr(list);

    if( list )
        for( List *l=list; cdr(l); l=cdr(l) )
            if( car(cdr(l)) == element ) {
                cdr(l) = cdr(cdr(l));
                break;
            }

    return list;
}

List *cons( void *car, List *cdr )
{
    List *cell = (List *)getblock( (Block**)&listhead, sizeof(List) );

    if( cell ) {
        cell->car = car;
        cell->cdr = cdr;
    }

    return cell;
}

List *copy( List *list )
{
    /* Lazy copy ! */
    if( list )
        list = cons( car(list), copy(cdr(list)) );
    return list;
}

int length( List *list )
{
    int n = 0;
    while(list) {
        list=cdr(list);
        n++;
    }
    return n;
}

List *sort( List *list, int (*compare)(const void *, const void *) )
{
    List *l;
    void **a;
    int i;

    if( list ) {
        a = (void **)malloc( (unsigned)(length(list)*sizeof(void *)) );

        i = 0;
        ForAllElements( l, list ) 
            a[i++] = car(l);

        qsort( a, i, sizeof(int), compare );
        i = 0;
        ForAllElements( l, list ) 
            car(l) = a[i++];
        free((void *)a);
    }

    return list;
}

List *reverse( List *list )
{
    List *l, *ln, *lnn;

    l   = NULL;
    ln  = list;
    lnn = cdr(list);
    while( ln ) {
        cdr(ln) = l;
        l   = ln;
        ln  = lnn;
        if( lnn )
            lnn = cdr(lnn);
    }
    return l;
}

void freelist( List *list, int (*freecar)(void *) )
{
    List *l;

    if( freecar ) 
        ForAllElements( l, list )
            (*freecar)(car(l));
  
    while( list ) {
        l = cdr(list);
        putblock( (Block**)&listhead, (Block*)(list) );
        list = l;
    }
}

