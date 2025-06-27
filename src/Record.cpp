# include "Record.hpp"
# include "Transformation.hpp"

Record::Record(std::unordered_map<std::string, std::string> &types, std::vector<std::pair<std::string, std::string>>& values, std::string key)
{
    // Nullable value edge case is required
    for(int i = 0 ; i < values.size() ; i++){
        std::string type = types.at(values[i].first);
        if(values[i].second != "null"){
            // for the nullable value of a column
            std::any val = fromStr(type,values[i].second);
            this->vals.emplace(values[i].first,val);
        }
        this->datatypes.emplace(values[i].first, type);
    }
    this->clusteringKey = key;
}

Record::Record(const std::unordered_map<std::string, std::any> &values, std::unordered_map<std::string, std::string> types, std::string key)
    : vals(values)
{
    // for the new to be inserted record
    this->clusteringKey = key;
    this->datatypes = types;
}

bool Record::operator==(Record record)
{
    return isEqual(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
}

bool Record::operator<(Record record)
{

    return isLessThan(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
}

bool Record::operator>(Record record)
{
    return isMoreThan(this->vals.at(clusteringKey), record.getVals().at(record.getClusteringKey()));
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
    vals = v;
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
    std::vector<std::string> result;
    for(std::string col: columns){
       if(!vals.count(col)){
        result.push_back("null");
       }else{
        result.push_back(toStr(vals.at(col)));
       }
    }
    return result;
}
