#include <db/Database.hpp>
#include <iostream>

using namespace db;

BufferPool &Database::getBufferPool() { return bufferPool; }

Database &db::getDatabase() {
  static Database instance;
  return instance;
}

void Database::add(std::unique_ptr<DbFile> file) {
  // TODO pa1: add the file to the catalog. Note that the file must not exist.

  std::string fName = file->getName(); // saving passed in file name
  for (const auto& f : fileArr) { // iterating through all files in file array
    std::string currName = f->getName(); // getting current file name
    if (fName == currName) // check to see if file already added
      throw std::runtime_error("File add must be unique."); // throwing exception if so
  }
  fileArr.push_back(std::move(file)); // if file not yet added, add to file array
}

std::unique_ptr<DbFile> Database::remove(const std::string &name) {
  // TODO pa1: remove the file from the catalog. Note that the file must exist.

  for (auto f = fileArr.begin(); f != fileArr.end(); ++f) { // changing approach, because erasing (removing) requires iterator pointing to element
    if (name == (*f)->getName()) { // if found file associated with passed in name
      std::unique_ptr<DbFile> tmp = std::move(*f); // save the file to a tmp variable
      fileArr.erase(f); // erase the file from the file array
      return tmp; // return the erased file (saved into tmp)
    }
  }
  throw std::runtime_error("File to remove must exist."); // if file with associated name not found, throw exception
}

DbFile &Database::get(const std::string &name) const {
  // TODO pa1: get the file from the catalog. Note that the file must exist.

  for (const auto& f : fileArr) { // iterating through all files in file array
    std::string currName = f->getName(); // getting current file name
    if (name == currName) // if passed in file name found
      return *f; // return associated file
  }
  throw std::runtime_error("File get must exist."); // if not found, throw exception
}
