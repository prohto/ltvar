#include <ltvar.h>
#include <ijson.h>

int main(){
  std::istringstream in_stream( "{flag:true, money: 123.456,count:\t123,\ndescription:\"anything\",undef:null,list:[]}");
  LTVar value;
  IJson ijson(value);

  in_stream >> ijson;

  LTVarIterator iter = value.begin();
  while( iter != value.end() ){
    std::cout << "Field Name ["<<static_cast<std::string>(iter.first())<<"] Value ["<<static_cast<std::string>(iter.second())<<"]\n";
    iter++;
  }
  for( auto item: value ){
    std::cout << "Value ["<<static_cast<std::string>(item)<<"]\n";
  }
  return 0;
}
