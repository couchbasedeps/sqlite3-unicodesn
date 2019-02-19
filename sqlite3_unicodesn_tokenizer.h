#ifndef _UNICODESN_TOKENIZER_H_
#define _UNICODESN_TOKENIZER_H_
#include <stdbool.h>


/*
 ** Registers the Unicode Snowball tokenizer as "unicodesn", for use with SQLite's FTS3 or FTS4.
 ** This is for use when compiling the tokenizer directly into an application, instead of as a
 ** separate shared library. Example of usage:
 **   CREATE VIRTUAL TABLE fts USING fts3(text, tokenize=unicodesn "stemmer=russian");
 */
int register_unicodesn_tokenizer(sqlite3 *db);

/*
 ** Returns 1 if there is a supported stemmer with the given name, which can be used as the value
 ** of the "stemmer" parameter; otherwise returns 0.
 ** The name is expected to be a 2-letter ISO language code, or a longer (lowercase) English
 ** country name. For example, "en" and "english" are equivalent, and both return 1.
 */
int unicodesn_isSupportedStemmer(const char *name);

/*
 ** Informs tokenizer instances that the current thread is running a query, not indexing rows.
 ** This affects the parsing of stop-words when the tokenizer is called on the target string of
 ** a MATCH. For example, the stop-word "he" should be removed if the target is "he ran", but
 ** not if it's "he* ran".
 */
void unicodesn_tokenizerRunningQuery(bool);

#endif /* _UNICODESN_TOKENIZER_H_ */
