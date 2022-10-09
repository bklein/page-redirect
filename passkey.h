#ifndef PASSKEY_H
#define PASSKEY_H

#include <iomanip>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>

namespace passkey {

using Key = int;

class RegisteredDataAccess final {
  friend class KeyDataStore;
private:
  RegisteredDataAccess();
  RegisteredDataAccess(const RegisteredDataAccess&);
  RegisteredDataAccess(RegisteredDataAccess&&) noexcept;
  RegisteredDataAccess& operator=(const RegisteredDataAccess&);
  RegisteredDataAccess& operator=(RegisteredDataAccess&&);
};

class KeyedData {
public:
  KeyedData(int id, std::string msg, RegisteredDataAccess);
  int id() const;
  const std::string& msg() const;
private:
  int m_id;
  std::string m_msg;
};

auto operator<<(std::ostream& os, const KeyedData& kd) -> std::ostream&;

class KeyDataStore {
public:
  Key add(std::string msg);
  std::optional<KeyedData> get(Key key) const;
private:
  int m_next_id{0};
  std::unordered_map<Key, KeyedData> m_data;

  int get_next_id();
};

} // namespace passkey

#endif // PASSKEY_H
