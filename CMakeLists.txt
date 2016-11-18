cmake_minimum_required (VERSION 2.6)
project (SQLite3_UnicodeSN)

add_definitions(-DSQLITE_ENABLE_FTS4_UNICODE61 -DSQLITE_OMIT_LOAD_EXTENSION -DSQLITE_ENABLE_FTS4)
set(COMPILE_FLAGS   "${COMPILE_FLAGS}   -Wall -Werror")

include_directories("libstemmer_c/runtime" ${SQLITE3_WIN_INCLUDE})

aux_source_directory(libstemmer_c/src_c  TOKENIZER_SRC)     # All the different language stemmers
set(TOKENIZER_SRC   ${TOKENIZER_SRC}
                    fts3_unicode2.c
                    fts3_unicodesn.c
                    sqlite3_unicodesn_tokenizer.c
                    libstemmer_c/libstemmer/libstemmer_utf8.c
                    libstemmer_c/runtime/api_sq3.c
                    libstemmer_c/runtime/utilities_sq3.c)

add_library(SQLite3_UnicodeSN  STATIC  ${TOKENIZER_SRC})
