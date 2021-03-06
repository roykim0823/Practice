// Q. Design a hash function that is suitable for words in a dictionary

#include <iostream>
#include <numeric>
#include <random>
#include <string>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

string rand_string(int len) {
  string ret;
  default_random_engine gen((random_device())());
  while (len--) {
    uniform_int_distribution<int> zero_or_one(0, 1);
    uniform_int_distribution<char> dis(0, 26);
    ret += (zero_or_one(gen) ? 'a' : 'A') + dis(gen);
  }
  return ret;
}

// @include
int string_hash(const string& str, int modulus) {
  const int kMult = 997;
  // @exclude
  /*
  return accumulate(str.cbegin(), str.cend(), 0,
    [kMult, modulus](const int &val, const char &c) -> int {
      return (val * kMult + c) % modulus;
    });
  */
  // @include
  int val = 0;
  for (const char& c : str) {
    val = (val * kMult + c) % modulus;	// modules 1<<16
  }
  return val;
}
// @exclude

int main(int argc, char* argv[]) {
  default_random_engine gen((random_device())());
  string str;
  if (argc == 2) {
    str = argv[1];
  } else {
    uniform_int_distribution<int> dis(1, 20);
    str = rand_string(dis(gen));
  }
  cout << "string = " << str << endl;
  cout << string_hash(str, 1 << (16)) << endl;
  return 0;
}
