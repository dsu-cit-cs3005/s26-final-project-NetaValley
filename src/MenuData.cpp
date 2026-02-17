#include "MenuData.h"


MenuData::MenuData(){}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
    names.push_back(name);
    amap.insert({name, func});
    dmap.insert({name, description});
}


const std::vector<std::string>& MenuData::getNames() const {
    return names;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
    auto it = amap.find(name);
    if (it != amap.end()) {
        return it->second;
    }
    return 0;
}


const std::string& MenuData::getDescription(const std::string& name) {
    auto it = dmap.find(name);
    if (it != dmap.end()) {
        return it->second;
    }
    static std::string empty = "";
    return empty;
}
