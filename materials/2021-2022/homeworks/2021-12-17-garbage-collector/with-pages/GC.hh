#pragma once

#include <cstddef>
#include <list>
#include <ios>

using namespace std;

class GC {
  class MemBlock {
  public:
    char* start;
    size_t size;

    MemBlock(char* start, size_t size);
  };

  class MemPage {
    // Track the first byte of the total memory
    char *memory_start;

    // Track all free and allocated blocks for easy searching
    list<MemBlock*> free_blocks;
    list<MemBlock*> allocated_blocks;

    static void dump_list(list<MemBlock*>& list, ostream& out);
    MemBlock* find_block(void *target_memory, list<MemBlock*>& list);
  public:
    MemPage(size_t page_size);
    ~MemPage();

    // Helpers
    size_t total_free_size();
    MemBlock* find_free_block(size_t target_size);
    void* allocate_in_block(MemBlock* block, size_t target_size);
    MemBlock* find_block(void *target_memory);
    void free_block(MemBlock* block);
    void shrink_block(MemBlock* block, size_t new_size);
    void grow_block(MemBlock* block, size_t new_size);

    void dump(ofstream& ofs);
    void dump_all(ofstream& ofs);
  };

  static list<MemPage*> pages;

  // Hardcoded limits
  static const size_t page_size = 1024;
  static const size_t max_pages = 5;

  // Private constructor to prevent instantiation
  GC();

  // Helpers
  static size_t total_free_size();
  static size_t total_allocated_size();
  // static MemBlock* find_block(void *target_memory, list<MemBlock*>& list);
public:
  class InvalidSizeException : public logic_error {
  public:
    InvalidSizeException( const char* what_arg );
  };

  // Used to allocate memory on startup
  static void init();
  // Used to free memory on exit
  static void clear();

  static void *allocate(size_t target_size);
  static void free(void *target_memory);
  static void shrink(void *target_memory, size_t new_size);
  static void grow(void *target_memory, size_t new_size);

  static void dump(string file_path);
  // Extra dump that also lists all free blocks
  static void dump_all(string file_path);
};
