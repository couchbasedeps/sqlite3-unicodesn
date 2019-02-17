cmake_minimum_required (VERSION 3.9)
project (SQLite3_UnicodeSN)
set(COMPILE_FLAGS   "${COMPILE_FLAGS}   -Wall -Werror")

if(NOT DEFINED SQLITE3_INCLUDE_DIR)
    message(FATAL_ERROR "Cannot build without SQLITE3_INCLUDE_DIR defined")
endif()

set(
    TOKENIZER_SRC   
    libstemmer_c/src_c/stem_ISO_8859_1_danish.c
    libstemmer_c/src_c/stem_ISO_8859_1_dutch.c
    libstemmer_c/src_c/stem_ISO_8859_1_english.c
    libstemmer_c/src_c/stem_ISO_8859_1_finnish.c
    libstemmer_c/src_c/stem_ISO_8859_1_french.c
    libstemmer_c/src_c/stem_ISO_8859_1_german.c
    libstemmer_c/src_c/stem_ISO_8859_1_hungarian.c
    libstemmer_c/src_c/stem_ISO_8859_1_italian.c
    libstemmer_c/src_c/stem_ISO_8859_1_norwegian.c
    libstemmer_c/src_c/stem_ISO_8859_1_porter.c
    libstemmer_c/src_c/stem_ISO_8859_1_portuguese.c
    libstemmer_c/src_c/stem_ISO_8859_1_spanish.c
    libstemmer_c/src_c/stem_ISO_8859_1_swedish.c
    libstemmer_c/src_c/stem_ISO_8859_2_romanian.c
    libstemmer_c/src_c/stem_KOI8_R_russian.c
    libstemmer_c/src_c/stem_UTF_8_danish.c
    libstemmer_c/src_c/stem_UTF_8_dutch.c
    libstemmer_c/src_c/stem_UTF_8_english.c
    libstemmer_c/src_c/stem_UTF_8_finnish.c
    libstemmer_c/src_c/stem_UTF_8_french.c
    libstemmer_c/src_c/stem_UTF_8_german.c
    libstemmer_c/src_c/stem_UTF_8_hungarian.c
    libstemmer_c/src_c/stem_UTF_8_italian.c
    libstemmer_c/src_c/stem_UTF_8_norwegian.c
    libstemmer_c/src_c/stem_UTF_8_porter.c
    libstemmer_c/src_c/stem_UTF_8_portuguese.c
    libstemmer_c/src_c/stem_UTF_8_romanian.c
    libstemmer_c/src_c/stem_UTF_8_russian.c
    libstemmer_c/src_c/stem_UTF_8_spanish.c
    libstemmer_c/src_c/stem_UTF_8_swedish.c
    libstemmer_c/src_c/stem_UTF_8_turkish.c    
    fts3_unicode2.c
    fts3_unicodesn.c
    sqlite3_unicodesn_tokenizer.c
    libstemmer_c/libstemmer/libstemmer_utf8.c
    libstemmer_c/runtime/api_sq3.c
    libstemmer_c/runtime/utilities_sq3.c
    stopwordset.cc
)

add_library(SQLite3_UnicodeSN  STATIC  ${TOKENIZER_SRC})
target_compile_definitions(
    SQLite3_UnicodeSN PRIVATE
    -DSQLITE_ENABLE_FTS4_UNICODE61 
    -DSQLITE_OMIT_LOAD_EXTENSION 
    -DSQLITE_ENABLE_FTS4
)

target_include_directories(
    SQLite3_UnicodeSN PRIVATE
    libstemmer_c/runtime
    ${SQLITE3_INCLUDE_DIR}
)