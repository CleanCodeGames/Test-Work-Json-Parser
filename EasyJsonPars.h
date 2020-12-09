#pragma once
// My easy json parser
// https://vk.com/proheisenberg
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <list>

using std::list;
using std::string;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;

namespace ejp // Easy Json Parser
{
	enum class KeyType : uint16_t {
		STR,
		OBJ
	};

	struct Key 
	{
		string m_data;		// Список данных ключа
		list<Key> m_keys;	// Список ключей, если тип ключа является объектом
		const char m_name;	// Имя ключа
		KeyType m_type;		// Тип ключа

		Key(const char name, const KeyType type = KeyType::STR) 
			: m_name(name),  m_type(type) {
		}

		void SetData(const string data) {
			m_data = data;
		}

		void Print() {
			if (m_type == KeyType::OBJ) {
				for (auto& key : m_keys)
					std::cout << ">" << m_name << "." << key.m_name << "\n" << key.m_data << std::endl;
			}
			else std::cout << ">" << m_name << "\n" << m_data << std::endl;
		}
	};


	class EasyJsonPars
	{
	private:

		list<Key> m_keys;	// Ключи
		string m_file_data;	// Данные из файла

	public:

		EasyJsonPars();
		const bool Read(string path);	// Считывание Json
		list<Key>& GetKeys();			// Получение списка ключей
		void Clear();					// Очистка списка ключей
		void Print();					// Вывод на экран
		~EasyJsonPars();
	};
};

