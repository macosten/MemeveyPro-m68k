#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <map>


typedef struct AutojerkStrings {
	Str255 strings[4];
} AutojerkStrings;

class Markov {
public:
    void create( char * readBuffer, unsigned int keyLen, unsigned int words ) {
		fileBuffer = std::string(readBuffer);
        if( fileBuffer.length() < 1 ) return;
        createDictionary( keyLen );
        initialized = true;
    }
    AutojerkStrings createText() {
        std::string key, first, second, intermediateResult;
        size_t next;
        std::map<std::string, std::vector<std::string> >::iterator it = dictionary.begin();
        std::advance( it, rand() % dictionary.size() );
        key = ( *it ).first;
        intermediateResult += key;
        while( intermediateResult.length() < 1019 ) { //1019 being the capacity of 4 Str255s, minus one for the '!'.
            std::vector<std::string> d = dictionary[key];
            if( d.size() < 1 ) break;
            second = d[rand() % d.size()];
            if( second.length() < 1 ) break;
			if (intermediateResult.size() + (" " + second).size() < 1019){
				intermediateResult += (" " + second); //Keep going if the strings are small enough.
			} else break;
            next = key.find_first_of( 32, 0 );
            first = key.substr( next + 1 );
            key = first + " " + second;
        }
        intermediateResult += "!";
		
		//Split these strings into 4 (safely).
		std::vector<std::string> intermediateVector = split(intermediateResult, 4);
		
		AutojerkStrings result;
		
		//result.strings[0] = intermediateVector[0].c_str();
		memcpy(result.strings[0], intermediateVector[0].c_str(), intermediateVector[0].length());
		//result.strings[1] = intermediateVector[1].c_str();
		memcpy(result.strings[1], intermediateVector[1].c_str(), intermediateVector[1].length());
		//result.strings[2] = intermediateVector[2].c_str();
		memcpy(result.strings[2], intermediateVector[2].c_str(), intermediateVector[2].length());
		//result.strings[3] = intermediateVector[3].c_str();
		memcpy(result.strings[3], intermediateVector[3].c_str(), intermediateVector[3].length());
		
		return result;
    }
	bool isInitialized(){
		return initialized;
	}
	
	//For file access purposes, we should keep track of the source file's referece number.
	short getRefNumber(){
		return fileRefNum;
	}
	void setRefNumber(short newRefNum){
		fileRefNum = newRefNum;
	}
private:
    void createDictionary( unsigned int kl ) {
        std::string w1, key;
        size_t wc = 0, pos, next;
        next = fileBuffer.find_first_not_of( 32, 0 );
        if( next == std::string::npos ) return;
        while( wc < kl ) {
            pos = fileBuffer.find_first_of( ' ', next );
            w1 = fileBuffer.substr( next, pos - next );
            key += w1 + " ";
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            if( next == std::string::npos ) return;
            wc++;
        }
        key = key.substr( 0, key.size() - 1 );
        while( true ) {
            next = fileBuffer.find_first_not_of( 32, pos + 1 );
            if( next == std::string::npos ) return;
            pos = fileBuffer.find_first_of( 32, next );
            w1 = fileBuffer.substr( next, pos - next );
            if( w1.size() < 1 ) break;
            if( std::find( dictionary[key].begin(), dictionary[key].end(), w1 ) == dictionary[key].end() ) 
                dictionary[key].push_back( w1 );
            key = key.substr( key.find_first_of( 32 ) + 1 ) + " " + w1;
        }
    }
	
	std::vector<std::string> split(std::string const & s, size_t count){
	//Split s into count strings of size as close to equal as possible.
		size_t minsize = s.size()/count;
		int extra = s.size() - minsize * count;
		std::vector<std::string> tokens;
		for(size_t i = 0, offset=0 ; i < count; ++i, --extra){
			size_t size = minsize + (extra>0?1:0);
			if ( (offset + size) < s.size())
				tokens.push_back(s.substr(offset,size));
			else
				tokens.push_back(s.substr(offset, s.size() - offset));
			offset += size;
		}       
		return tokens;
	}
	bool initialized;
    std::string fileBuffer;
    std::map<std::string, std::vector<std::string> > dictionary;
	//Mac-specific info:
	short fileRefNum;
};
