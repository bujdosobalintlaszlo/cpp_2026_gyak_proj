#pragma once
#include <fstream>   
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
// ============================================================================
// REQUIRED CLASS FOR TESTS
// ============================================================================

/**
 * GameState class - Manages character state with file I/O
 *
 * Requirements for tests:
 * - Store: name, class, level, gold, location (strings and ints)
 * - Store: inventory (vector of item names)
 * - saveToFile(filename) - Write state to file, return success
 * - loadFromFile(filename) - Read state from file, return success
 * - Proper const correctness on getters
 * - Pass strings by const reference
 *
 * Tests verify:
 * - Saving and loading preserves all data
 * - File operations return correct success/failure
 * - Const correctness (getters are const)
 * - Parameter passing (const reference for strings)
 *
 * Hints:
 * - Use std::ofstream for writing, std::ifstream for reading
 * - Check is_open() before file operations
 * - Think about data format (how to separate fields?)
 * - Consider validation when loading (valid ranges)
 *
 * Resources:
 * - https://en.cppreference.com/w/cpp/io/basic_fstream
 * - https://en.cppreference.com/w/cpp/io/basic_ofstream
 * - https://en.cppreference.com/w/cpp/io/basic_ifstream
 */

// TODO HOMEWORK (Side Quest): StreamGuard class
// Saves and restores stream formatting state using RAII
class StreamGuard {
    // TODO: Store stream reference, flags, precision, fill character
    // TODO: Constructor saves state
    // TODO: Destructor restores state
};

class GameState {
   private:
		 std::string name;
		 std::string class_;
		 int level;
		 int gold;
		 std::string location;
		 std::vector<std::string> inv;
    // TODO: Add private members
    // Character data: name, class, level, gold, location
    // Inventory: vector of item names

   public:
    // TODO: Constructor
	 // here : name(std::move(name)) could be equaly or more efficent since const ref creates a copy, but move does not .
	 // This is not ideal at big ds.-as or if it is expensive to move.
	 GameState(const std::string& name,const std::string& class_,int level,int gold,const std::string& location) : name(name), class_(class_), level(level), gold(gold), location(location), inv(){};
	 GameState() {};
    // TODO: Getters (must be const methods!)
	 // first const tells that it will return a const string ref and the second const is a member function qualifier 
	 // which means it wont modify the object
	 const std::string& getName() const {
		  return name;
	 }
	 const std::string& getClass() const {
		  return class_;
	 }
	 
	 const std::string& getLocation() const {
		  return location;
	 }

	 const int getLevel() const {
		  return level;
	 }

	 const int getGold() const {
		  return gold;
	 }
	 const std::vector<std::string>& getInv() const{
		  return inv;
	 }
    // TODO: Setters (pass strings by const reference!)
	 void setName(const std::string& name){
		  this->name=name;
	 }
	 void setClass(const std::string& class_){
		  this->class_=class_;
	 }
	 void setLocation(const std::string& location){
		  this->location=location;
	 }
	 void setGold(int gold){
		  this->gold=gold;
	 }
	 void setLevel(int level){
		  this->level=level;
	 }
	 void addItem(const std::string &item){
		  inv.push_back(item);
	 }
    // todo: bool savetofile(const std::string& filename) const
    // write all data to file, return true on success
	 bool savetofile(const std::string& filename) const {
		  //here with the help of this version we wont overwrite the file we will extend it
		  //std::ofstream savefile(filename, std::ios::out | std::ios::app);
		  std::ofstream savefile(filename);
		  if(!savefile) return false;
		  savefile << "# character data" << '\n'
		  << name << '\n'
		  << class_ << '\n'
		  << level << '\n'
		  << gold << '\n'
		  << location << '\n'
		  << "# inventory" << '\n'
		  << inv.size() << '\n';
		  
		  for(const auto& item : inv){
				savefile << item << '\n';
		  }
		  savefile.close();
		  return static_cast<bool>(savefile);
	 }
    // todo: bool loadfromfile(const std::string& filename)
    // read all data from file, return true on success
    // consider: input validation (level range, gold >= 0, etc.)
	 bool readfromfile(const std::string& filename){
		  std::ifstream readfile(filename);
		  std::string line;
		  std::vector<std::string> temp;
		  while(getline(readfile,line) && line != "#inventory"){
				temp.push_back(line);
		  }
		  this->name=temp[0];
		  this->class_=temp[1];
		  int templevel=0;
		  int tempgold=0;
		  try{
				templevel = std::stoi(temp[2]);
				tempgold = std::stoi(temp[3]);
		  }catch(...){
				return false;
		  }
		  this->location=temp[4];
		  if(templevel <= 0) return false;
		  if(tempgold <= 0) return false;
		  this->gold=tempgold;
		  this->level=templevel;
		  this->inv.clear();

		  while (getline(readfile, line)) {
				this->inv.push_back(line);
		  }
		  readfile.close();
		  return true;
	 }
    // TODO HOMEWORK (Side Quest 4): C-style I/O versions
    // bool saveToFileC(const char* filename) const;
    // bool loadFromFileC(const char* filename);
    // Use FILE*, fprintf, fscanf instead of streams

    // TODO: void display() const - show current state
	 void display() const {
		  
	 }
};
