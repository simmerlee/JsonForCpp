# JsonForCpp
Json for cpp

ATTENTION!!!

This is an incomplete version!

1. Not support '\/' character
2. Not support '\uxxxx' character
3. The performence of string transfer to number is extremly poor!!!
4. Just partially tested.

5. The file archetectrue needed to be polished.
6. Maybe some algorithms could be improved.


Sample usage:

Json json;
json.putString("Hello", "World!");
cout<<json.toString()<<endl;
//output: {"Hello":"World!"}

cout<<json.getString("Hello")<<endl;
// output: World!

string s = "{\"abc\" : \"def\"}"
Json json2;
json2.fromString(s.c_str(), s.length());
cout<<json2.toString()<<endl;
// output: {"abc":"def"}
