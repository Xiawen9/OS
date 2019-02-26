#ifndef __LIB_LIBFS_FILECACHE_H
#define __LIB_LIBFS_FILECACHE_H

#include <HashTable.h>
#include "File.h"

/**
 * Cached in-memory file.
 */
typedef struct FileCache
{
    /**
     * @brief Constructor function.
     *
     * @param f File to insert into the cache.
     * @param name Entry name of the File in the parent, if any.
     * @param p Our parent. ZERO if we have no parent.
     */
    FileCache(File *f, const char *n, FileCache *p)
            : file(f), valid(true), parent(p)
    {
        name = n;

        if (p && p != this)
        {
            p->entries.insert(name, this);
        }
    }
    
    /**
     * Comparision operator.
     * @param fc Instance to compare us with.
     * @return True if equal, false otherwise.
     */
    bool operator == (FileCache *fc)
    {
        return file == fc->file;
    }

    /** File pointer. */
    File *file;

    /** Our name */
    String name;
    
    /** Contains childs. */
    HashTable<String, FileCache *> entries;

    /** Is this entry still valid?. */
    bool valid;
    
    /** Parent */
    FileCache *parent;
}
FileCache;

#endif /* __LIB_LIBFS_FILECACHE_H */
