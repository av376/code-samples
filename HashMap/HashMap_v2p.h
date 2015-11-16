// HashMap_v2p class template
using namespace std;

template <typename K, typename V>
class HashMap2{
    public:
        // HashMap constructor
        HashMap2(unsigned long hash_map_size) : hashMapSize(hash_map_size), slotsTaken(0), slotsAdded(0){
            if(hashMapSize < 1){
                printf("%s\n","Invalid hashMap size. Using a default value of 1.");
                hashMapSize = 1;
            }
            hashMap = new HashNode* [hashMapSize]();
        }

        // HashMap destructor
        ~HashMap2(){
            // Destroy all linked-lists in the hashMap
            for (int i = 0; i < hashMapSize; ++i){
                HashNode* entry = hashMap[i];
                while (entry != NULL) {
                    HashNode* prev = entry;
                    entry = entry->getNext();
                    delete prev;
                }
                hashMap[i] = NULL;
            }
            // Destroy the hashMap
            delete [] hashMap;
        }

        // boolean  set(key, value): Stores the given key/value pair in the hash map.
        //                           Returns a boolean value indicating success/failure.
        bool set(const K key, V* value){
            unsigned long hashValue = stringHash(key);
            HashNode* entry = hashMap[hashValue];
            HashNode* prev = NULL;

            // Reach the end of a linked-list or a node with the same given key
            while(entry != NULL && entry->getKey() != key){
                prev = entry;
                entry = entry->getNext();
            }

            if(entry == NULL){
                // If empty, insert a node into the hashMap
                entry = new HashNode(key, value);
                slotsTaken++;

                // And fix linkage...
                if(prev == NULL){
                    // to the hashMap or... 
                    hashMap[hashValue] = entry;
                }else {
                    // to the previous node.
                    prev->setNext(entry);
                    slotsAdded++;
                }
                return true;
            }else if(entry != NULL && entry->getKey() == key){
                // Update the value
                entry->setValue(value);
                return true;
            }else{
                cout << "Error using set: unknown." << endl;
                return false;
            }
        }

        // value*   get(key):       Return the value associated with the given key, or null if none is set.
        V* get(const K key) {
            unsigned long hashValue = stringHash(key);
            HashNode *entry = hashMap[hashValue];

            // Iterate through the linked-list at the given entry
            while (entry != NULL) {
                if (entry->getKey() == key) {
                    return entry->getValue();;
                }
                entry = entry->getNext();
            }
            return NULL;
        }

        // float load(): return the load factor (`(items in hash map)/(size of hashMap + added hashNodes)`)
        float load(){
            return ((float) slotsTaken/(hashMapSize + slotsAdded));
        }

        // delete(key): delete the value associated with the given key, returning 
        //              the value on success or null if the key has no value.
        //
        // I did not want to overload the native 'delete' operator
        V* remove(const K &key){
            unsigned long hashValue = stringHash(key);
            HashNode *entry = hashMap[hashValue];
            HashNode *prev = NULL;

            while(entry != NULL && entry->getKey() != key){
                prev = entry;
                entry = entry->getNext();
            }

            if(entry == NULL){
                // If empty, do nothing
                return NULL;
            }else if(entry != NULL && entry->getKey() == key){
                V* val = entry->getValue();                 // Temporarily store the value
                if(prev == NULL){
                    hashMap[hashValue] = entry->getNext();  // Update hashMap
                }else{
                    prev->setNext(entry->getNext());        // Update prev node
                    slotsAdded--;                           // Update slotsAdded
                }
                delete entry;                               // Delete node
                slotsTaken--;                               // Update slotsTaken
                return val;
            }else{
                cout << "Error using remove: unknown." << endl;
                return NULL;
            }
        }

        void printHashMap(){
            for(int i = 0; i < hashMapSize; i++){
                HashNode *entry = hashMap[i];

                if(entry == NULL){
                    cout << "HashMap[" << i << "]: NULL" << endl;
                }else{
                    cout << "HashMap[" << i << "]: ";
                    while(entry != NULL){
                        cout << entry->getKey() << " -> " << *(entry->getValue()) << ", ";
                        entry = entry->getNext();
                    }
                    cout << "end" << endl;
                }
            }
        }
    private:
        // Classes
        class HashNode{
            public:
                // Constructor
                HashNode(const K newKey, V* newValue) : key(newKey), value(newValue), next(NULL) {}

                K getKey() const{
                    return key;
                }

                V* getValue(){
                    return value;
                }

                void setValue(V* value){
                    HashNode::value = value;
                }

                HashNode *getNext() const{
                    return next;
                }

                void setNext(HashNode *next){
                    HashNode::next = next;
                }
            private:
                K key;
                V* value;
                HashNode* next;
        };

        // Variables
        unsigned long slotsTaken;
        unsigned long slotsAdded;
        unsigned long hashMapSize;
        HashNode **hashMap;

        // Methods
        unsigned long stringHash(const K key){
            // djb2 hash: http://www.cse.yorku.ca/~oz/hash.html
            unsigned long hash = 5381;
            int c, counter = 0;
            while ((c = key[counter++])){
                hash = ((hash << 5) + hash) + c;
            }
            return (hash % hashMapSize);
        }
};