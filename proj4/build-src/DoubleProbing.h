#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <string>
#include "Utils.h"
#include <set>


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

using namespace std;
template <typename HashedObj>
class LinearHashTable
{
  public:

    LinearHashTable( int size) {
		array.resize(size);
		makeEmpty( );
		totalProbes = 0;
		currentSize = 0;
		totalInsertionAttempts= 0;
		averageClusterSize= 0;
		maxProbesInAnInsert= 0;
	}

    HashedObj getElementAt(int x){
		return array[x].element;
    }

    bool contains( const HashedObj & x ) const
    {
	   return isActive( hashFunction( x ) );
    }

    void makeEmpty( )
    {
	   currentSize = 0;
	   for( int i = 0; i < array.capacity( ); i++ )
		  array[ i ].info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
	    totalInsertionAttempts++;
		  // Insert x as active
		printDebug("Pre-Find", 3);
	   int currentPos = hashFunction( x );
	   printDebug("Post-Find", 3);
	   //findPos will return a non-empty location IF:
	   // we try to insert something twice OR
	   // the same location gets probed for insertion twice, aka 2 collisions
	   printDebug("Attempting inserting at: " + numToString(currentPos), 0);
	   if( isActive( currentPos ) ){
		  return false;
		}
	   currentSize++;
	   array[ currentPos ] = HashEntry( x, ACTIVE );

	   return true;
    }

    int getTotalClusters(){
	    int totalClusters = 0;
	    bool inCluster = false;
	    for(int i = 0; i < array.size(); i++){
			if(array[i].info == ACTIVE && !inCluster){
				totalClusters++;
				inCluster = true;
			}else if(array[i].info != ACTIVE ){
				inCluster = false;
			}
	    }
	    return totalClusters;
    }

    float getAverageClusterSize(){
		//is average cluster size == total cluster sizes / # clusters?
	    // and isn't total cluster size = # of active hashes?
	    return (float)currentSize / (float)getTotalClusters();
    }

    int getSizeOfBiggestCluster(){
	    int biggestClusterSize = 0;
	    int potentialBiggest = 0;
		for(int i = 0; i < array.size(); i++){
			if(array[i].info == ACTIVE){
				potentialBiggest++;
				if(i == array.size() - 1){
					// if we've hit end of current cluster AND end of array
					if(biggestClusterSize < potentialBiggest){
						//check to see if this is biggest so far, if so, make biggest found
						biggestClusterSize = potentialBiggest;
						potentialBiggest = 0;
					}else{
						//otherwise, just reset for new test
						potentialBiggest = 0;
					}
				}
			}else{
				// if we've hit end of current cluster AND end of array
				if(biggestClusterSize < potentialBiggest){
					//check to see if this is biggest so far, if so, make biggest found
					biggestClusterSize = potentialBiggest;
					potentialBiggest = 0;
				}else{
					//otherwise, just reset for new test
					potentialBiggest = 0;
				}
			}
		}
		return biggestClusterSize;

    }

    float getAverageProbesPerInsertion(){
		return (float)totalProbes/(float)totalInsertionAttempts;
    }

    int getTotalProbes(){
	    return totalProbes;
    }

    bool remove( const HashedObj & x )
    {
	   int currentPos = hashFunction( x );
	   if( !isActive( currentPos ) ){
		  return false;
	   }
	   currentSize--;
	   array[ currentPos ].info = DELETED;
	   return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

    int getMaxProbesInAnInsert(){
	    return maxProbesInAnInsert;
    }

private:

    int totalProbes;
    int currentSize;
    int totalInsertionAttempts;
    int averageClusterSize;
    int maxProbesInAnInsert;

    struct HashEntry
    {
	   HashedObj element;
	   EntryType info;

	   HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
		: element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;


    bool isActive( int currentPos ) const
	 { return array[ currentPos ].info == ACTIVE; }

    int hashFunction( const HashedObj & x ){
	   int oldProbeTotal = totalProbes;
	   int offset = 1;
	   int currentPos = myhash( x );
	   int origPos = currentPos;
	   //need to test to make sure the same location isn't probed twice.
	   set<int> testedPositions;
	   totalProbes++;
	   //while probing location is NOT empty and w e haven't tested this location before...
	   while( array[ currentPos ].info != EMPTY && testedPositions.count(currentPos) == 0){
			//NON-LINEAR related code below
			totalProbes++;
			printDebug("Pre-While", 3);
			//To keep track of if we've probed this location before.
			testedPositions.insert(currentPos);
			//we have to reset the position so we can move from it.
			currentPos = origPos;
			//Definitiion of Quadratic Right here.
			currentPos += offset;  // Compute ith probe
			offset++;
			//Debugging necessary for testing proper position testing.
			printDebug("currentPos:  " + numToString(currentPos) + ", offset: " +
					 numToString(offset), 1);
			currentPos = currentPos % array.capacity();
			printDebug("Post-While @ " + numToString(currentPos) , 1);
	   }
	   int maxProbesThisInsert = totalProbes - oldProbeTotal;
	   if(maxProbesThisInsert > maxProbesInAnInsert){
		   maxProbesInAnInsert = maxProbesThisInsert;
	   }
	   printDebug("Out-While", 3);
	   return currentPos;
    }


    int myhash( const HashedObj & x ) const{
	   int hashVal = hash( x );
	   hashVal = hashVal % array.capacity();
	   if( hashVal < 0 ){
		  hashVal += array.capacity( );
		}
	   return hashVal;
    }
};


#endif
