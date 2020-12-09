#include "EasyJsonPars.h"

ejp::EasyJsonPars::EasyJsonPars() {

}

const bool ejp::EasyJsonPars::Read(const string path) {
	ifstream file;
	file.open(path + ".json");
	uint16_t count_braces = 0;	// Счётчик открытых фигурных скобок

	if (file.is_open()) 
	{
		m_file_data;
		static string key_data;
		static char key_name = '♣';
		while (!file.eof()) {
			std::getline(file, m_file_data);

			// Переключатель открытых-закрытых кавычек
			bool is_quotes_open = false;	

			// Является ли содержимое внутри кавычек именем ключа если true,
			// иначе содержимое внутри кавычек является данными для ключа
			bool is_key = true;
			
			for (auto& c : m_file_data) {
				switch (c)
				{
					case '\"':
						if (is_quotes_open) {
							if (count_braces > 1) {
								m_keys.back().m_type = KeyType::OBJ;
								if (is_key) m_keys.back().m_keys.push_back(Key(key_name));
								else  m_keys.back().m_keys.back().SetData(key_data);
							}
							else
							{
								if (is_key) m_keys.push_back(Key(key_name));
								else m_keys.back().SetData(key_data);
							}
							key_name = '♣';
							key_data.clear();
						}
						is_quotes_open = !is_quotes_open;

						break;
					case '{': 
						count_braces++;
						is_key = true;
						break;

					case ':': 
						is_key = false; 
						break;
					case ',': if(!is_quotes_open) is_key = true; break;

					case '}':
						count_braces--;
						break;

					default:
						if (is_quotes_open) {
							if (!is_key) key_data += c; // Добовляем символ в данные ключа
							else key_name = c;			// Считываем символ ключа
						}
						break;
				}
			}
		}

		file.close();
		return true;
	}
	return false;
}

void ejp::EasyJsonPars::Print() {
	for (auto& key : m_keys)
		key.Print();
}

void ejp::EasyJsonPars::Clear() {
	m_keys.clear();
	m_file_data.clear();
}

list<ejp::Key>& ejp::EasyJsonPars::GetKeys() {
	return m_keys;
}

ejp::EasyJsonPars::~EasyJsonPars() {

}