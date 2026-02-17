#pragma once
#include "ActionData.h"
#include <map>
#include <vector>
#include <string>


typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:
    MenuData();
    void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
    const std::vector<std::string>& getNames() const;
    ActionFunctionType getFunction(const std::string& name);
    const std::string& getDescription(const std::string& name);
private:
    std::vector<std::string> names;
    std::map<std::string,ActionFunctionType> amap;
    std::map<std::string,std::string> dmap;



};