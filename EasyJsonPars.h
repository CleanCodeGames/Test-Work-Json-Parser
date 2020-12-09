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
		string m_data;		// ������ ������ �����
		list<Key> m_keys;	// ������ ������, ���� ��� ����� �������� ��������
		const char m_name;	// ��� �����
		KeyType m_type;		// ��� �����

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

		list<Key> m_keys;	// �����
		string m_file_data;	// ������ �� �����

	public:

		EasyJsonPars();
		const bool Read(string path);	// ���������� Json
		list<Key>& GetKeys();			// ��������� ������ ������
		void Clear();					// ������� ������ ������
		void Print();					// ����� �� �����
		~EasyJsonPars();
	};
};

