// HashMap_v1p class template
using namespace std;

template <typename K, typename V>
class HashMap {
    public:
        // HashMap constructor
        HashMap(unsigned long hash_map_size) : hashMapSize(hash_map_size), slotsOccupied(0){
            if(hashMapSize < 1){
                cout << "Invalid hashMap size. Using a default value of 1." << endl;
                hashMapSize = 1;
            }
            hashMap = new HashNode* [hashMapSize]();
        }

        // HashMap destructor
        ~HashMap(){
            // Destroy any entries in the hashMap
            for (int i = 0; i < hashMapSize; ++i){
                if(hashMap[i] != NULL){
                    delete hashMap[i];
                }
            }
            // Destroy the hashMap
            delete [] hashMap;
        }

        // boolean  set(key, value): Stores the given key/value pair in the hash map.
        //                           Returns a boolean value indicating success/failure.
        bool set(const K key, V* value){
            unsigned long hashValue = stringHash(key);
            HashNode* entry = hashMap[hashValue];
            
            if (entry == NULL){
                // If empty, insert a node into the hashMap
                entry = new HashNode(key, value);
                hashMap[hashValue] = entry;
                slotsOccupied++;
                return true;
            }else if(entry != NULL && entry->getKey() == key){
                // Update the value
                entry->setValue(value);
                return true;
            }else if(entry != NULL && entry->getKey() != key){
                return false;
            }else{
                cout << "Error using set: unknown." << endl;
                return false;
            }
        }

        // value*   get(key):       Return the value associated with the given key, or null if none is set.
        V* get(const K key) {
            unsigned long hashValue = stringHash(key);
            HashNode *entry = hashMap[hashValue];

            if(entry != NULL && entry->getKey() == key) {
                return entry->getValue();
            }else{
                return NULL;
            }
        }

        // float load(): return the load factor (`(items in hash map)/(size of hash map)`)
        float load(){
            return ((float) slotsOccupied/hashMapSize);
        }

        // delete(key): delete the value associated with the given key, returning 
        //              the value on success or null if the key has no value.
        //
        // I did not want to overload the native 'delete' operator
        V* remove(const K &key){
            unsigned long hashValue = stringHash(key);
            HashNode *entry = hashMap[hashValue];

            if (entry == NULL){
                // If empty, do nothing
                return NULL;
            }else if(entry != NULL && entry->getKey() == key){
                V* val = entry->getValue(); // Temporarily store the value
                delete entry;               // Remove the node;
                hashMap[hashValue] = NULL;  // Update hashMap
                slotsOccupied--;            // Update slotsOccupied
                return val;
            }else if(entry != NULL && entry->getKey() != key){
                cout << "Error using remove: incorrect key match." << endl;
                return NULL;
            }else{
                cout << "Error using remove: unknown." << endl;
                return NULL;
            }
        }

        void printHashMap(){
            for(int i = 0; i < hashMapSize; i++){
                HashNode *entry = hashMap[i];

                if (entry == NULL){
                    cout << "HashMap[" << i << "]: NULL" << endl;
                }else{
                    cout << "HashMap[" << i << "]: " << entry->getKey() << " -> " << *(entry->getValue()) << endl;
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
            private:
                K key;
                V* value;
                HashNode* next;
        };

        // Variables
        unsigned long slotsOccupied;
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