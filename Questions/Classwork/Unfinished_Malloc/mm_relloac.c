void *mm_realloc(void *bp, size_t size)
{
	if(bp == NULL || size == 0) {
		mm_free(bp);
		return NULL;
	}

	if (size > 0){
		size_t oldsize = GET_SIZE(HDRP((bp)));
		size_t newsize = ALIGN(size + OVERHEAD);
		void *n_bp = NEXT_BLKP(bp);
		void *p_bp = PREV_BLKP(bp);
		// if oldsize is greater than newsize
		// so that means we can only copy part of
		// the old memory into the new block
		if(newsize < oldsize) {
				// if next block is allocated
			if(GET_ALLOC(HDRP(n_bp))){
				// if oldsize minus new size is greater than BLOCK SIZE
				// that means we are going to have too much internal
				// fragmentation and we want to split the block into
				// two; one free and one allocated.
				if((oldsize - newsize) >= BLKSIZE){
					PUT(HDRP(bp), PACK(newsize, 1)); // Create new allocated block
					PUT(FTRP(bp), PACK(newsize, 1));
					void *tmp = NEXT_BLKP(bp);
					PUT(HDRP(tmp), PACK(oldsize - newsize, 0)); // Create new free block
					PUT(FTRP(tmp), PACK(oldsize - newsize, 0));
				}
				else { // Otherwise leave it as internal fragmentation!
					PUT(HDRP(bp), PACK(oldsize, 1));
					PUT(FTRP(bp), PACK(oldsize ,1));
				}
				return bp;
			}
			else { // The next block is NOT allocated
				// So we move the appropriate footers and headers to expand
				// free block and shrink the current block
				void *next_bp = NEXT_BLKP(bp);
				size_t c_size = oldsize + GET_SIZE(HDRB(next_bp));
				PUT(HDRP(bp), PACK(newsize, 1));
				PUT(FTRP(bp), PACK(newsize, 1));
				void *tmp = NEXT_BLKP(bp);
				PUT(HDRP(tmp), PACK(c_size - newsize, 0));
				PUT(FTRP(tmp), PACK(c_size - newsize, 0));
				return bp;
			}

		}

		else { // The requested size is greater than the size
			// of the original block.
			void *prev_bp = PREV_BLKP(bp);
			void *next_bp = NEXT_BLKP(bp);
			size_t prev = GET_ALLOC(HDRB(prev_bp));
			size_t nex  = GET_ALLOC(HDRB(next_bp));
			size_t c_size;

			// If the next block is not allocated and this block
			// plus the size of the next block are larger than the 
			// desired size...
			if(!nex && ((c_size = oldsize + GET_SIZE(HDRB(next_bp))) >= newsize)){
				// AND the difference between the combined size and
				// the desired size...
				if((c_size - newsize) >= BLKSIZE){
					// Expand the current block, and leave the 
					// remainder as free space
					PUT(HDRP(bp), PACK(newsize, 1));
					PUT(FTRP(bp), PACK(newsize, 1));
					void *tmp = NEXT_BLKP(bp);
					PUT(HDRP(tmp), PACK(c_size - newsize, 0));
					PUT(FTRP(tmp), PACK(c_size - newsize, 0));
				}
				// Otherwise, internalize the fragmentation
				else
				{
					PUT(HDRP(bp), PACK(c_size, 1));
					PUT(FTRP(bp), PACK(c_size, 1));
				}
				return bp;
			}
			// If the previous block is free and the combined sizes of
			// that block and the current block are greater than the
			// desired size...
			else if(!prev && ((csize = oldsize + GET_SIZE(HDRB(prev_bp))) >= newsize))
				{
					// Copy the memory of the current block to the previous block...
					memcpy(prev_bp, bp, (oldsize - OVERHEAD));
					// If the fragmentation will be less than BLKSIZE,
					// externalize it
					if(c_size - newsize) >= BLKSIZE){
						PUT(HDRP(temp), PACK(newsize, 1));
						PUT(FTRP(temp), PACK(newsize, 1));
						void *tmp1 = GET_NEXT(bp);
						PUT(HDRP(tmp1), PACK(c_size - newsize, 0));
						PUT(FTRP(tmp1), PACK(c_size - newsize, 0));
					}
					// If it's less than that, internalize it.
					else 
					{
						PUT(HDRP(tmp), PACK(c_size, 1));
						PUT(FTRP(tmp), PACK(c_size, 1));
					}
					return tmp;
				}
			// There are no blocks that are free and of sufficient size
			// to hold a block of the desired size
			// OR blocks are free but not of a sufficient size
			else {
				size_t size_align = ALIGN(size + (OVERHEAD)); 
				size_t size_ext;
				void *tmps;
				tmps = mm_malloc(size);
				memcpy(tmps, bp, oldsize - OVERHEAD);
				mm_free(bp);
				return tmps;
				}
			}
		}
	else
	{
		return NULL;
	}
}