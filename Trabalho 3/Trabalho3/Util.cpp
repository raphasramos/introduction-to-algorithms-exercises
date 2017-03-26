#include "Util.hpp"

namespace Util{

    vector<int> getKeys(map<int,string> &m){
        vector<int> out;
        for(auto e : m)
            out.push_back(e.first);

        return out;
    }

    vector<string> getValues(map<int,string> &m){
        vector<string> out;
        for(auto e : m)
            out.push_back(e.second);

        return out;
    }

}

