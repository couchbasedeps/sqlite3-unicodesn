//
//  stopwordset.cc
//  LiteCore
//
//  Created by Jens Alfke on 11/6/17.
//  Copyright © 2017 Couchbase. All rights reserved.
//

extern "C" {
    #include "stopwordset.h"
}
#include <cstring>
#include <string>
#include <unordered_set>


#include "stopwords_en.h"
#include "stopwords_fr.h"


namespace stopwordset {

    static struct {const char *language; const char *words;} kStopWordLists[] = {
        {"en",      kEnglishStopWords},
        {"english", kEnglishStopWords},
        {"fr",      kFrenchStopWords},
        {"french",  kFrenchStopWords},
        { }
    };


    // Simple memory-range type
    struct slice {
        const char * const start;
        size_t const size;

        explicit slice(const char *start_, size_t size_)
        :start(start_), size(size_)
        { }

        bool operator== (const slice &s) const noexcept {
            return size == s.size && memcmp(start, s.start, size) == 0;
        }
    };


    // Functor for computing hash of a slice
    struct sliceHash {
        uint32_t operator() (slice const& s) const noexcept {
            // djb2 hash algorithm
            uint32_t h = 5381;
            auto *pos = (const uint8_t*)s.start, *end = pos + s.size;
            while (pos < end)
                h = (h<<5) + h + *(pos++);
            return h;
        }
    };

}

using namespace stopwordset;


struct StopWordSet {
    // The contents of wordList must remain valid as long as this StopWordSet exists!
    StopWordSet(const char *wordList)
    :_words(200)
    {
        addWords(wordList);
    }

    StopWordSet(slice wordList)
    :_words(200)
    ,_customList(wordList.start, wordList.size)   // copy the string to my own storage
    {
        addWords(_customList.c_str());
    }

    bool contains(const char *word, size_t length) {
        return _words.find(slice{word, length}) != _words.end();
    }

private:
    // The contents of wordList must remain valid as long as this StopWordSet exists.
    void addWords(const char *wordList)
    {
        const char* space;
        do {
            space = strchr(wordList, ' ');
            size_t length = space ? (space-wordList) : strlen(wordList);
            if (length > 0)
                _words.insert(slice{wordList, length});
            wordList = space+1;
        } while (space);
    }

    std::unordered_set<slice, sliceHash> _words;
    std::string _customList;
};


StopWordSet* newStopwordsForLanguage(const char *languageCode, size_t languageCodeLen) {
    if (!languageCode || languageCodeLen == 0)
        return nullptr;
    std::string lang(languageCode, languageCodeLen);
    for (auto i = &kStopWordLists[0]; i->language; ++i) {
        if (strcmp(lang.c_str(), i->language) == 0)
            return new StopWordSet(i->words);
    }
    return nullptr;
}


StopWordSet* newStopwordsWithList(const char *list, size_t listLen) {
    if (!list || listLen == 0)
        return nullptr;
    return new StopWordSet(slice(list, listLen));
}


void freeStopwords(StopWordSet *sw) {
    delete sw;
}


int isStopWord(StopWordSet *sw, const char *word, size_t length) {
    return sw && sw->contains(word, length);
}

