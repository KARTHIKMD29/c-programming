#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


/*Writes key from a line*/
char * getKey(char * line) {
  size_t keyLen = (strchr(line, '=') - line);
  char keyStr[keyLen+1];
  memset(keyStr, '\0', keyLen+1);
  strncpy(keyStr, line, keyLen);
  return strdup(keyStr); //returns allocated key string
}


/*Returns a value string from a line*/
char * getVal(char * line, size_t keyLen) {
  size_t valLen = strchr(line, '\n') - strchr(line, '=') - 1; //lines delimited by \r\n so -2 instead of -1
  char valStr[valLen + 1];
  memset(valStr, '\0', valLen+1);
  strncpy(valStr, (line + keyLen + 1), valLen);
  return strdup(valStr); //return allocated value string
}

/*In readKVs, you will want to open the file, read the lines of text, split them into
key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
each time), close the file, and return the kvarray_t * that has your array.*/
kvarray_t * readKVs(const char * fname) {
  //Begine file opening
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "problem opening file\n");
    exit(EXIT_FAILURE);
  } //End file opening

  //Allocate memory for kvarray_t struct
  kvarray_t * kvArray = malloc(sizeof(kvarray_t));
  kvArray->nPairs = 0; //Maybe start with 1?
  kvArray->pairs = NULL;

  char * line = NULL; //line to search for key-value combo on
  size_t lnSz = 0;
  size_t i = 0;
  char * curKey = NULL;
  char * curVal = NULL;
  //Begin KV reading/writing loop
  while (getline(&line, &lnSz, file) > 0) {
    //New KV pair to read/write
    kvArray->nPairs++;
    i = kvArray->nPairs - 1;

    //Functions to read pairs, retrun key or value string
    curKey = getKey(line);
    curVal = getVal(line, strlen(curKey));

    //Resize array of pointers to kvpair_ts for new KV combo
    kvArray->pairs = realloc(kvArray->pairs, (kvArray->nPairs) * sizeof(kvpair_t*));
    //Allocate memory for new kvpair_t
    kvArray->pairs[i] = malloc(sizeof(kvpair_t));
    //Allocate and copy current key and value to newest kvpair_t
    kvArray->pairs[i]->key = strdup(curKey);
    kvArray->pairs[i]->val = strdup(curVal);

    //Free these in the same loop they were allocated in
    free(curKey);
    free(curVal);
  } //End KV reading/writing loop

  //Free line here since it is only for temporary use and not part of the kvarray_t
  free(line);

  //Begin file closing
  if(fclose(file) != 0) {
    fprintf(stderr, "problem closing file\n");
    exit(EXIT_FAILURE);
  } //End file closing

  return kvArray;
}


/*Next, you will write freeKVs, which should free all the memory allocated by readKVs.
That is,  freeKVs(readKVs(filename)) should not leak any memory.*/
void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->nPairs; i++) {
    free(pairs->pairs[i]->key); //all key strings
    free(pairs->pairs[i]->val); //all value strings
    free(pairs->pairs[i]); //all kvpair_t structs
  }
  free(pairs->pairs); //the array of kvpair_t pointers
  free(pairs); //the kvarray_t
}


/*Third, write printKVs which should take a kvarray_t *, and print out:
 "key = '%s' value = '%s'\n"
for each key/value pair in the array, with the first %s being whatever the key is,
and the second being whatever value (e.g., key = 'Jean Luc Picard' value = 'Captain').*/
void printKVs(kvarray_t * pairs) {
  char * key;
  char * val;
  for (size_t i = 0; i < pairs->nPairs; i++) {
    key = pairs->pairs[i]->key;
    val = pairs->pairs[i]->val;
    printf("key = '%s' value = '%s'\n", key, val);
  }
}


/*Finally, write the lookupValue function, which takes a kvarray_t * and a char * (string).
The char * that is passed in represents a key.  This function searches the kvarray_t 
for a matching key, and if found, returns the corresponding value.  If no match is found,
this function returns NULL.*/
char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->nPairs; i++) {
    if (strcmp(key, pairs->pairs[i]->key) == 0) {
      return (pairs->pairs[i]->val);
    }
  }
  return NULL;
}
