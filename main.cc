#include "passkey.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main(int, char**) {
  using namespace passkey;

  //const KeyedData kd{5, "data", RegisteredDataAccess{}};
  //std::cout << kd << std::endl;

  KeyDataStore data_store;
  std::vector<Key> keys;
  keys.emplace_back(data_store.add("hello guv"));
  keys.emplace_back(data_store.add("Oh, what's you got there?"));
  keys.emplace_back(data_store.add("Testing 1 2 3"));

  std::sort(keys.begin(), keys.end());

  for (const auto key : keys) {
    std::cout << key << " -> " << data_store.get(key).value() << std::endl;
  }

  return 0;
}
