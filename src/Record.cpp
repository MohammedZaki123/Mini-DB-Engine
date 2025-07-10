# include "Record.hpp"

Record::Record(const std::unordered_map<std::string, std::string> &types, std::vector<std::pair<std::string, std::string>>& values, std::string key)
{
    Transformer trans;
    // Nullable value edge case is required
    for(int i = 0 ; i < values.size() ; i++){
        std::string type = types.at(values[i].first);
        if(values[i].second != "null"){
            // for the nullable value of a column
            std::any val = trans.fromStr(type,values[i].second);
            this->vals.emplace(values[i].first,val);
        }
        this->datatypes.emplace(values[i].first, type);
    }
    this->clusteringKey = key;
}

Record::Record(const std::unordered_map<std::string, std::string> &types, std::vector<std::pair<std::string, std::string>> &values)
{
    Transformer trans;
     for(int i = 0 ; i < values.size() ; i++){
        std::string type = types.at(values[i].first);
        if(values[i].second != "null"){
            // for the nullable value of a column
            std::any val = trans.fromStr(type,values[i].second);
            this->vals.emplace(values[i].first,val);
        }
        this->datatypes.emplace(values[i].first, type);
    }
}

Record::Record(const std::unordered_map<std::string, std::any> &values, std::unordered_map<std::string, std::string> types, std::string key)
    : vals(values)
{
    // for the new to be inserted record
    this->clusteringKey = key;
    this->datatypes = types;
}

bool Record::operator==(Record & record)
{
    Decider dec;
    return dec.isEqual(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
}

bool Record::operator<(Record & record)
{
      Decider dec;
    return dec.isLessThan(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
}

bool Record::operator>(Record & record)
{
      Decider dec;
    return dec.isMoreThan(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
}
// ----- Instance Members -----
const std::string& Record::getClusteringKey() const {
    return clusteringKey;
}

void Record::setClusteringKey(const std::string& key) {
    clusteringKey = key;
}

const std::unordered_map<std::string, std::any>& Record::getVals() const {
    return vals;
}

void Record::setVals(const std::unordered_map<std::string, std::any>& v) {
    // Only keys exist in v will affect the same keys in the instance variable vals
     for(auto it = v.begin() ; it != v.end(); it++){
        vals[it->first] = v.at(it->first);
     }
}

// ----- Static Members -----
std::unordered_map<std::string, std::string>& Record::getDatatypes() {
    return datatypes;
}

void Record::setDatatypes(const std::unordered_map<std::string, std::string>& types) {
    datatypes = types;
}

const std::vector<std::string> Record::toString(std::vector<std::string> columns)
{
    // Nullable values is considered 
    Transformer trans;
    std::vector<std::string> result;
    for(std::string col: columns){
       if(!vals.count(col)){
        result.push_back("null");
       }else{
        result.push_back(trans.toStr(vals.at(col)));
       }
    }
    return result;
}
