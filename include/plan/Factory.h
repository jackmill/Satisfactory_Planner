/**
 * @project Satisfactory_Planner
 * @file Factory.h
 *
 * @author Jackson Miller
 * @date 2021-09-25
 * @copyright (c) 2021 Jackson Miller
 */

#ifndef SATISFACTORY_PLANNER_FACTORY_H
#define SATISFACTORY_PLANNER_FACTORY_H

#include <vector>

#include "Subfactory.h"
#include "nlohmann/json.hpp"

namespace plan {

class Factory {
    friend std::ostream &operator<< (std::ostream &out, const Factory &factory);
    friend std::istream &operator>> (std::istream& in, Factory& factory);

  public:
    Factory() = default;
    explicit Factory(const std::string& file_path, const data::DBMap& db);

    void save(const std::string &file_path) const;

	[[nodiscard]] int numSubfactories() const { return static_cast<int>(subfactories_.size()); }

	void addSubfactory(const Subfactory& new_subfactory);

	[[nodiscard]] Subfactory* subfactoryAt(int index) const { return subfactories_.at(index).get(); }

    std::vector<std::unique_ptr<Subfactory>> subfactories_;

  private:
    // Used only for generation from json files
    std::optional<data::DBMap> db_;
};

} // namespace plan

#endif //SATISFACTORY_PLANNER_FACTORY_H
