//
//  stopwords.h
//  LiteCore
//
//  Created by Jens Alfke on 11/6/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

#include <stdlib.h>

struct StopWordSet;
typedef struct StopWordSet StopWordSet;

StopWordSet* newStopwordsForLanguage(const char *languageCode, size_t languageCodeLen);
StopWordSet* newStopwordsWithList(const char *list, size_t listLen);

void freeStopwords(StopWordSet*);

int isStopWord(StopWordSet*, const char *word, size_t length);
