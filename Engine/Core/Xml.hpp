﻿#pragma once
#include "ThirdParty/pugixml/pugixml.hpp"
#include "StringUtils.hpp"
#include "ErrorWarningAssert.hpp"

namespace xml {
  class Attribute: public pugi::xml_attribute {
  public:
    Attribute(const pugi::xml_attribute& attr) : pugi::xml_attribute(attr) {};

    operator std::string() const {
      return value();
    }

    template<typename ValType>
    Attribute& operator=(const ValType& val) {
      this->set_value(toString(val).c_str());
      return *this;
    }

    Attribute& operator=(const std::string& val) {
      this->set_value(val.c_str());
      return *this;
    }

    Attribute& operator=(const char* val) {
      this->set_value(val);
      return *this;
    }
  };
}

class Xml {
public:
  Xml(const char* path);
  Xml(const char* content, size_t size);
  ~Xml();
  std::string    name()                const;
  std::string    value()               const;
  Xml            parent()              const;
  Xml            firstChild(const char* name = nullptr) const;
  bool           hasAttribute(const char* name) const;
  bool           isEmpty()             const;
  Xml            lastChild()           const;
  Xml            nextSibling()         const;
  Xml            previousSibling()     const;
  xml::Attribute appendAttribute(const char*  name, const char*  value);
  
  Xml            selectNode(const char* xpath) const;
  bool           save(const char* path)  const;
  void           save(std::ostream&  stream) const;
  void           print(std::ostream& stream) const;

  template<typename T>
  T selectAttribute(const char* xpath) const {
    pugi::xpath_node node = m_node.select_node(xpath);
    GUARANTEE_OR_DIE(node, "query return empty");
    return parse<T>(node.attribute().value());
  }
  template<typename T>
  inline T attribute(const char* attributeName, T defaultValue) const {
    return parseXmlAttribute(*this, attributeName, defaultValue);
  }

  template<typename Functor>
  inline Functor traverseChilds(const Functor& fn) const {
    for(auto& node: m_node) {
      Xml child(node, m_document);
      fn(child);
    }

    return (fn);
  }


  template<typename Functor>
  inline void traverseChilds(const std::string& name, const Functor&& fn) const {
    for (auto&& node : m_node) {
      if (node.name() != name) continue;
      Xml child(node, m_document);
      fn(child);
    }
  }

  template<typename Functor>
  inline void traverseAttributes(const Functor&& fn) const {
    for (auto& attr : m_node.attributes()) {
      std::invoke(fn, attr.name(), attr.value());
    }
  }

  const xml::Attribute operator[](const char* attribute) const;
  xml::Attribute operator[] (const char* attribute);
protected:
  Xml(const pugi::xml_node& xmlNode, pugi::xml_document* doc, bool isRoot = false);
  pugi::xml_node m_node;
  pugi::xml_document* m_document = nullptr;
  bool m_isRoot = false;

};

template<typename T>
inline T parseXmlAttribute(const Xml& ele, const char* attributeName, T defaultValue) {
  std::string raw = ele[attributeName];
  if (raw.length() == 0) return defaultValue;
  T result = parse<T>(raw);
  return result;
}

template<>
inline std::string parseXmlAttribute(const Xml& ele, const char* attributeName, std::string defaultValue) {
  std::string raw = ele[attributeName];
  return (raw.length() == 0) ? defaultValue : raw;
}

template<typename T, typename A>
inline std::vector<T, A> parseXmlAttribute(const Xml& ele, const char* attributeName, std::vector<T, A> defaultValue) {
  std::string raw = ele[attributeName];

  return (raw.length() == 0) ? defaultValue : parse<T, A>(raw.c_str(), " ,");
}


