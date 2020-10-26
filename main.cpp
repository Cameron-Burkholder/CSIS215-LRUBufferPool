/* 
 * File:   main.cpp
 * Author: Professor Terri Sipantzi
 *
 * Created on August 25, 2012, 8:49 AM
 */

#include "constants.h"
#include "./ConsoleApplication1/LRUBufferPool.h"
#include "./ConsoleApplication1/BufferBlock.h"

using namespace std;

int main() {
    //initialize buffer pool
    LRUBufferPool* bp = new LRUBufferPool("mydatafile.txt", POOL_SIZE, BLOCKSIZE);
    
    //get data from the buffer
    char* data = new char[10];
    bp->getBytes(data, 10, 5030);
    printChars(data, 10, 5030/BLOCKSIZE);
    bp->printBufferBlockOrder();
	/*Output should be something like the following:
		My data for block 1 is: "ment all o"
		My buffer block order from most recently used to LRU is:
			1, 0, 2, 3, 4,
	*/
    
	//re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 16500);
    printChars(data, 10, 16500/BLOCKSIZE);
    bp->printBufferBlockOrder();
	/*Output should be something like the following:
		My data for block 4 is: "e for the "
		My buffer block order from most recently used to LRU is:
			4, 1, 0, 2, 3,
	*/
	

	//re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 24640);
    printChars(data, 10, 24640/BLOCKSIZE);
    bp->printBufferBlockOrder();
	/*Output should be something like the following:
		My data for block 6 is: "ent a Buff"
		My buffer block order from most recently used to LRU is:
			6, 4, 1, 0, 2,
	*/
	
	//re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 28700);
    printChars(data, 10, 28700/BLOCKSIZE);
    bp->printBufferBlockOrder();
	
	//re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 16600);
    printChars(data, 10, 16600/BLOCKSIZE);
    bp->printBufferBlockOrder();

    // CAMERON BURKHOLDER - TESTS 
    // LRUBufferPool
    cout << "LRU ID: " << bp->getLRUBlockID() << endl;

    // BufferBlock 
    bp->getBytes(data, 10, 0);
    BufferBlock *block = new BufferBlock(data, 0, BLOCKSIZE);
    char* newData = new char[BLOCKSIZE];
    block->getData(0, BLOCKSIZE, newData);
    cout << "New Data: " << newData << endl;

    cout << "ID: " << block->getID() << endl;
    cout << "Setting ID to 4" << endl;
    block->setID(4);
    cout << "New ID: " << block->getID() << endl;

    cout << "Blocksize (Should be 4096): " << block->getBlocksize() << endl;

    cout << "Getting block: " << block->getBlock() << endl;
    cout << "Setting block to last value of data:" << endl;
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 28700);
    block->setBlock(data);
    cout << "New block: " << block->getBlock() << endl;

	
	//close program
	cout << endl << endl;
	system("pause");
	return 0;
}
