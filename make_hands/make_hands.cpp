#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

unsigned int primes[13] = {2,3,5,7,11,13,17,19,23,29,31,37,41};

struct High_five{
  High_five(unsigned int one, unsigned int two, unsigned int three, unsigned int four, unsigned int five){
    vec = {one,two,three,four,five};
    std::sort(vec.rbegin(), vec.rend());
    hash = primes[one] * primes[two] * primes[three] * primes[four] * primes[five];
  }
  std::vector<unsigned int> vec;
  unsigned int hash;
};

unsigned int hash(unsigned int short *vals){
  return primes[vals[0]] * primes[vals[1]] * primes[vals[2]] * primes[vals[3]] * primes[vals[4]];
}

void make_combos(){
  std::ofstream myfile("../data/combos.txt");
  static const unsigned int short total_cards = 7;
  for (int mask = 0; mask < (1 << total_cards); mask++){
    if (std::__popcount(mask) == 5){
      int count = 0;
      for (unsigned int short i=0; i < total_cards; ++i){
        if (mask & 1<<i){
          if (count < 4){
            myfile << i << " ";
          }
          else{
            myfile << i << "\n";
          }
          ++count;
        }
      }
    }
  }
  myfile.close();
}

void make_straights(){
  std::ofstream myfile("../data/straights.txt");
  int count = 1;
  myfile << primes[12] * primes[0] * primes[1] * primes[2] * primes[3] << " ";
  myfile << count << "\n";
  ++count;
  for(int i=0; i<13-4;++i){
    unsigned int hash = primes[i];
    for (int x=1;x<5;++x){
      hash *= primes[i+x];
    }
    myfile << hash << " " << count << "\n";
    ++count;
  }
   
  myfile.close();
}




bool cust_sort_high(High_five &a, High_five &b) {
  for (int i=0;i<4;++i){
    if (a.vec[i] != b.vec[i]){
      return a.vec[i] > b.vec[i];
    }
  }
  return a.vec[4] > b.vec[4];
}


std::vector<High_five> make_high_card() {
  //std::ofstream myFile("../data/highcards.txt");
  int num_cards = 13;
  std::vector<High_five> vec;
  
  for (int one = 0; one < num_cards - 4; ++one) {
    for (int two = one + 1; two < num_cards - 3; ++two) {
      for (int three = two + 1; three < num_cards - 2; ++three) {
        for (int four = three + 1; four < num_cards - 1; ++four) {
          for (int five = four + 1; five < num_cards; ++five) {
            
            unsigned int hash = primes[one] * primes[two] * primes[three] * primes[four] * primes[five];

            //myFile << one << " " << two << " " << three << " " << four << " " << five << " " << hash << "\n";
            vec.emplace_back(High_five(one,two,three,four,five));
          }
        }
      }
    }
  }
  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  /*
  int count = 1;
  for (High_five &i : vec){
    myFile << i.hash << " " << count << "\n"; 
    ++count;
  } 
  int tmp = vec.size()-1;
  myFile.close();
  */
  return vec;
}



std::vector<High_five> make_pair() {
  //std::ofstream myFile("../data/pairs.txt");
  int num_cards = 13;
  std::vector<High_five> vec;

  for (int pair_card = 0; pair_card < num_cards; ++pair_card) {
    for (int kicker1 = 0; kicker1 < num_cards; ++kicker1) {
      if (kicker1 == pair_card) continue;
      for (int kicker2 = kicker1 + 1; kicker2 < num_cards; ++kicker2) {
        if (kicker2 == pair_card) continue;
        for (int kicker3 = kicker2 + 1; kicker3 < num_cards; ++kicker3) {
          if (kicker3 == pair_card) continue;

          unsigned int hash = primes[pair_card] * primes[pair_card] * primes[kicker1] * primes[kicker2] * primes[kicker3];

          vec.emplace_back(High_five(pair_card, pair_card, kicker1, kicker2, kicker3));
        }
      }
    }
  }

  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  /*
    int count = 1;
    for (High_five &i : vec) {
        myFile << i.hash << " " << count << "\n"; 
        ++count;
    } 

    myFile.close();
    */
  return vec;
}



std::vector<High_five> make_two_pair() {
  int num_cards = 13;
  std::vector<High_five> vec;
  for (int one = 0; one < num_cards - 1; ++one) {  // First pair (0 to 11)
    for (int two = one + 1; two < num_cards; ++two) {  // Second pair (one+1 to 12)
      for (int kicker = 0; kicker < num_cards; ++kicker) {  // Kicker (any card)
        if (kicker == one || kicker == two) continue; // Kicker must be different
        vec.emplace_back(High_five(one, one, two, two, kicker));
      }
    }
  }

  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  return vec;
}


std::vector<High_five> make_trips() {
  //std::ofstream myFile("../data/trips.txt");
  int num_cards = 13;
  std::vector<High_five> vec;

  for (int trips_card = 0; trips_card < num_cards; ++trips_card) {
    for (int kicker1 = 0; kicker1 < num_cards; ++kicker1) {
      if (kicker1 == trips_card) continue;
      for (int kicker2 = kicker1 + 1; kicker2 < num_cards; ++kicker2) {
        if (kicker2 == trips_card) continue;
        unsigned int hash = primes[trips_card] * primes[trips_card] * primes[trips_card] * primes[kicker1] * primes[kicker2];

        vec.emplace_back(High_five(trips_card, trips_card, trips_card, kicker1, kicker2));
      }
    }
  }

  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  /*
    int count = 1;
    for (High_five &i : vec) {
        myFile << i.hash << " " << count << "\n"; 
        ++count;
    } 

    myFile.close();
    */
  return vec;
}



std::vector<High_five> make_full_house() {
  //std::ofstream myFile("../data/fullhouse.txt");
  int num_cards = 13;
  std::vector<High_five> vec;

  for (int three = 0; three < num_cards; ++three) { // Three of a kind
    for (int pair = 0; pair < num_cards; ++pair) { // Pair
      if (pair == three) continue; // Pair must be different
        
      unsigned int hash = primes[three] * primes[three] * primes[three] * primes[pair] * primes[pair];

      vec.emplace_back(High_five(three, three, three, pair, pair));
    }
  }

  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  return vec;
}



std::vector<High_five>make_quads() {
    //std::ofstream myFile("../data/quads.txt");
    int num_cards = 13;
    std::vector<High_five> vec;

    for (int four = 0; four < num_cards; ++four) { // Four of a kind
      for (int kicker = 0; kicker < num_cards; ++kicker) { // Kicker
        if (kicker == four) continue; // Kicker must be different
        
        unsigned int hash = primes[four] * primes[four] * primes[four] * primes[four] * primes[kicker];

        vec.emplace_back(High_five(four, four, four, four, kicker));
      }
    }

    std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  /*
    int count = 1;

    for (High_five &i : vec) {
      myFile << i.hash << " " << count << "\n";
      ++count;
    }

    myFile.close();
  */
  return vec;
}


void make_flushes() {
  std::ofstream myFile("../data/flushes.txt");
  int num_cards = 13;
  std::vector<High_five> vec;

  for (int one = 0; one < num_cards - 4; ++one) {
    for (int two = one + 1; two < num_cards - 3; ++two) {
      for (int three = two + 1; three < num_cards - 2; ++three) {
        for (int four = three + 1; four < num_cards - 1; ++four) {
          for (int five = four + 1; five < num_cards; ++five) {
            unsigned int hash = primes[one] * primes[two] * primes[three] * primes[four] * primes[five];
            vec.emplace_back(High_five(one, two, three, four, five));
          }
        }
      }
    }
  }

  std::sort(vec.rbegin(), vec.rend(), cust_sort_high);
  int count = 1;
  for (High_five &i : vec) {
      myFile << i.hash << " " << count << "\n";
      ++count;
  }

  myFile.close();
}

void combine(std::vector<std::vector<High_five>> &vecs){
  std::ofstream outfile("../data/all_pairs.txt");
  
  unsigned int count = 1;
  for(std::vector<High_five> &vec : vecs){
    for(High_five &i : vec){
      outfile << i.hash << " " <<  count << "\n";
      ++count;
    }
  } 
  
  outfile.close();
}

int main(){
  make_combos();
  make_straights();
  
  make_flushes();
  std::vector<std::vector<High_five>> vecs;
  vecs.push_back(make_high_card());
  std::cout << "HIGH CARD: " << make_high_card().size() << "\n";
  vecs.push_back(make_pair());
  std::cout << "ONE PAIR : " << make_pair().size() << "\n";
  vecs.push_back(make_two_pair());
  std::cout << "TWO PAIR : " << make_two_pair().size() << "\n";
  vecs.push_back(make_trips());
  std::cout << "MAKE TRIPS: " << make_trips().size() << "\n";
  vecs.push_back(make_full_house());
  std::cout << "MAKE FULL HOUSE: " << make_full_house().size() << "\n";
  vecs.push_back(make_quads());
  std::cout << "MAKE QUADS: " << make_quads().size() << "\n";
  combine(vecs);
  return 0;
}
