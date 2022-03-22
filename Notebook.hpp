#include <string>
#include <vector>
#include <map>
#include "Direction.hpp"
#define SIZE 100

using namespace std;


namespace ariel{
        class Row{
            private: 
            char arr[SIZE];
            public:
            Row();
                // for(int i=0; i<SIZE; i++){   //todo: move to cpp file
            //         arr[i] = '_';
            //     }
            // }
        };
        class Page{
            private:
            int capacity;
            vector<Row> page();
            public:
            Page();
                // capacity = 0;
            // }
            void add(int size);
                // capacity += size;
                // for(int i=0; i<size; i++){
                //     this->page.pushback(Row());
                // }
                // this->page.resize(capacity, Row());
            // }
        };
    	class Notebook{
            private:
            vector<Page> note();
		    public:
            Notebook();
		    void write(int page, int row, int col, Direction d, string s);
		    string read(int page, int row, int col, Direction d, int size);
		    void erase(int page, int row, int col, Direction d, int size);
		    void show(int page);
		};
};
