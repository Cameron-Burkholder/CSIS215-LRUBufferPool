#pragma once

#include "../BufferBlockADT.h"

#include <iostream>

class BufferBlock : public BufferblockADT {
private:
	int blockID;
	char* block;
    int size;
public:
    BufferBlock(char* data, int id, int sz = 4096) : block{ data }, blockID{ id }, size{ sz } {}
    virtual ~BufferBlock() {}

    //read the block from pos to pos + sz-1 (or to the end of the block)
    void getData(int pos, int sz, char* data) {
        int end;
        if (pos + sz > this->size) {
            end = this->size - 1;
        }
        else {
            end = pos + sz - 1;
        }
        for (int i = 0; i + pos < end; i++) {
            data[i] = block[i + pos];
        }

    }

    //setID
    void setID(int id) {
        this->blockID = id;
    }

    //getID
    int getID() const {
        return this->blockID;
    }

    //getBlocksize
    int getBlocksize() const {
        return this->size;
    }

    //return the block
    char* getBlock() const {
        return this->block;
    }

    //set the block
    void setBlock(char* blk) {
        this->block = blk;
    }
};