#pragma once

#include "../BufferPoolADT.h"
#include "BufferBlock.h"
#include <fstream>
#include <iostream>

class LRUBufferPool : public BufferPoolADT {
private:
	int poolSize;
	int blockSize;
	std::fstream file;
	BufferBlock **pool;
public:
	//Constructor gets the filename of the file to be buffered,
	//opens the file, and instantiates poolSize buffer blocks by
	//reading the file and filling the blocks in order.  When the constructor
	//is done the buffer pool blocks should be full with the beginning
	//contents of the input file.
	LRUBufferPool() {}
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) : poolSize{ poolSize }, blockSize{ blockSize } {
		file.open(filename.c_str(), fstream::in | fstream::binary);
		pool = new BufferBlock*[poolSize];
		for (int i = 0; i < poolSize; i++) {
			file.seekg(i * blockSize);
			char* data = new char[blockSize];
			file.read(data, blockSize);
			pool[i] = new BufferBlock(data, i, blockSize);
		}
	}
	~LRUBufferPool() {
		file.close();
		delete[] pool;
	}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {
		int id = pos / blockSize;
		
		BufferBlock* block;
		int index = this->indexOf(id);
		// Find block
		if (index >= 0) {
			block = pool[index];
		}
		else {
			char* data = new char[blockSize];
			file.seekg(id * blockSize);
			file.read(data, blockSize);
			block = new BufferBlock(data, id, blockSize);
		}

		// Get data, assign it to space
		block->getData(pos - (id * blockSize), sz, space);

		// Update pool with LRU heuristic
		if (index >= 0) {
			// Assign temp to lru block
			BufferBlock* temp = pool[index];
			// Shift all other elements to front, move lru to back
			for (int i = index; i < poolSize; i++) {
				if (i + 1 < poolSize) {
					pool[i] = pool[i + 1];
				}
			}
			pool[poolSize - 1] = temp;
			this->updatePool();
		}
		// Delete last element in buffer 
		// Assign new block to last position 
		// Shift new block to front
		else {
			delete pool[poolSize - 1];
			pool[poolSize - 1] = block;
			this->updatePool();
		}

	}

	// Get index of blocks in pool. If block not in pool return -1
	int indexOf(int id) {
		int index = -1;
		for (int i = 0; i < this->poolSize; i++) {
			if (pool[i]->getID() == id) {
				index = i;
			}
		}
		return index;
	}

	// Update pool to move lru element to front
	// LRU element will always start in back of array
	void updatePool() {
		BufferBlock* temp = pool[0];
		// move LRU element to front
		pool[0] = pool[poolSize - 1];
		for (int i = poolSize - 1; i > 1; i--) {
			pool[i] = pool[i - 1];
		}
		pool[1] = temp;
	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
		for (int i = 0; i < poolSize; i++) {
			std::cout << pool[i]->getID() << " ";
		}
		std::cout << std::endl;
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() {
		return pool[0]->getID();
	}
};