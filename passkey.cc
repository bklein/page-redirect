#include "passkey.h"

#include <cassert>
#include <utility>

namespace passkey {

RegisteredDataAccess::RegisteredDataAccess() = default;
RegisteredDataAccess::RegisteredDataAccess(const RegisteredDataAccess&) = default;
RegisteredDataAccess::RegisteredDataAccess(RegisteredDataAccess&&) noexcept = default;
RegisteredDataAccess& RegisteredDataAccess::operator=(const RegisteredDataAccess&) = default;
RegisteredDataAccess& RegisteredDataAccess::operator=(RegisteredDataAccess&&) = default;

KeyedData::KeyedData(int id, std::string msg, RegisteredDataAccess)
  : m_id(id)
  , m_msg(std::move(msg))
{}

int KeyedData::id() const { return m_id; }
const std::string& KeyedData::msg() const { return m_msg; }

auto operator<<(std::ostream& os, const KeyedData& kd) -> std::ostream& {
  os << "{" << kd.id() << ": " << std::quoted(kd.msg()) << "}";
  return os;
}

Key KeyDataStore::add(std::string msg) {
  const auto id = get_next_id();
  const auto [it, inserted] = m_data.emplace(std::make_pair(
        id,
        KeyedData{id, std::move(msg), RegisteredDataAccess{}}));
  assert(inserted);
  return id;
}

std::optional<KeyedData> KeyDataStore::get(Key key) const {
  const auto it = m_data.find(key);
  if (it != m_data.end()) {
    return std::make_optional(it->second);
  } else {
    return std::nullopt;
  }
}

int KeyDataStore::get_next_id() {
  return m_next_id++;
}

} // namespace passkey
