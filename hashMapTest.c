
#include "src/HashMap.h"
#include "mu_test.h"
#include <stdio.h>

size_t HashFunctionMod(const void* _key);
int EqualityFunctionInt(const void* _firstKey, const void* _secondKey);
int KeyValueActionFunctionIntModGroup(const void* _key, void* _value, void* _context);


typedef struct Context
{
    int m_key;

}Context;

size_t HashFunctionMod(const void* _key)
{
    const int *key = _key;
    
    return ((*key) % 11);

}

int EqualityFunctionInt(const void* _firstKey, const void* _secondKey)
{
    
    return ((*(int *)_firstKey) == (*(int *)_secondKey));
}


int	KeyValueActionFunctionInt(const void* _key, void* _value, void* _context)
{
	int *x = _value;
    /*    Context *cntx = _context;*/
    *x += 1000;
    printf("\nthe next value is: %d\n", *x);
    

	return 1;
}


int KeyValueActionFunctionIntModGroup(const void* _key, void* _value, void* _context)
{
    int *x = _value;
    /*    Context *cntx = _context;*/
    if ((*(int *)_key % 5) == 1)
    {
        *x += 1000;
        printf("\nthe next value is: %d\n", *x);
    }

    return 1;
}


UNIT(Insert_normal)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,4};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, &keyArr[i], &valArr[i]);
        ASSERT_THAT(error == MAP_SUCCESS);

    }


    ASSERT_THAT(HashMap_Size(map) == 4);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT


UNIT(Insert_duplicate_key)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,3};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 3; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/
    error = HashMap_Insert(map, keyArr + i, valArr + i);
    ASSERT_THAT(error == MAP_KEY_DUPLICATE_ERROR);

    ASSERT_THAT(HashMap_Size(map) == 3);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT






UNIT(remove_normal)

    Map_Result error;
    HashMap* map;
    const void *pKey, *pVal;
    int i;
    int keyArr[] = {1,2,3,5};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/

    ASSERT_THAT(HashMap_Size(map) == 4);


    error = HashMap_Remove(map, &keyArr[3], &pKey, &pVal);

    ASSERT_THAT((*(int *)(pKey)) == 5);
    ASSERT_THAT((*(int *)(pVal)) == 55);

    ASSERT_THAT(HashMap_Size(map) == 3);
    HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(remove_till_empty_and_remove)

    Map_Result error;
    HashMap* map;
    const void *pKey, *pVal;
    int i;
    int keyArr[] = {1,2,3,5};
    int valArr[] = {11,22,33,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/

    ASSERT_THAT(HashMap_Size(map) == 4);


    error = HashMap_Remove(map, &keyArr[3], &pKey, &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT((*(int *)(pKey)) == 5);
    ASSERT_THAT((*(int *)(pVal)) == 55);

    ASSERT_THAT(HashMap_Size(map) == 3);


    error = HashMap_Remove(map, &keyArr[2], &pKey, &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT((*(int *)(pKey)) == 3);
    ASSERT_THAT((*(int *)(pVal)) == 33);

    ASSERT_THAT(HashMap_Size(map) == 2);
   
   
    error = HashMap_Remove(map, &keyArr[1], &pKey, &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT((*(int *)(pKey)) == 2);
    ASSERT_THAT((*(int *)(pVal)) == 22);

    ASSERT_THAT(HashMap_Size(map) == 1);
    
    
    error = HashMap_Remove(map, &keyArr[0], &pKey, &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT((*(int *)(pKey)) == 1);
    ASSERT_THAT((*(int *)(pVal)) == 11);

    ASSERT_THAT(HashMap_Size(map) == 0);
    
    error = HashMap_Remove(map, &keyArr[3], &pKey, &pVal);

    ASSERT_THAT(error == MAP_KEY_NOT_FOUND_ERROR);
    ASSERT_THAT(HashMap_Size(map) == 0);
    
    
    error = HashMap_Remove(map, &keyArr[3], &pKey, &pVal);

    ASSERT_THAT(error == MAP_KEY_NOT_FOUND_ERROR);

    ASSERT_THAT(HashMap_Size(map) == 0);
    HashMap_Destroy(&map, NULL, NULL);


END_UNIT

UNIT(for_each)

    Map_Result error;
    size_t numOfInvokes;
    HashMap* map;
    const void *pKey, *pVal; 
    int i;
    int keyArr[] = {1,2,3,5};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/

    ASSERT_THAT(HashMap_Size(map) == 4);

	numOfInvokes = HashMap_ForEach(map, KeyValueActionFunctionInt, NULL);
	ASSERT_THAT(numOfInvokes == 4);

    error = HashMap_Remove(map, &keyArr[3], &pKey, &pVal);

    ASSERT_THAT((*(int *)(pKey)) == 5);
    ASSERT_THAT((*(int *)(pVal)) == 1055);

    ASSERT_THAT(HashMap_Size(map) == 3);
   	putchar('\n');
	numOfInvokes = HashMap_ForEach(map, KeyValueActionFunctionInt, NULL);
	ASSERT_THAT(numOfInvokes == 3);

    HashMap_Destroy(&map, NULL, NULL);

END_UNIT




UNIT(for_each_empty_hash)

    HashMap* map;
	size_t numOfInvokes;

    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);



    ASSERT_THAT(HashMap_Size(map) == 0);


	numOfInvokes = HashMap_ForEach(map, KeyValueActionFunctionInt, NULL);
	ASSERT_THAT(numOfInvokes == 0);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT





UNIT(for_each_after_all_elements_removed)

    Map_Result error;
    HashMap* map;
    const void *pKey, *pVal;
    int i;
    int keyArr[] = {1,2,3,5};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/

    ASSERT_THAT(HashMap_Size(map) == 4);


    for (i = 3; i >= 0; --i)
    {

        error = HashMap_Remove(map, &keyArr[i], &pKey, &pVal);

        ASSERT_THAT((*(int *)(pKey)) == keyArr[i]);
        ASSERT_THAT((*(int *)(pVal)) == valArr[i]);

        ASSERT_THAT(HashMap_Size(map) == (i));
    }

    HashMap_Destroy(&map, NULL, NULL);

END_UNIT

/************************************************/

UNIT(insert_remove_insert_foreach)

    Map_Result error;
    HashMap* map;
    size_t numOfInvokes;
    const void *pKey, *pVal;
    int i;
    int keyArr[] = {1,2,3,5};
    int valArr[] = {22,33,44,55};
    map = HashMap_Create(8, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/

    ASSERT_THAT(HashMap_Size(map) == 4);


    for (i = 3; i >= 0; --i)
    {

        error = HashMap_Remove(map, &keyArr[i], &pKey, &pVal);

        ASSERT_THAT((*(int *)(pKey)) == keyArr[i]);
        ASSERT_THAT((*(int *)(pVal)) == valArr[i]);

        ASSERT_THAT(HashMap_Size(map) == (i));
    }

    ASSERT_THAT(HashMap_Size(map) == 0);

    for (i = 0; i < 4; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }

    ASSERT_THAT(HashMap_Size(map) == 4);

    numOfInvokes = HashMap_ForEach(map, KeyValueActionFunctionInt, NULL);
    ASSERT_THAT(numOfInvokes == 4);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT






UNIT(insert_alot_make_collisions_foreach)

    Map_Result error;
    HashMap* map;
    size_t numOfInvokes;
    /*const void *pKey, *pVal;*/
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/



    numOfInvokes = HashMap_ForEach(map, KeyValueActionFunctionInt, NULL);
    ASSERT_THAT(numOfInvokes == 18);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT




UNIT(find_key_normal)

    Map_Result error;
    HashMap* map;
    const void *pVal;
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/



    error = HashMap_Find(map, &keyArr[1], &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT(*(int *)pVal == 2);

    error = HashMap_Find(map, &keyArr[0], &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT(*(int *)pVal == 1);

    error = HashMap_Find(map, &keyArr[17], &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT(*(int *)pVal == 18);

    error = HashMap_Find(map, &keyArr[11], &pVal);
    ASSERT_THAT(error == MAP_SUCCESS);
    ASSERT_THAT(*(int *)pVal == 12);

HashMap_Destroy(&map, NULL, NULL);

END_UNIT




UNIT(create_normal)

    HashMap* map;

    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

HashMap_Destroy(&map, NULL, NULL);

    /*printf("\n%d\n",i);*/


END_UNIT


UNIT(insert_null)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(NULL, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_UNINITIALIZED_ERROR);

    }
    /*printf("\n%d\n",i);*/
HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(create_null_hashFunc)

    HashMap* map;

    map = HashMap_Create(5, NULL, EqualityFunctionInt);
    ASSERT_THAT(map == NULL);

HashMap_Destroy(&map, NULL, NULL);



END_UNIT


UNIT(create_null_equlityFunc)

    HashMap* map;

    map = HashMap_Create(5, HashFunctionMod, NULL);
    ASSERT_THAT(map == NULL);


HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(create_0_size)

    HashMap* map;

    map = HashMap_Create(0, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map == NULL);


HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(destroy_empty_hash_normal)

    HashMap* map;

    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    /*printf("\n%d\n",i);*/
    HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(destroy_null)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/
    HashMap_Destroy(NULL, NULL, NULL);
    HashMap_Destroy(&map, NULL, NULL);


END_UNIT


UNIT(destroy_full_hash)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/
    HashMap_Destroy(&map, NULL, NULL);


END_UNIT




UNIT(destroy_full_hash_and_destroy_again)

    Map_Result error;
    HashMap* map;
    int i;
    int keyArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    int valArr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
    map = HashMap_Create(5, HashFunctionMod, EqualityFunctionInt);
    ASSERT_THAT(map != NULL);

    for (i = 0; i < 18; ++i)
    {
        error = HashMap_Insert(map, keyArr + i, valArr + i);
        ASSERT_THAT(error == MAP_SUCCESS);

    }
    /*printf("\n%d\n",i);*/
    HashMap_Destroy(&map, NULL, NULL);
    HashMap_Destroy(&map, NULL, NULL);

END_UNIT




TEST_SUITE(framework test)
    TEST(create_normal)
    TEST(insert_null)
    TEST(destroy_empty_hash_normal)
	TEST(create_null_hashFunc)
    TEST(create_null_equlityFunc)
    TEST(create_0_size)
    TEST(destroy_full_hash)
    TEST(destroy_null)
    TEST(destroy_full_hash_and_destroy_again)


    TEST(Insert_normal)
	TEST(Insert_duplicate_key)
    TEST(remove_normal)
    TEST(remove_till_empty_and_remove)
	TEST(for_each)
	TEST(for_each_empty_hash)
    TEST(for_each_after_all_elements_removed)
    TEST(insert_remove_insert_foreach)
    TEST(insert_alot_make_collisions_foreach)
    TEST(find_key_normal)
END_SUITE






