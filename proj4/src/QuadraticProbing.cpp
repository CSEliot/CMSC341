///*File file
// * fle
// */

//#include "QuadraticProbing.h"

//using namespace std;



//// QuadraticProbing Hash table class
////
//// CONSTRUCTION: an approximate initial size or default of 101
////
//// ******************PUBLIC OPERATIONS*********************
//// bool insert( x )       --> Insert x
//// bool remove( x )       --> Remove x
//// bool contains( x )     --> Return true if x is present
//// void makeEmpty( )      --> Remove all items

//template <typename HashedObj>

//QuadraticHashTable::QuadraticHashTable( int size) {
//		QuadraticHashTable::array.resize(size);
//		QuadraticHashTable::makeEmpty( );
//		QuadraticHashTable::totalProbes = 0;
//		QuadraticHashTable::currentSize = 0;
//	}

//bool QuadraticHashTable::contains( const HashedObj & x ) const
//{
//   return QuadraticHashTable::isActive( findPos( x ) );
//}

//void QuadraticHashTable::makeEmpty( )
//{
//   currentSize = 0;
//   for( int i = 0; i < array.capacity( ); i++ )
//	  array[ i ].info = EMPTY;
//}

//    bool insert( const HashedObj & x )
//    {
//		  // Insert x as active
//		printDebug("Pre-Find", 3);
//	   int currentPos = findPos( x );
//	printDebug("Post-Find", 3);
//	   //findPos will return a non-empty location IF:
//	   // we try to insert something twice OR
//	   // the same location gets probed for insertion twice, aka 2 collisions
//	printDebug("Attempting inserting at: " + numToString(currentPos), 0);
//	   if( isActive( currentPos ) ){
//		  return false;
//		}
//	   array[ currentPos ] = HashEntry( x, ACTIVE );

//	   return true;
//    }


//    int getAverageProbesPerInsertion(){
//	    for(int i = 0; i < currentSize; i++){

//	    }
//		return;
//    }

//    int getTotalProbes(){
//	    return totalProbes;
//    }

//    bool remove( const HashedObj & x )
//    {
//	   int currentPos = findPos( x );
//	   if( !isActive( currentPos ) )
//		  return false;

//	   array[ currentPos ].info = DELETED;
//	   return true;
//    }

//    enum EntryType { ACTIVE, EMPTY, DELETED };

//  private:
//    struct HashEntry
//    {
//	   HashedObj element;
//	   EntryType info;

//	   HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
//		: element( e ), info( i ) { }
//    };

//    vector<HashEntry> array;
//    int currentSize;
//    vector<int> averageProbesPerInsertion;
//    int totalProbes;

//    bool isActive( int currentPos ) const
//	 { return array[ currentPos ].info == ACTIVE; }

//    int findPos( const HashedObj & x ) const
//    {
//	    int oldTotalProbes = totalProbes;
//	   int offset = 2;
//	   int currentPos = myhash( x );
//	   //need to test to make sure the same location isn't probed twice.
//	   set<int> testedPositions;
//	   totalProbes = totalProbes + 1;
//		//while probing location is NOT empty and we haven't tested this location before...
//	   while( array[ currentPos ].info != EMPTY && testedPositions.count(currentPos) == 0){
//			totalProbes++;
//			printDebug("Pre-While", 3);
//			testedPositions.insert(currentPos);
//			currentPos += offset;  // Compute ith probe
//			offset = offset*offset;
//			currentPos = currentPos % array.capacity();
//			printDebug("Post-While @ " + numToString(currentPos) , 3);
//	   }
//		averageProbesPerInsertion.insert(totalProbes - oldTotalProbes);
//	   printDebug("Out-While", 3);
//	   return currentPos;
//    }


//    int myhash( const HashedObj & x ) const{
//	   int hashVal = hash( x );
//	   hashVal = hashVal % array.capacity();
//	   if( hashVal < 0 ){
//		  hashVal += array.capacity( );
//		}
//	   return hashVal;
//    }
//};
